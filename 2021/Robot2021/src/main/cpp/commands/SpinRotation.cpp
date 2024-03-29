// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <spdlog/spdlog.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/SpinRotation.h"

SpinRotation::SpinRotation(Spinner *m_spinner) : m_spinner(m_spinner)
{
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("SpinRotation");
    AddRequirements(m_spinner);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
}

// Called just before this Command runs the first time
void SpinRotation::Initialize()
{
    spdlog::info("SpinRotation - Init");
    m_spinner->ControlRotationInit();
}

// Called repeatedly when this Command is scheduled to run
void SpinRotation::Execute()
{
    m_spinner->ControlRotationExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool SpinRotation::IsFinished()
{
    return m_spinner->ControlRotationIsFinished();
}

// Called once after isFinished returns true
void SpinRotation::End(bool interrupted)
{
    spdlog::info("SpinRotation - End");
    m_spinner->ControlRotationEnd();
}

bool SpinRotation::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
