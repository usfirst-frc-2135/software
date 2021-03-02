// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <frc/smartdashboard/SmartDashboard.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/SpinColor.h"

SpinColor::SpinColor(Spinner *m_spinner) : m_spinner(m_spinner)
{
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("SpinColor");
    AddRequirements(m_spinner);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
}

// Called just before this Command runs the first time
void SpinColor::Initialize()
{
    std::printf("2135: SpinColor - Init\n");
    m_spinner->ControlPositionInit(frc::SmartDashboard::GetString("Color Setpoint", "Unknown"));
}

// Called repeatedly when this Command is scheduled to run
void SpinColor::Execute()
{
    m_spinner->ControlPositionExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool SpinColor::IsFinished()
{
    return m_spinner->ControlPositionIsFinished();
}

// Called once after isFinished returns true
void SpinColor::End(bool interrupted)
{
    std::printf("2135: SpinColor - End\n");
    m_spinner->ControlPositionEnd();
}

bool SpinColor::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
