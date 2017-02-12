// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ShooterMotorControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ShooterMotorControl::ShooterMotorControl(bool runShooter): Command() {
    m_runShooter = runShooter;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ShooterMotorControl::Initialize() {
	printf("2135: Shoot Motor Control %s - Start\n", (m_runShooter) ? "SHOOT" : "OFF");
}

// Called repeatedly when this Command is scheduled to run
void ShooterMotorControl::Execute() {
	Robot::shooter->SetMotorSpeed(m_runShooter);
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterMotorControl::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ShooterMotorControl::End() {
	printf("2135: Shoot Motor Control - Ended\n");
	Robot::shooter->SetMotorSpeed(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterMotorControl::Interrupted() {
	printf("2135: Shoot Motor Control - Interrupted\n");
	Robot::shooter->SetMotorSpeed(false);
}
