// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ShootPresets.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ShootPresets::ShootPresets(int direction): Command() {
    m_direction = direction;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ShootPresets::Initialize() {


	//For Low Shot
	if (m_direction == 3) {
		m_upperMotorSpeed = SmartDashboard::GetNumber("LowShotUpperMotor", 0.75);
		m_lowerMotorSpeed = SmartDashboard::GetNumber("LowShotLowerMotor", 0.5);
		printf("2135: Low Shot speed set\n");
	}

	//For Mid Shot
	else if(m_direction == 2){
		m_upperMotorSpeed = SmartDashboard::GetNumber("MidShotUpperMotor", 0.85);
		m_lowerMotorSpeed = SmartDashboard::GetNumber("MidShotLowerMotor", 0.6);
		printf("2135: Mid Shot speed set\n");
	}

	//For High Shot
	else if(m_direction == 1){
		m_upperMotorSpeed = SmartDashboard::GetNumber("HighShotUpperMotor", 0.95);
		m_lowerMotorSpeed = SmartDashboard::GetNumber("HighShotLowerMotor", 0.7);
		printf("2135: High Shot speed set\n");
	}

	else {
		m_upperMotorSpeed = 0;
		m_lowerMotorSpeed = 0;
	}

}

// Called repeatedly when this Command is scheduled to run
void ShootPresets::Execute() {
	Robot::shooter->ShootSpeeds(m_upperMotorSpeed, m_lowerMotorSpeed);
	Robot::shooter->setFireSolenoid(true);
}

// Make this return true when this Command no longer needs to run execute()
bool ShootPresets::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ShootPresets::End() {
	Robot::shooter->ShootSpeeds(0.0, 0.0);
	Robot::shooter->setFireSolenoid(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootPresets::Interrupted() {
	Robot::shooter->ShootSpeeds(0.0, 0.0);
	Robot::shooter->setFireSolenoid(false);
}
