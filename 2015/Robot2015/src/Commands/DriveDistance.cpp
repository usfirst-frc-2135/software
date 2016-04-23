// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveDistance.h"


DriveDistance::DriveDistance() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	m_inches = 0.0;
}

DriveDistance::DriveDistance(double inches) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(Robot::chassis);
	m_inches = inches;
}


// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	printf("2135: Drive Distance\n");

	m_inches = SmartDashboard::GetNumber("Drive Distance", 0);
	printf("2135:   %f inches\n", m_inches);
	Robot::chassis->DriveDistanceWithPIDInit(m_inches);
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	Robot::chassis->DriveDistanceWithPIDExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	return (Robot::chassis->DriveDistanceWithPIDIsAtSetpoint());
	printf("PID is finished\n");
}

// Called once after isFinished returns true
void DriveDistance::End() {
	Robot::chassis->DriveDistanceWithPIDStop();
	printf("PID is stopped\n");

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() {
	Robot::chassis->DriveDistanceWithPIDStop();
	printf("PID is interrupted\n");
}

