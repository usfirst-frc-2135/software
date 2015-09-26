#include "CheesyVisionServer.h"
#include "WPILib.h"
#include "networktables2/util/EOFException.h"

CheesyVisionServer *CheesyVisionServer::_instance = (CheesyVisionServer *) 0;

#define HEARTBEAT_TIMEOUT 3.0

CheesyVisionServer::CheesyVisionServer(int port)
{
    _listenPort = port;
    _counting = false;
    _curLeftStatus = false;
    _curRightStatus = false;
    _lastHeartbeatTime = Timer::GetFPGATimestamp();
    _leftCount = 0;
    _rightCount = 0;
    _totalCount = 0;
    _listening = false;
    
    
}

void CheesyVisionServer::Run()
{
    if (_listening == false) return;    //Make sure we are listening
    
    SocketServerStreamProvider *sock;
    sock = new SocketServerStreamProvider(_listenPort);
    while (_listening)
    {
        IOStream *stream = sock->accept();
        _lastHeartbeatTime = Timer::GetFPGATimestamp();
        try
        {
            while (Timer::GetFPGATimestamp() < _lastHeartbeatTime + HEARTBEAT_TIMEOUT)
            {
                try 
                {
                    uint8_t byte;
                    stream->read(&byte, 1);
                    _curLeftStatus = (byte & (1 << 1)) > 0;
                    _curRightStatus = (byte & (1 << 0)) > 0;
                    UpdateCounts(_curLeftStatus,_curRightStatus);
                    _lastHeartbeatTime = Timer::GetFPGATimestamp();
                }
                catch (EOFException e)
                {
                    //End of file, wait for a bit and read some more
                    Wait(0.05);
                }   
                
            }
        }
        catch (IOException e) 
        {
            printf("Socket IO error: %s\n", e.what());
            //Catching this exception will dro
        }
        delete stream;//close, delete and recreate the stream

        Wait(0.05);
    }
    delete sock;
}

void CheesyVisionServer::Reset()
{
    _leftCount = 0;
    _rightCount = 0;
    _totalCount = 0;
    
    _curLeftStatus = false;
    _curRightStatus = false;
}

void CheesyVisionServer::UpdateCounts(bool left, bool right)
{
    if (true == _counting)
    {
        _leftCount += left ? 1 : 0;
        _rightCount += right ? 1 : 0;
        _totalCount++;
    }
}

CheesyVisionServer *CheesyVisionServer::GetInstance()
{
    if (CheesyVisionServer::_instance == (CheesyVisionServer *) 0)
    {
        CheesyVisionServer::_instance = new CheesyVisionServer();
    }
    return CheesyVisionServer::_instance;
}

bool CheesyVisionServer::HasClientConnection()
{
    return (_lastHeartbeatTime > 0) && (Timer::GetFPGATimestamp() - _lastHeartbeatTime);
}

   

