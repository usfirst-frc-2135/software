#ifndef DRIVESTRAIGHT_H
#define DRIVESTRAIGHT_H

#include "../CommandBase.h"

class DriveStraight: public CommandBase {
	
private:
	double m_timeout;
	
public:
	DriveStraight( double timeout );
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
