#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
	
private:
	Joystick *driverStick;
	Joystick *operatorStick;
	JoystickButton *driverTrigger;
	JoystickButton *operatorTrigger;
	
public:
	OI();
	Joystick *getDriverJoystick();
	Joystick *getOperatorJoystick();
	float OI::getDriverThrottle();
	float OI::getOperatorThrottle();
};

#endif
