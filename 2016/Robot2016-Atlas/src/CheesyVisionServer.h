#include "jankyTask.h"
#include "networktables2/stream/SocketServerStreamProvider.h"

#ifndef CHEESYVISIONSERVER_H_
#define CHEESYVISIONSERVER_H_



class CheesyVisionServer: private JankyTask
{

    static CheesyVisionServer *_instance;
    
    
    CheesyVisionServer(int port = 1180);
    int _listenPort;
    
    int _leftCount;
    int _rightCount;
    int _totalCount;
    bool _curLeftStatus;
    bool _curRightStatus;
    bool _counting;
    
    double _lastHeartbeatTime;
    bool _listening;
public:
    static CheesyVisionServer *GetInstance();
    bool HasClientConnection();
    void SetPort(int port){_listenPort = port;}
    virtual void Run();
    void StartListening(){_listening = true; Start();}
    void StopListening(){_listening = false; Pause();}
    
    void Reset();
    void UpdateCounts(bool left, bool right);
    void StartSamplingCounts(){_counting = true;}
    void StopSamplingCounts(){_counting = false;}

    bool GetLeftStatus(){return _curLeftStatus;}
    bool GetRightStatus(){return _curRightStatus;}
    int GetLeftCount(){return _leftCount;}
    int GetRightCount(){return _rightCount;}
    int GetTotalCount(){return _totalCount;}


};


#endif //CHEESYVISIONSERVER_H_
