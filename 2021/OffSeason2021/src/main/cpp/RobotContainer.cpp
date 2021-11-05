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

#include "commands/ClimberRun.h"
#include "frc2135/AxisButton.h"

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
    frc::SmartDashboard::PutData("Climber Run: CLDIR_STOP", new ClimberBrake(true));
    frc::SmartDashboard::PutData("Climber Run: CLDIR_RUNNING", new ClimberBrake(false));
    frc::SmartDashboard::PutData("Climber Run: CLDIR_RUN", new ClimberRun(&m_climber));
    frc::SmartDashboard::PutData("Shooter Aim: LIGHT_ON", new ShooterAim(true));
    frc::SmartDashboard::PutData("Shooter Aim: LIGHT_OFF", new ShooterAim(false));
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
    frc::SmartDashboard::PutData(
        "Auto Drive Path: driveForward",
        new AutoDrivePath("driveForward", &m_drivetrain));
    frc::SmartDashboard::PutData(
        "Auto Drive Path: driveBackward",
        new AutoDrivePath("driveBackward", &m_drivetrain));
    frc::SmartDashboard::PutData(
        "Auto Drive Path: testTurnRight90deg",
        new AutoDrivePath("testTurnRight90deg", &m_drivetrain));
    frc::SmartDashboard::PutData(
        "Auto Drive Path: testTurnLeft90deg",
        new AutoDrivePath("testTurnLeft90deg", &m_drivetrain));
    frc::SmartDashboard::PutData(
        "Auto Drive Path: simCurvePath",
        new AutoDrivePath("simCurvePath", &m_drivetrain));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_STOP", new IntakeRun(0, &m_intake));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_ACQUIRE", new IntakeRun(1, &m_intake));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_EXPEL", new IntakeRun(-1, &m_intake));
    frc::SmartDashboard::PutData("Intake Deploy: INTAKE_EXTEND", new IntakeDeploy(true));
    frc::SmartDashboard::PutData("Intake Deploy: INTAKE_STOW", new IntakeDeploy(false));
    frc::SmartDashboard::PutData("Auto Drive Stop", new AutoDriveStop(&m_drivetrain));
    frc::SmartDashboard::PutData(
        "Auto Shoot Trench Left",
        new AutoShootTrenchLeft(&m_drivetrain, &m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter));
    frc::SmartDashboard::PutData(
        "Auto Shoot Trench Right",
        new AutoShootTrenchRight(
            &m_drivetrain,
            &m_intake,
            &m_floorConveyor,
            &m_verticalConveyor,
            &m_shooter));
    frc::SmartDashboard::PutData(
        "Auto Drive Shoot",
        new AutoDriveShoot(&m_drivetrain, &m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter));
    frc::SmartDashboard::PutData("Auto Path Sequence", new AutoPathSequence(&m_drivetrain));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=SMARTDASHBOARD

    frc::SmartDashboard::PutData("Limelight Drive", new DriveLimelight(false, &m_drivetrain, &m_vision));
    frc::SmartDashboard::PutData(
        "Intaking Action",
        new IntakingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor));
    frc::SmartDashboard::PutData(
        "Intaking Stop",
        new IntakingStop(&m_intake, &m_floorConveyor, &m_verticalConveyor));
    frc::SmartDashboard::PutData(
        "Exhausting Action",
        new ExhaustingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor));
    frc::SmartDashboard::PutData(
        "Exhausting Stop",
        new ExhaustingStop(&m_intake, &m_floorConveyor, &m_verticalConveyor));
    frc::SmartDashboard::PutData(
        "Scoring Action",
        new ScoringAction(&m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter));
    frc::SmartDashboard::PutData(
        "Scoring Stop",
        new ScoringStop(&m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter));
    frc::SmartDashboard::PutData("LED Set", new LEDSet(&m_led));
    frc::SmartDashboard::PutData("AUTO Calibrate Gyro", new CalibrateGyro(&m_drivetrain));

    ConfigureButtonBindings();

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT-COMMANDS
    m_drivetrain.SetDefaultCommand(DriveTeleop(&m_drivetrain));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT-COMMANDS

    m_climber.SetDefaultCommand(ClimberRun(&m_climber));

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

    m_chooser.AddOption("Auto Drive Stop", new AutoDriveStop(&m_drivetrain));
    m_chooser.AddOption(
        "Auto Shoot Trench Left",
        new AutoShootTrenchLeft(&m_drivetrain, &m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter));
    m_chooser.AddOption(
        "Auto Shoot Trench Right",
        new AutoShootTrenchRight(
            &m_drivetrain,
            &m_intake,
            &m_floorConveyor,
            &m_verticalConveyor,
            &m_shooter));
    m_chooser.AddOption(
        "Auto Drive Shoot",
        new AutoDriveShoot(&m_drivetrain, &m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter));
    m_chooser.AddOption(
        "Auto Drive LL Shoot",
        new AutoDriveLimelightShoot(
            &m_drivetrain,
            &m_intake,
            &m_floorConveyor,
            &m_verticalConveyor,
            &m_shooter,
            &m_vision));

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

//  axes: kLeftX = 0, kLeftY = 1, kLeftTrigger = 2, kRightTrigger = 3, kRightX = 4, kRightY = 5
//  btns: kA = 1, kB = 2, kX = 3, kY = 4, kBumperLeft = 5, kBumperRight = 6
//  btns: kBack = 7, kStart = 8, kStickLeft = 9, kStickRight = 10

void RobotContainer::ConfigureButtonBindings()
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=BUTTONS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=BUTTONS

    // Driver Controller Assignments
    frc2::JoystickButton m_quickturn{ &m_driverController, (int)frc::XboxController::Button::kA };
    frc2::JoystickButton m_intakingDr{ &m_driverController, (int)frc::XboxController::Button::kBumperLeft };
    frc2::JoystickButton m_shootingDr{ &m_driverController, (int)frc::XboxController::Button::kBumperRight };
    frc2::JoystickButton m_shooterAimOnDr{ &m_driverController, (int)frc::XboxController::Button::kStart };
    frc2::JoystickButton m_shooterAimOffDr{ &m_driverController, (int)frc::XboxController::Button::kBack };

    // Driver - A, B, X, Y
    m_quickturn.WhileHeld(DriveQuickturn(), true);

    // Driver Bumpers
    m_intakingDr.WhenPressed(IntakingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor), true);
    m_intakingDr.WhenReleased(IntakingStop(&m_intake, &m_floorConveyor, &m_verticalConveyor), true);

    m_shootingDr.WhenPressed(
        ScoringAction(&m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter),
        true);
    m_shootingDr.WhenReleased(
        ScoringStop(&m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter),
        true);

    // Triggers EXAMPLE ONLY: FIXME WITH CORRECT COMMANDS!
    frc2135::AxisButton m_leftTriggerDr(&m_driverController, (int)frc::XboxController::Axis::kLeftTrigger);
    m_leftTriggerDr.WhenPressed(ShooterAim(true), true);
    m_leftTriggerDr.WhenReleased(ShooterAim(false), true);

    // Driver Trigger for Limelight Mode
    frc2135::AxisButton m_rightTriggerDr(&m_driverController, (int)frc::XboxController::Axis::kRightTrigger);
    m_rightTriggerDr.WhileHeld(DriveLimelightShoot(
        &m_drivetrain,
        &m_intake,
        &m_floorConveyor,
        &m_verticalConveyor,
        &m_shooter,
        &m_vision));
    m_rightTriggerDr.WhenReleased(
        ScoringStop(&m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter),
        true);

    // Start/back
    m_shooterAimOnDr.WhenPressed(ShooterAim(true), true);
    m_shooterAimOffDr.WhenPressed(ShooterAim(false), true);

    // Operator Controller Assignments
    frc2::JoystickButton m_inStowOp{ &m_operatorController, (int)frc::XboxController::Button::kA };
    frc2::JoystickButton m_exhaustingOp{ &m_operatorController, (int)frc::XboxController::Button::kB };
    frc2::JoystickButton m_scoringOffOp{ &m_operatorController, (int)frc::XboxController::Button::kX };
    frc2::JoystickButton m_inDeployOp{ &m_operatorController, (int)frc::XboxController::Button::kY };
    frc2::JoystickButton m_intakingOp{ &m_operatorController, (int)frc::XboxController::Button::kBumperLeft };
    frc2::JoystickButton m_scoringPrimeOp{ &m_operatorController,
                                           (int)frc::XboxController::Button::kBumperRight };
    frc2::JoystickButton m_shooterAimOnOp{ &m_operatorController, (int)frc::XboxController::Button::kStart };
    frc2::JoystickButton m_shooterAimOffOp{ &m_operatorController, (int)frc::XboxController::Button::kBack };

    // Operator - A, B, X, Y
    m_inStowOp.WhenPressed(IntakeDeploy(false), true);
    m_exhaustingOp.WhenPressed(ExhaustingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor), true);
    m_exhaustingOp.WhenReleased(ExhaustingStop(&m_intake, &m_floorConveyor, &m_verticalConveyor), true);
    m_inDeployOp.WhenPressed(IntakeDeploy(true), true);

    // Operator Bumpers
    m_intakingOp.WhenPressed(IntakingAction(&m_intake, &m_floorConveyor, &m_verticalConveyor), true);
    m_intakingOp.WhenReleased(IntakingStop(&m_intake, &m_floorConveyor, &m_verticalConveyor), true);

    m_scoringPrimeOp.WhenPressed(ScoringPrime(&m_shooter), true);
    m_scoringOffOp.WhenPressed(
        ScoringStop(&m_intake, &m_floorConveyor, &m_verticalConveyor, &m_shooter),
        true);

    // Start/back
    m_shooterAimOnOp.WhenPressed(ShooterAim(true), true);
    ;
    m_shooterAimOffOp.WhenPressed(ShooterAim(false), true);
    ;
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
