// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "FireValve3.h"
FireValve3::FireValve3() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::firing);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void FireValve3::Initialize() {
	printf ( "2135: Fire Valve 3\n" );
	SetTimeout(0.5);
}
// Called repeatedly when this Command is scheduled to run
void FireValve3::Execute() {
	Robot::firing->EnableFiringValve( 3 );
}
// Make this return true when this Command no longer needs to run execute()
bool FireValve3::IsFinished() {
	return IsTimedOut();
}
// Called once after isFinished returns true
void FireValve3::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireValve3::Interrupted() {
}
