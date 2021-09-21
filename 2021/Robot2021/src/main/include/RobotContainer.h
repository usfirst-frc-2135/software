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

#include <frc2/command/button/JoystickButton.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "commands/AutoDriveDist.h"
#include "commands/AutoDrivePath.h"
#include "commands/AutoDriveStop.h"
#include "commands/AutoPathSequenceTest.h"
#include "commands/AutoShootDrive.h"
#include "commands/ClimberDeploy.h"
#include "commands/ClimberRun.h"
#include "commands/ConveyorRun.h"
#include "commands/DriveAlignTurn.h"
#include "commands/DriveModeToggle.h"
#include "commands/DriveQuickTurn.h"
#include "commands/DriveReset.h"
#include "commands/DriveTeleop.h"
#include "commands/IndexerDeploy.h"
#include "commands/IntakeDeploy.h"
#include "commands/IntakeRun.h"
#include "commands/LEDSet.h"
#include "commands/ShooterRun.h"
#include "commands/SpinColor.h"
#include "commands/SpinRotation.h"
#include "subsystems/Climber.h"
#include "subsystems/Conveyor.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Led.h"
#include "subsystems/Pneumatics.h"
#include "subsystems/Power.h"
#include "subsystems/Shooter.h"
#include "subsystems/Spinner.h"
#include "subsystems/Vision.h"

#include <frc/XboxController.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/Command.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

class RobotContainer
{
public:
    frc2::Command *GetAutonomousCommand();
    static RobotContainer *GetInstance();

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
    // The robot's subsystems
    Vision m_vision;
    Power m_power;
    Pneumatics m_pneumatics;
    Led m_led;
    Climber m_climber;
    Spinner m_spinner;
    Shooter m_shooter;
    Conveyor m_conveyor;
    Intake m_intake;
    Drivetrain m_drivetrain;

    frc::XboxController *getDriverPad();
    frc::XboxController *getOperatorPad();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

private:
    RobotContainer();

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    // Joysticks
    frc::XboxController m_operatorPad{ 1 };
    frc::XboxController m_driverPad{ 0 };

    frc::SendableChooser<frc2::Command *> m_chooser;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    AutoDriveStop m_autonomousCommand;
    static RobotContainer *m_robotContainer;

    void ConfigureButtonBindings();
};
