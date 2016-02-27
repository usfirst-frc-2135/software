// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveWait.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveWait::DriveWait(double time): Command() {
    m_time = time;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveWait::Initialize() {
	printf("2135: Drive Wait Initialized\n");
	m_timer.Reset();
	m_timer.Start();
	Robot::chassis->MoveStop();
}

// Called repeatedly when this Command is scheduled to run
void DriveWait::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool DriveWait::IsFinished() {
	return (m_timer.HasPeriodPassed(m_time));
}

// Called once after isFinished returns true
void DriveWait::End() {
	m_timer.Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWait::Interrupted() {
	m_timer.Stop();
}
