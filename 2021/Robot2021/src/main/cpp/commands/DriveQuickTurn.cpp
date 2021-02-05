// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "RobotContainer.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/DriveQuickTurn.h"

DriveQuickTurn::DriveQuickTurn(){

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("DriveQuickTurn");

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

    RobotContainer *container = RobotContainer::GetInstance ();
    m_drivetrain = &container->m_drivetrain;
}

// Called just before this Command runs the first time
void DriveQuickTurn::Initialize()
{
    std::printf("2135: DriveQuickTurn - Init\n");
    m_drivetrain->MoveSetQuickTurn(true);
}

// Called repeatedly when this Command is scheduled to run
void DriveQuickTurn::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveQuickTurn::IsFinished()
{
    return false;
}

// Called once after isFinished returns true
void DriveQuickTurn::End(bool interrupted)
{
    std::printf("2135: DriveQuickTurn - End\n");
    m_drivetrain->MoveSetQuickTurn(false);
}

bool DriveQuickTurn::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
