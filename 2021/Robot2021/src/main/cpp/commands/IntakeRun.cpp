// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/IntakeRun.h"

IntakeRun::IntakeRun(){

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(Robot::chassis.get());
    SetName("IntakeRun");

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

}

// Called just before this Command runs the first time
void IntakeRun::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void IntakeRun::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeRun::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void IntakeRun::End(bool interrupted) {

}

bool IntakeRun::RunsWhenDisabled() const {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
