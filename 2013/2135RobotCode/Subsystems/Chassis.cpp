///////////////////////////////////////////////////////////////////////////////
//
//	Chassis.cpp
//
//	Chassis subsystem definition.
//
//#include "WPILib.h"
#include "../Robotmap.h"
#include "Chassis.h"
#include "../Commands/DriveWithJoystick.h"

Chassis::Chassis() : Subsystem("Chassis") {
	printf( "2135: Chassis - constructed\n" );
	
	SpeedController* chassisleftMotor = NULL;
	SpeedController* chassisrightMotor = NULL;
	RobotDrive* chassisdriveTrain = NULL;

	chassisleftMotor = new Victor ( 1, PWM_LEFT_DRIVE_MOTOR);	
	chassisrightMotor = new Victor ( 1, PWM_RIGHT_DRIVE_MOTOR);
	chassisdriveTrain = new RobotDrive ( chassisleftMotor, chassisrightMotor );

	chassisdriveTrain->SetSafetyEnabled ( false );
}
    
//	Default command is to use joystick input to drive

void Chassis::InitDefaultCommand () {
	SetDefaultCommand ( new DriveWithJoystick() );
}

//	Drive straight at full speed

void Chassis::goStraight () {
//	chassisdriveTrain->ArcadeDrive ( 1.0, 0.0 );
}

//	Drive using joysticks as input

void Chassis::driveWithJoystick ( Joystick *driverStick ) {
//	chassisdriveTrain->ArcadeDrive ( driverStick );
}



