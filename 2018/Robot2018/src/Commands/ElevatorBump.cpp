// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ElevatorBump.h"
#include "../Subsystems/Elevator.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ElevatorBump::ElevatorBump(bool direction): frc::Command() {
    m_direction = direction;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::elevator.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ElevatorBump::Initialize() {
	const char *strName;

	if (m_direction)
		strName = "UP";
	else
		strName = "DOWN";

	std::printf("2135: ElevatorBump %s - Init\n", strName);
	Robot::elevator->BumpToPosition(m_direction);
}

// Called repeatedly when this Command is scheduled to run
void ElevatorBump::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorBump::IsFinished() {
	// Elevator runs forever (except when interrupted by other commands)
    return Robot::elevator->MoveToPositionIsFinished();
}

// Called once after isFinished returns true
void ElevatorBump::End() {
	std::printf("2135: ElevatorBump - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorBump::Interrupted() {
	std::printf("2135: ElevatorBump - Interrupted\n");
}
