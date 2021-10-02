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

#include <spdlog/spdlog.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/ShooterRun.h"

ShooterRun::ShooterRun(bool lightOn, int shooterState, Shooter *m_shooter) :
    m_lightOn(lightOn),
    m_shooterState(shooterState),
    m_shooter(m_shooter)
{
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("ShooterRun");
    AddRequirements(m_shooter);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
}

// Called just before this Command runs the first time
void ShooterRun::Initialize()
{
    spdlog::info("ShooterRun - Init {}", m_shooterState);
    m_shooter->SetShooterSpeed(m_shooterState);
    RobotContainer *robotContainer = RobotContainer::GetInstance();
    robotContainer->m_shooter.FlashlightOn(m_lightOn);
}

// Called repeatedly when this Command is scheduled to run
void ShooterRun::Execute() {}

// Make this return true when this Command no longer needs to run execute()
bool ShooterRun::IsFinished()
{
    return m_shooter->AtDesiredRPM();
}

// Called once after isFinished returns true
void ShooterRun::End(bool interrupted)
{
    spdlog::info("ShooterRun - End");
}

bool ShooterRun::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
