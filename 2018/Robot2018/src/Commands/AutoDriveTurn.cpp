// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoDriveTurn.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoDriveTurn::AutoDriveTurn(double angle): frc::Command() {
    m_angle = angle;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivetrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoDriveTurn::Initialize() {
	RobotConfig *config;
	// If distance is less than 0.1 (default is 0.0), then read RobotConfig
	//	auton programs will pass in larger value
	if (fabs(m_angle) < 0.1) {
		config = RobotConfig::GetInstance();
		config->GetValueAsDouble("AutoDriveTurn", m_angle, 90.0);
	}

	std::printf("2135: AutoDriveTurn - Init %4.1f degrees\n", m_angle);
	Robot::drivetrain->MoveDriveTurnPIDInit(m_angle);
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveTurn::Execute() {
	Robot::drivetrain->MoveDriveTurnPIDExecute();

}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveTurn::IsFinished() {
    return (Robot::drivetrain->MoveDriveTurnIsPIDAtSetPoint());
}

// Called once after isFinished returns true
void AutoDriveTurn::End() {
	std::printf("2135: AutoDriveTurn - End\n");
	Robot::drivetrain->MoveDriveTurnPIDStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveTurn::Interrupted() {
	std::printf("2135: AutoDriveTurn - Interrupted\n");
	Robot::drivetrain->MoveDriveTurnPIDStop();
}
