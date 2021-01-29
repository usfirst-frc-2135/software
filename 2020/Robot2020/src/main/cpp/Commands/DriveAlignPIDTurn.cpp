// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/DriveAlignPIDTurn.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveAlignPIDTurn::DriveAlignPIDTurn(double horizontalTarget): frc::Command() {
m_horizontalTarget = horizontalTarget;
    // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivetrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveAlignPIDTurn::Initialize() {
    std::printf("2135: Drive Align PID Turn - Init\n");
    Robot::drivetrain->MoveAlignTurnPIDInit(m_horizontalTarget);
}

// Called repeatedly when this Command is scheduled to run
void DriveAlignPIDTurn::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool DriveAlignPIDTurn::IsFinished() {
    return Robot::drivetrain->MoveAlignTurnPIDISFinished();
}

// Called once after isFinished returns true
void DriveAlignPIDTurn::End() {
    Robot::drivetrain->MoveAlignTurnPIDStop();
    std::printf("2135: Drive Align PID Turn - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveAlignPIDTurn::Interrupted() {
    Robot::drivetrain->MoveAlignTurnPIDStop();
    std::printf("2135: Drive Align PID Turn - Interrupted\n");
}