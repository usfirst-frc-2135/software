///////////////////////////////////////////////////////////////////////////////
//
//	Chassis.cpp
//
//	Chassis subsystem definition.
//
#include "../Robotmap.h"
#include "Chassis.h"
#include "../Commands/DriveWithJoystick.h"

Chassis::Chassis() : Subsystem("Chassis") {
	printf( "2135: Chassis - constructed\n" );
	driveTrain = new RobotDrive ( PWM_LEFT_DRIVE_MOTOR, PWM_RIGHT_DRIVE_MOTOR );
	driveTrain->SetSafetyEnabled ( false );
}
    
//	Default command is to use joystick input to drive

void Chassis::InitDefaultCommand () {
	SetDefaultCommand ( new DriveWithJoystick() );
}

//	Drive straight at full speed

void Chassis::goStraight () {
	driveTrain->ArcadeDrive ( 1.0, 0.0 );
}

//	Drive using joysticks as input

void Chassis::driveWithJoystick ( Joystick *driverStick ) {
	driveTrain->ArcadeDrive ( driverStick );
}



