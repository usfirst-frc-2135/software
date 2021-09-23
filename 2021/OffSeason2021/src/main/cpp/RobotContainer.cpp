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

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/ParallelRaceGroup.h>

RobotContainer *RobotContainer::m_robotContainer = NULL;

RobotContainer::RobotContainer() :
    m_autonomousCommand(
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
        &m_drivetrain)
{
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=SMARTDASHBOARD
    // Smartdashboard Subsystems

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Climber Brake: CLIMBER_RUNNING", new ClimberBrake(false));
    frc::SmartDashboard::PutData("Climber Brake: CLIMBER_STOP", new ClimberBrake(true));
    frc::SmartDashboard::PutData("Climber Run: CLDIR_STOP", new ClimberRun(0, &m_climber));
    frc::SmartDashboard::PutData("Climber Run: CLDIR_UP", new ClimberRun(1, &m_climber));
    frc::SmartDashboard::PutData("Climber Run: CLDIR_DOWN", new ClimberRun(-1, &m_climber));
    frc::SmartDashboard::PutData("Shooter Aim: LIGHT_ON", new ShooterAim(true));
    frc::SmartDashboard::PutData("Shooter Aim: LIGHT_OFF", new ShooterAim(false));
    frc::SmartDashboard::PutData("Shooter At Speed", new ShooterAtSpeed());
    frc::SmartDashboard::PutData("Shooter Run: SHDIR_STOP", new ShooterRun(0, &m_shooter));
    frc::SmartDashboard::PutData("Shooter Run: SHDIR_SHOOT", new ShooterRun(1, &m_shooter));
    frc::SmartDashboard::PutData(
        "Vertical Conveyor Run: VCONDIR_STOP",
        new VerticalConveyorRun(0, &m_verticalConveyor));
    frc::SmartDashboard::PutData(
        "Vertical Conveyor Run: VCONDIR_ACQUIRE",
        new VerticalConveyorRun(1, &m_verticalConveyor));
    frc::SmartDashboard::PutData(
        "Vertical Conveyor Run: VCONDIR_EXPEL",
        new VerticalConveyorRun(-1, &m_verticalConveyor));
    frc::SmartDashboard::PutData(
        "Floor Conveyor Run: FCONDIR_STOP",
        new FloorConveyorRun(0, &m_floorConveyor));
    frc::SmartDashboard::PutData(
        "Floor Conveyor Run: FCONDIR_ACQUIRE",
        new FloorConveyorRun(1, &m_floorConveyor));
    frc::SmartDashboard::PutData(
        "Floor Conveyor Run: FCONDIR_EXPEL",
        new FloorConveyorRun(-1, &m_floorConveyor));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_STOP", new IntakeRun(0, &m_intake));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_ACQUIRE", new IntakeRun(1, &m_intake));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_EXPEL", new IntakeRun(-1, &m_intake));
    frc::SmartDashboard::PutData("Intake Deploy: INTAKE_STOW", new IntakeDeploy(true));
    frc::SmartDashboard::PutData("Intake Deploy: INTAKE_EXPEL", new IntakeDeploy(false));
    frc::SmartDashboard::PutData("Auto Drive Stop", new AutoDriveStop(&m_drivetrain));
    frc::SmartDashboard::PutData("Auto Shoot Trench Left", new AutoShootTrenchLeft());
    frc::SmartDashboard::PutData("Auto Shoot Trench Right", new AutoShootTrenchRight());
    frc::SmartDashboard::PutData("Auto Drive Shoot", new AutoDriveShoot());
    frc::SmartDashboard::PutData("Auto Drive Path", new AutoDrivePath());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=SMARTDASHBOARD

    frc::SmartDashboard::PutData(
        "Intake Action",
        new IntakingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor));
    frc::SmartDashboard::PutData(
        "Shoot Action",
        new ShootingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter));

    ConfigureButtonBindings();

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT-COMMANDS
    m_drivetrain.SetDefaultCommand(DriveTeleop(&m_drivetrain));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT-COMMANDS

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

    m_chooser.AddOption("Auto Drive Stop", new AutoDriveStop(&m_drivetrain));
    m_chooser.AddOption("Auto Shoot Trench Left", new AutoShootTrenchLeft());
    m_chooser.AddOption("Auto Shoot Trench Right", new AutoShootTrenchRight());
    m_chooser.AddOption("Auto Drive Shoot", new AutoDriveShoot());
    m_chooser.AddOption("Auto Drive Path", new AutoDrivePath());

    m_chooser.SetDefaultOption("Auto Drive Stop", new AutoDriveStop(&m_drivetrain));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

    frc::SmartDashboard::PutData("Auto Mode", &m_chooser);
}

RobotContainer *RobotContainer::GetInstance()
{
    if (m_robotContainer == NULL)
    {
        m_robotContainer = new RobotContainer();
    }
    return (m_robotContainer);
}

void RobotContainer::ConfigureButtonBindings()
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=BUTTONS

    frc2::JoystickButton m_quickturn{ &m_driverController, (int)frc::XboxController::Button::kA };

    m_quickturn.WhileHeld(DriveQuickturn(&m_drivetrain), true);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=BUTTONS

    frc2::JoystickButton m_intaking{ &m_driverController, (int)frc::XboxController::Button::kBumperLeft };
    frc2::JoystickButton m_shooting{ &m_driverController, (int)frc::XboxController::Button::kBumperRight };

    m_intaking.WhenPressed(IntakingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor), true);
    m_shooting.WhenPressed(
        ShootingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter),
        true);
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

frc::XboxController *RobotContainer::getDriverController()
{
    return &m_driverController;
}
frc::XboxController *RobotContainer::getOperatorController()
{
    return &m_operatorController;
}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

frc2::Command *RobotContainer::GetAutonomousCommand()
{
    // The selected command will be run in autonomous
    return m_chooser.GetSelected();
}
