// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "AzimuthOff.h"
AzimuthOff::AzimuthOff() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::azimuth);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void AzimuthOff::Initialize() {
	printf( "2135: AzimuthOff\n" );
}
// Called repeatedly when this Command is scheduled to run
void AzimuthOff::Execute() {
	
}
// Make this return true when this Command no longer needs to run execute()
bool AzimuthOff::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void AzimuthOff::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AzimuthOff::Interrupted() {
}
