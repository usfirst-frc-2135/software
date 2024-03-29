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

#include "commands/ExhaustingAction.h"
#include "commands/ExhaustingStop.h"
#include "commands/IntakingAction.h"
#include "commands/IntakingStop.h"
#include "commands/ScoringAction.h"
#include "commands/ScoringStop.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "commands/AutoDrivePath.h"
#include "commands/AutoDriveShoot.h"
#include "commands/AutoDriveStop.h"
#include "commands/AutoPathSequence.h"
#include "commands/AutoShootTrenchLeft.h"
#include "commands/AutoShootTrenchRight.h"
#include "commands/ClimberBrake.h"
#include "commands/ClimberRun.h"
#include "commands/DriveQuickturn.h"
#include "commands/DriveTeleop.h"
#include "commands/FloorConveyorRun.h"
#include "commands/IntakeDeploy.h"
#include "commands/IntakeRun.h"
#include "commands/ScoringPrime.h"
#include "commands/ShooterAim.h"
#include "commands/ShooterRun.h"
#include "commands/VerticalConveyorRun.h"
#include "subsystems/Climber.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/FloorConveyor.h"
#include "subsystems/Intake.h"
#include "subsystems/LED.h"
#include "subsystems/Pneumatics.h"
#include "subsystems/Power.h"
#include "subsystems/Shooter.h"
#include "subsystems/VerticalConveyor.h"
#include "subsystems/Vision.h"

#include <frc/XboxController.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/Command.h>
#include <frc2/command/button/JoystickButton.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

class RobotContainer
{
public:
    frc2::Command *GetAutonomousCommand();
    static RobotContainer *GetInstance();

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
    // The robot's subsystems
    Drivetrain m_drivetrain;
    Intake m_intake;
    FloorConveyor m_floorConveyor;
    VerticalConveyor m_verticalConveyor;
    Shooter m_shooter;
    Climber m_climber;
    Pneumatics m_pneumatics;
    Power m_power;
    Vision m_vision;
    LED m_lED;

    frc::XboxController *getOperatorController();
    frc::XboxController *getDriverController();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

private:
    RobotContainer();

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    // Joysticks
    frc::XboxController m_driverController{ 0 };
    frc::XboxController m_operatorController{ 1 };

    frc::SendableChooser<frc2::Command *> m_chooser;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    AutoDriveStop m_autonomousCommand;
    static RobotContainer *m_robotContainer;

    void ConfigureButtonBindings();
};
