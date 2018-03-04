// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <Commands/AutoDriveDist.h>
#include "../FRC2135/RobotConfig.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoDriveDist::AutoDriveDist(double distance): frc::Command() {
    m_distance = distance;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivetrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoDriveDist::Initialize(){
	// If distance is less than 0.1 (default is 0.0), then read RobotConfig
	//	auton programs will pass in larger value
		RobotConfig* config = RobotConfig::GetInstance();
		config->GetValueAsDouble("Pos123Move_D", m_distance, 97.25);

	std::printf("2135: AutoDriveDist - Init\n");
	Robot::drivetrain->MoveDriveDistancePIDInit(m_distance);

}

// Called repeatedly when this Command is scheduled to run
void AutoDriveDist::Execute() {
	Robot::drivetrain->MoveDriveDistancePIDExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveDist::IsFinished() {
    return (Robot::drivetrain->MoveDriveDistanceIsPIDAtSetpoint());
}

// Called once after isFinished returns true
void AutoDriveDist::End() {
	Robot::drivetrain->MoveDriveDistancePIDStop();
	std::printf("2135: AutoDriveDist - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveDist::Interrupted() {
	Robot::drivetrain->MoveDriveDistancePIDStop();
	std::printf("2135: AutoDriveDist - Interrupted\n");
}