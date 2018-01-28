// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "../RobotConfig.h"
#include "AutoDriveDistance.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoDriveDistance::AutoDriveDistance(double distance): frc::Command() {
    m_distance = distance;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivetrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoDriveDistance::Initialize(){
	// If distance is less than 0.1 (default is 0.0), then read RobotConfig
	//	auton programs will pass in larger value
	if (fabs(m_distance) < 0.1) {
		RobotConfig* config = RobotConfig::GetInstance();
		config->GetValueAsDouble("Pos123Move_D", m_distance, 0.0);
	}
	std::printf("2135: AutoDriveDistance - Init\n");
	Robot::drivetrain->MoveDriveDistancePIDInit(m_distance);

}

// Called repeatedly when this Command is scheduled to run
void AutoDriveDistance::Execute() {
	Robot::drivetrain->MoveDriveDistancePIDExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveDistance::IsFinished() {
    return (Robot::drivetrain->MoveDriveDistanceIsPIDAtSetpoint());
}

// Called once after isFinished returns true
void AutoDriveDistance::End() {
	Robot::drivetrain->MoveDriveDistancePIDStop();
	std::printf("2135: AutoDriveDistance - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveDistance::Interrupted() {
	Robot::drivetrain->MoveDriveDistancePIDStop();
	std::printf("2135: AutoDriveDistance - Interrupted\n");
}
