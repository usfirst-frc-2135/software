#include "Robotmap.h"
#include "OI.h"
#include "Commands/DriveInASquare.h"
#include "Commands/Shoot.h"
#include "Joystick.h"

OI::OI() {
	driverStick = new Joystick( DRIVER_JOYSTICK_PORT );
	operatorStick = new Joystick( OPERATOR_JOYSTICK_PORT );
	
	driverTrigger = new JoystickButton( driverStick, Joystick::kTriggerButton );
	driverTrigger->WhenPressed ( new Shoot );
}

Joystick * OI::getDriverJoystick() {
	return driverStick;
}

Joystick * OI::getOperatorJoystick() {
	return operatorStick;
}

float OI::getDriverThrottle() {
	float driverThrottle;

	driverThrottle = driverStick->GetAxis( Joystick::kThrottleAxis );
	return driverThrottle;
}

float OI::getOperatorThrottle() {
	float operatorThrottle;

	operatorThrottle = operatorStick->GetAxis( Joystick::kThrottleAxis );
//	printf( "2135: operatorStick->GetAxis\n");
	return operatorThrottle;
}

