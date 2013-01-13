#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
	
private:
	Joystick *driverStick;
	Joystick *operatorStick;
	JoystickButton *operatorTrigger;

public:
	OI();
	Joystick *getDriverJoystick();
	Joystick *getOperatorJoystick();
};

#endif
