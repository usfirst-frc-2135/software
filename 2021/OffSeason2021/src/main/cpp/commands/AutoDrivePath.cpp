// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "commands/AutoDrivePath.h"

#include <spdlog/spdlog.h>

AutoDrivePath::AutoDrivePath(const char *pathName, Drivetrain *m_drivetrain) :
    m_pathName(pathName),
    m_drivetrain(m_drivetrain)
{
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("AutoDrivePath");
    AddRequirements(m_drivetrain);
}

// Called just before this Command runs the first time
void AutoDrivePath::Initialize()
{
    spdlog::info("AutoDrivePath - Init: pathName: {}", m_pathName);
    m_drivetrain->RamseteFollowerInit(m_pathName);
}

// Called repeatedly when this Command is scheduled to run
void AutoDrivePath::Execute()
{
    m_drivetrain->RamseteFollowerExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrivePath::IsFinished()
{
    return m_drivetrain->RamseteFollowerIsFinished();
}

// Called once after isFinished returns true
void AutoDrivePath::End(bool interrupted)
{
    m_drivetrain->RamseteFollowerEnd();
}

bool AutoDrivePath::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
