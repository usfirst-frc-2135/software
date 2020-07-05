// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/DriveReset.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveReset::DriveReset(): frc::Command()
{
    // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    SetRunWhenDisabled(true);
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveReset::Initialize()
{
    std::printf("2135: DriveReset - Init\n");
}

// Called repeatedly when this Command is scheduled to run
void DriveReset::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveReset::IsFinished()
{
    return true;
}

// Called once after isFinished returns true
void DriveReset::End()
{
    std::printf("2135: DriveReset - End\n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveReset::Interrupted()
{
    std::printf("2135: DriveReset - Interrupted\n");
}
