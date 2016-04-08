// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveDistanceTimed.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveDistanceTimed::DriveDistanceTimed(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	m_maxSpeed = 0.0;
	m_time = 0.0;
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveDistanceTimed::Initialize() {
	printf("2135: Drive Distance Timed\n");
	m_time = SmartDashboard::GetNumber("AutoDriveTimed", 3.0);
	m_maxSpeed = SmartDashboard::GetNumber("AutoDriveTimedSpeed", 0.8);
	m_timer.Reset();
	m_timer.Start();

	printf("2135: m_time = %f\n", m_time);
}

// Called repeatedly when this Command is scheduled to run
void DriveDistanceTimed::Execute() {
	Robot::chassis->MoveUsingLeftRightMotorOutputs(m_maxSpeed, m_maxSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistanceTimed::IsFinished() {
    return (m_timer.HasPeriodPassed(m_time));
}

// Called once after isFinished returns true
void DriveDistanceTimed::End() {
	m_timer.Stop();
	Robot::chassis->MoveStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistanceTimed::Interrupted() {
	m_timer.Stop();
	Robot::chassis->MoveStop();
}
