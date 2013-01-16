#include "Robotmap.h"
#include "OI.h"
#include "Commands/Shoot.h"
#include "Commands/DriveStraight.h"

OI::OI() {
	driverStick = new Joystick( DRIVER_JOYSTICK_PORT );
	operatorStick = new Joystick( OPERATOR_JOYSTICK_PORT );
	
	driverTrigger = new JoystickButton( driverStick, Joystick::kTriggerButton );
	driverTrigger->WhenPressed ( new Shoot );
	operatorTrigger = new JoystickButton( operatorStick, Joystick::kTriggerButton );
//	operatorTrigger->WhenPressed ( new DriveStraight );
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

	driverThrottle = driverStick->GetRawAxis( Joystick::kThrottleAxis );
	printf ( "driverStick->GetRawAxis\n" );
	return driverThrottle;
}

float OI::getOperatorThrottle() {
	float operatorThrottle;

	operatorThrottle = operatorStick->GetAxis( Joystick::kThrottleAxis );
    //printf( "2135: operatorStick->GetAxis\n");
	return operatorThrottle;
}

