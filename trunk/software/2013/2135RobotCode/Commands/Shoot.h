///////////////////////////////////////////////////////////////////////////////
//
//	Shoot.h
//
//	Shoot command header file.
//
#ifndef SHOOT_H
#define SHOOT_H

#include "../CommandBase.h"

//	Subclass CommandBase type

class Shoot: public CommandBase {

private:
	double m_power;
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shoot( double power );
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
