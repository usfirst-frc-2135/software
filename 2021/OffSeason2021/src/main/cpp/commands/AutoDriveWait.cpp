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
#include <spdlog/spdlog.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/AutoDriveWait.h"

AutoDriveWait::AutoDriveWait(Drivetrain *m_drivetrain) : m_drivetrain(m_drivetrain)
{
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("AutoDriveWait");
    AddRequirements(m_drivetrain);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
}

// Called just before this Command runs the first time
void AutoDriveWait::Initialize()
{
    spdlog::info("AutoDriveWait - Init");

    m_waitTime = frc::SmartDashboard::GetNumber("AUTO_WaitTime", 0.0);
    spdlog::info("AutoDriveWait - Waiting {} seconds", m_waitTime);

    m_timer.Reset();
    m_timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveWait::Execute()
{
    m_drivetrain->MoveStop();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveWait::IsFinished()
{
    return m_timer.HasElapsed(m_waitTime * 1_s);
}

// Called once after isFinished returns true
void AutoDriveWait::End(bool interrupted)
{
    spdlog::info("AutoDriveWait - End");
    m_timer.Stop();
}

bool AutoDriveWait::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
