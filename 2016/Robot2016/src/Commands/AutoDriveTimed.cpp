// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoDriveTimed.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoDriveTimed::AutoDriveTimed(double waitTime, double driveTime, double driveSpeed): Command() {
    m_waitTime = waitTime;
    m_driveTime = driveTime;
    m_driveSpeed = driveSpeed;
    m_mode = WAITMODE;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoDriveTimed::Initialize() {
	printf("2135: Auto Drive Timed - Wait %f Drive %f Speed %f\n",
		m_waitTime, m_driveTime, m_driveSpeed);
	m_mode = WAITMODE;
	m_timer.Reset();
	m_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveTimed::Execute() {
	if (m_mode == WAITMODE) {
		Robot::chassis->MoveStop();
		if (m_timer.HasPeriodPassed(m_waitTime)) {
			m_mode = DRIVEMODE;
			m_timer.Reset();
			m_timer.Start();
		}
	}
	else if (m_mode == DRIVEMODE) {
		Robot::chassis->MoveUsingLeftRightMotorOutputs(m_driveSpeed, m_driveSpeed);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveTimed::IsFinished() {
	if (m_mode == WAITMODE) {
		return false;
	}
	else if (m_mode == DRIVEMODE) {
		return (m_timer.HasPeriodPassed(m_driveTime));
	}
	return true;
}

// Called once after isFinished returns true
void AutoDriveTimed::End() {
	printf("Auto Drive Timed - End\n");
	m_timer.Stop();
	Robot::chassis->MoveStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveTimed::Interrupted() {
	printf("Auto Drive Timed - Interrupted\n");
	m_timer.Stop();
	Robot::chassis->MoveStop();
}
