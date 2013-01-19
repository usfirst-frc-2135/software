///////////////////////////////////////////////////////////////////////////////
//
//	DriveWithJoystick.cpp
//
//	Joystick command definition file.
//
#include "DriveWithJoystick.h"

//	When created, take control of chassis subsystem

DriveWithJoystick::DriveWithJoystick() {
	printf( "2135: DriveWithJoystick - Constructed\n" );
	Requires( chassis );
}

//	Initialization tasks
//	Called just before this Command runs the first time

void DriveWithJoystick::Initialize() {
	printf( "2135: DriveWithJoystick - Initialize\n" );
}

//	Normal tasks
//	Called repeatedly when this Command is scheduled to run

void DriveWithJoystick::Execute() {
	chassis->driveWithJoystick( oi->getDriverJoystick() );
}

//	Test for when finished
//	Make this return true when this Command no longer needs to run execute()

bool DriveWithJoystick::IsFinished() {
	return false;
}

//	Called once after isFinished returns true

void DriveWithJoystick::End() {
	printf( "2135: DriveWithJoystick - End\n" );
}

// Called when another command uses require on this subsystem and is scheduled

void DriveWithJoystick::Interrupted() {
	printf( "2135: DriveWithJoystick - Interrupted\n" );
}
