// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "commands/ShootingStop.h"

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

ShootingStop::ShootingStop(Intake *intake, FloorConveyor *fConv, VerticalConveyor *vConv, Shooter *shooter)
{
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("ShootingStop");

    spdlog::info("ShootingStop");

    // Add your commands here, e.g.
    // AddCommands(FooCommand(), BarCommand());
    AddCommands(
        IntakeDeploy(true),
        IntakeRun(Intake::INTAKE_STOP, intake),
        FloorConveyorRun(FloorConveyor::FCONVEYOR_STOP, fConv),
        VerticalConveyorRun(VerticalConveyor::VCONVEYOR_STOP, vConv));
    //ShooterRun(Shooter::SHOOTER_STOP, shooter))
}

bool ShootingStop::RunsWhenDisabled() const
{
    return false;
}