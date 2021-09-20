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
#include "frc2135/RobotConfig.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/AutoPathSequenceTest.h"

AutoPathSequenceTest::AutoPathSequenceTest(Drivetrain *drivetrain)
{
    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("AutoPathSequenceTest");

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
    // Add your commands here, e.g.
    // AddCommands(FooCommand(), BarCommand());
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsString("path1", path1, "driveForward");
    config->GetValueAsString("path2", path2, "driveForward");
    config->GetValueAsString("path3", path3, "driveForward");

    AddCommands(
        AutoDrivePath(path1.c_str(), drivetrain),
        AutoDrivePath(path2.c_str(), drivetrain)
        // AutoDrivePath(path3.c_str(), drivetrain)
    );
}

bool AutoPathSequenceTest::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}