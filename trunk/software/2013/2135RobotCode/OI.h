#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
	
private:
	Joystick *stick;
	JoystickButton *trigger;

public:
	OI();
	Joystick *getJoystick();
};

#endif
