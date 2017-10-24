// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutonDrivePeg1Turn.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutonDrivePeg1Turn::AutonDrivePeg1Turn(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutonDrivePeg1Turn::Initialize() {
	double angle = Robot::LoadPreferencesVariable(AUTON_POS1_TURN, AUTON_POS1_TURN_D);

	printf("2135: Auton Drive Peg 1 Turn - Initialize: %f degrees\n", angle);
	Robot::chassis->MoveDriveHeadingInit(angle);
}

// Called repeatedly when this Command is scheduled to run
void AutonDrivePeg1Turn::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutonDrivePeg1Turn::IsFinished() {
    return Robot::chassis->MoveDriveHeadingIsPIDAtSetPoint();
}

// Called once after isFinished returns true
void AutonDrivePeg1Turn::End() {
	Robot::chassis->MoveDriveHeadingStop();
	printf("2135: Auton Drive Peg 1 Turn - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutonDrivePeg1Turn::Interrupted() {
	Robot::chassis->MoveDriveHeadingStop();
	printf("2135: Auton Drive Peg 1 Turn - Interrupted\n");
}