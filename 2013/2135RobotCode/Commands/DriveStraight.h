///////////////////////////////////////////////////////////////////////////////
//
//	DriveStraight.h
//
//	DriveStraight command header file.
//
#ifndef DRIVESTRAIGHT_H
#define DRIVESTRAIGHT_H

#include "../CommandBase.h"

//	Subclass CommandBase type

class DriveStraight: public CommandBase {
	
private:
	double m_timeout;
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	DriveStraight( double timeout );
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
