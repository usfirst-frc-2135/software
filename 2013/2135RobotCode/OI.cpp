#include "Robotmap.h"
#include "OI.h"
#include "Commands/DriveInASquare.h"
#include "Commands/Shoot.h"

OI::OI() {
	driverStick = new Joystick( DRIVER_JOYSTICK_PORT );
	operatorStick = new Joystick( OPERATOR_JOYSTICK_PORT );
	
	operatorTrigger = new JoystickButton( operatorStick, Joystick::kTopButton );
	operatorTrigger->WhenPressed ( new Shoot );
}

Joystick * OI::getDriverJoystick() {
	return driverStick;
}

Joystick * OI::getOperatorJoystick() {
	return operatorStick;
}
