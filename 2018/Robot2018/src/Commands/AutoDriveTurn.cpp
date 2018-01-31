// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoDriveTurn.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoDriveTurn::AutoDriveTurn(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::drivetrain.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoDriveTurn::Initialize() {
	std::printf("2135: AutoDriveTurn - Init\n");
	Robot::drivetrain->MoveDriveTurnPIDInit(90.0); // TODO: Hard coded for now and will use a preference/robot default to get the value
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveTurn::Execute() {
	Robot::drivetrain->MoveDriveTurnPIDExecute();

}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveTurn::IsFinished() {
	bool isFinished;

	isFinished = Robot::drivetrain->MoveDriveTurnIsPIDAtSetPoint();

    return isFinished;
}

// Called once after isFinished returns true
void AutoDriveTurn::End() {
	std::printf("2135: AutoDriveTurn - End\n");
	Robot::drivetrain->MoveDriveTurnPIDStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveTurn::Interrupted() {
	std::printf("2135: AutoDriveTurn - Interrupted\n");
	Robot::drivetrain->MoveDriveTurnPIDStop();
}
