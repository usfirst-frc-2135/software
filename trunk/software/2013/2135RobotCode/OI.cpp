///////////////////////////////////////////////////////////////////////////////
//
//	OI.cpp
//
//	Operator Interface definitions.
//
#include "Robotmap.h"
#include "OI.h"
#include "Commands/DriveStraight.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/Shoot.h"

//	Define operator joysticks, buttons, and dashboard data

OI::OI() {
	printf ("2135: OI - constructed\n" );
	driverStick = new Joystick( DRIVER_JOYSTICK_PORT );
	operatorStick = new Joystick( OPERATOR_JOYSTICK_PORT );
	
	driverTrigger = new JoystickButton( driverStick, Joystick::kDefaultTriggerButton );
	driverTrigger->WhileActive( new Shoot( 0 ) );
	operatorTrigger = new JoystickButton( operatorStick, Joystick::kDefaultTriggerButton );
	operatorTrigger->WhenPressed ( new DriveStraight(2) );

	SmartDashboard::PutData( "Shoot", new Shoot( 0 ) );
	SmartDashboard::PutData( "DriveWithJoystick", new DriveWithJoystick() );
//	SmartDashboard::PutData( (NamedSendable *) "SchedulerData" );
}

//	Get driver joystick instance

Joystick * OI::getDriverJoystick() {
	//printf( "getDriverJoystick\n" );
	return driverStick;
}
	
//	Get operator joystick instance

Joystick * OI::getOperatorJoystick() {
	return operatorStick;
}

//	Get driver joystick throttle setting

float OI::getDriverThrottle() {
	float driverThrottle;

	driverThrottle = driverStick->GetThrottle();
	return driverThrottle;
}

//	Get driver joystick throttle setting

float OI::getOperatorThrottle() {
	float operatorThrottle;

	operatorThrottle = operatorStick->GetThrottle();
	return operatorThrottle;
}

