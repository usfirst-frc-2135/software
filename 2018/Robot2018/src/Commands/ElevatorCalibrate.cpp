// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ElevatorCalibrate.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ElevatorCalibrate::ElevatorCalibrate(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::elevator.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ElevatorCalibrate::Initialize() {
	std::printf("2135: Elevator Calibrate Init\n");
	Robot::elevator->CalibrationInit();

	//Set safety timer.
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
	m_safetyTimeout = 3.0;
}

// Called repeatedly when this Command is scheduled to run
void ElevatorCalibrate::Execute() {
	Robot::elevator->CalibrationExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorCalibrate::IsFinished() {
	//Check to see if it has passed the safety timeout.
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout)) {
		std::printf("2135: Elevator Calibrate - Safety Timer Timeout!\n");
		return true;	// exits without valid calibration
	}

	// Otherwise continue to use elevator calibration routine
	return Robot::elevator->CalibrationIsFinished();
}

// Called once after isFinished returns true
void ElevatorCalibrate::End() {
	std::printf("2135: Elevator Calibrate Ended\n");
	Robot::elevator->CalibrationStop();
	m_safetyTimer.Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorCalibrate::Interrupted() {
	std::printf("2135: Elevator Calibrate Interrupted\n");
	Robot::elevator->CalibrationStop();
	m_safetyTimer.Stop();
}
