// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "IndexerMotorEnable.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

IndexerMotorEnable::IndexerMotorEnable(int Direction): Command() {
    m_Direction = Direction;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    m_indexerSpeed = 0.0;
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void IndexerMotorEnable::Initialize() {
	m_indexerSpeed = SmartDashboard::GetNumber("IndexerSpeed", 0.50);

	if (m_Direction == 1) { 							// Acquire
		printf("2135: Indexer Motor Enable Acquire\n");
		m_indexerSpeed *= 1;
	}

	else if (m_Direction == -1) {						// Expel
		printf("2135: Indexer Motor Enable Expel\n");
		m_indexerSpeed *= -1;
	}

	else {
		m_indexerSpeed = 0;								// Default
	}
}

// Called repeatedly when this Command is scheduled to run
void IndexerMotorEnable::Execute() {
	Robot::sweeper->SetIndexerSpeed(m_indexerSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool IndexerMotorEnable::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void IndexerMotorEnable::End() {
	Robot::sweeper->SetIndexerSpeed(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IndexerMotorEnable::Interrupted() {
	Robot::sweeper->SetIndexerSpeed(0.0);
}
