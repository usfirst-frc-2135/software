// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Shoot.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

Shoot::Shoot(double upperMotorSpeed, double lowerMotorSpeed): Command() {
    m_upperMotorSpeed = upperMotorSpeed;
    m_lowerMotorSpeed = lowerMotorSpeed;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void Shoot::Initialize() {
	m_upperMotorSpeed = (SmartDashboard::GetNumber("Upper Shooter Speed", 0.0));
	m_lowerMotorSpeed = (SmartDashboard::GetNumber("Lower Shooter Speed", 0.0));
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
	Robot::shooter->ShootSpeeds(m_upperMotorSpeed, m_lowerMotorSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void Shoot::End() {
	Robot::shooter->ShootSpeeds(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
	Robot::shooter->ShootSpeeds(0.0, 0.0);
}
