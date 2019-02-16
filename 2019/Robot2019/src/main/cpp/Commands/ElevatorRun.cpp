// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/ElevatorRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ElevatorRun::ElevatorRun(int height): frc::Command() {
    m_height = height;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::elevator.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ElevatorRun::Initialize() {
	std::printf("2135: ElevatorRun - Init [%d]\n", m_height);
    Robot::elevator->MoveToPositionInit(m_height);
}

// Called repeatedly when this Command is scheduled to run
void ElevatorRun::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorRun::IsFinished() {
    return Robot::elevator->MoveToPositionIsFinished();
}

// Called once after isFinished returns true
void ElevatorRun::End() {
	std::printf("2135: ElevatorRun - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorRun::Interrupted() {
	std::printf("2135: ElevatorRun - Interrupted\n");
}
