// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/GPShift.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

GPShift::GPShift(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void GPShift::Initialize() {
    printf("2135: Game Piece - CARGO\n");
    Robot::elevator->SetGamePiece(true);
    Robot::elbow->SetGamePiece(true);
    Robot::wrist->SetGamePiece(true);
}

// Called repeatedly when this Command is scheduled to run
void GPShift::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool GPShift::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void GPShift::End() {
    printf("2135: Game Piece - HATCH PANEL\n");
    Robot::elevator->SetGamePiece(false);
    Robot::elbow->SetGamePiece(false);
    Robot::wrist->SetGamePiece(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GPShift::Interrupted() {
    printf("2135: Game Piece - HATCH PANEL\n");
    Robot::elevator->SetGamePiece(false);
    Robot::elbow->SetGamePiece(false);
    Robot::wrist->SetGamePiece(false);
}