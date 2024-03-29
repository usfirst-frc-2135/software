// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#pragma once

#include "commands/FloorConveyorRun.h"
#include "commands/IntakeRun.h"
#include "commands/ShooterAim.h"
#include "commands/ShooterRun.h"
#include "commands/VerticalConveyorRun.h"

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/ParallelCommandGroup.h>

/**
 *
 *
 * @author ExampleAuthor
 */
class ScoringStop : public frc2::CommandHelper<frc2::ParallelCommandGroup, ScoringStop>
{
public:
    explicit ScoringStop(Intake *intake, FloorConveyor *fConv, VerticalConveyor *vConv, Shooter *shooter);

    bool RunsWhenDisabled() const override;

private:
};
