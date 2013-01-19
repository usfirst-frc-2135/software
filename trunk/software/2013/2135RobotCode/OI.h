///////////////////////////////////////////////////////////////////////////////
//
//	OI.h
//
//	Header file base for Operator Interface.
//
#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {

	//	Define all joysticks and buttons
	
private:
	Joystick *driverStick;
	Joystick *operatorStick;
	JoystickButton *driverTrigger;
	JoystickButton *operatorTrigger;
	
	//	Joystick commands
	
public:
	OI();
	Joystick *getDriverJoystick();
	Joystick *getOperatorJoystick();
	float OI::getDriverThrottle();
	float OI::getOperatorThrottle();
};

#endif
