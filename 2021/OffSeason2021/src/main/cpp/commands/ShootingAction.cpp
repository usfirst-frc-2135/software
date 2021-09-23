// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "commands/ShootingAction.h"

#include <spdlog/spdlog.h>

ShootingAction::ShootingAction(
    Intake *intake,
    FloorConveyor *fConv,
    VerticalConveyor *vConv,
    Shooter *shooter)
{
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("ShootingAction");

    spdlog::info("ShootingAction");

    // Add your commands here, e.g.
    // AddCommands(FooCommand(), BarCommand());
    // Need to add if Shooter is at speed part, turning on flashlight part

    AddCommands(
        IntakeRun(Intake::INTAKE_ACQUIRE, intake),
        FloorConveyorRun(FloorConveyor::FCONVEYOR_ACQUIRE, fConv),
        VerticalConveyorRun(VerticalConveyor::VCONVEYOR_ACQUIRE, vConv),
        ShooterRun(Shooter::SHOOTERSPEED_FORWARD, shooter));
}

bool ShootingAction::RunsWhenDisabled() const
{
    return false;
}