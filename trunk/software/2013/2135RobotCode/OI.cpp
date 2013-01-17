#include "Robotmap.h"
#include "OI.h"
#include "Commands/Shoot.h"
#include "Commands/DriveStraight.h"

OI::OI() {
	printf (" 2135 - OI::OI\n" );
	driverStick = new Joystick( DRIVER_JOYSTICK_PORT );
	operatorStick = new Joystick( OPERATOR_JOYSTICK_PORT );
	
	driverTrigger = new JoystickButton( driverStick, Joystick::kDefaultTriggerButton );
	driverTrigger->WhileActive( new Shoot );
	operatorTrigger = new JoystickButton( operatorStick, Joystick::kDefaultTriggerButton );
	operatorTrigger->WhenPressed ( new DriveStraight (2) );
}

Joystick * OI::getDriverJoystick() {
	//printf( "getDriverJoystick\n" );
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
	return operatorThrottle;
}

