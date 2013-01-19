///////////////////////////////////////////////////////////////////////////////
//
//	DriveWithJoystick.h
//
//	DriveWithJoystick command header file
//
#ifndef DRIVEWITHJOYSTICK_H
#define DRIVEWITHJOYSTICK_H

#include "../CommandBase.h"

//	Subclass CommandBase type

class DriveWithJoystick: public CommandBase {
	
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	DriveWithJoystick();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
