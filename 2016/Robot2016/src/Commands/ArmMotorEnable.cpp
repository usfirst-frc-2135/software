// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ArmMotorEnable.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ArmMotorEnable::ArmMotorEnable(int Direction): Command() {
    m_Direction = Direction;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::sweeper.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ArmMotorEnable::Initialize() {
	m_sweeperSpeed = SmartDashboard::GetNumber("SweeperSpeed", 0.90);

	if (m_Direction == 0) {								//Default
		m_sweeperSpeed = 0;
	}

	else if (m_Direction == 1) { 						//Acquire
		printf("2135: Arm Motor Enable Acquire\n");
		m_sweeperSpeed = m_sweeperSpeed * 1;
	}

	else if (m_Direction == -1) {						//Expel
		printf("2135: Arm Motor Enable Expel\n");
		m_sweeperSpeed = m_sweeperSpeed * (-1);
	}

	else {
		m_sweeperSpeed = 0;
	}
}

// Called repeatedly when this Command is scheduled to run
void ArmMotorEnable::Execute() {
	Robot::sweeper->SetMotorSpeed(m_sweeperSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool ArmMotorEnable::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ArmMotorEnable::End() {
	Robot::sweeper->SetMotorSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmMotorEnable::Interrupted() {
	Robot::sweeper->SetMotorSpeed(0.0);
}
