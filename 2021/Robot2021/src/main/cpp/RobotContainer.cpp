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
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>



RobotContainer* RobotContainer::m_robotContainer = NULL;

RobotContainer::RobotContainer() : m_autonomousCommand(
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
&m_drivetrain){



    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=SMARTDASHBOARD
    // Smartdashboard Subsystems


    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Auto Drive Dist: DEFAULT", new AutoDriveDist(0, &m_drivetrain));
    frc::SmartDashboard::PutData("Auto Drive Path", new AutoDrivePath( &m_drivetrain ));
    frc::SmartDashboard::PutData("Auto Shoot Drive", new AutoShootDrive( &m_shooter ));
    frc::SmartDashboard::PutData("Auto Stop", new AutoStop( &m_drivetrain ));
    frc::SmartDashboard::PutData("Climber Deploy: CLIMBER_STOW", new ClimberDeploy(false, &m_climber));
    frc::SmartDashboard::PutData("Climber Deploy: CLIMBER_DEPLOY", new ClimberDeploy(true, &m_climber));
    frc::SmartDashboard::PutData("Climber Run: CLIMBERDIR_UP", new ClimberRun(1, &m_climber));
    frc::SmartDashboard::PutData("Climber Run: CLIMBERDIR_DOWN", new ClimberRun(-1, &m_climber));
    frc::SmartDashboard::PutData("Climber Run: CLIMBERDIR_STOP", new ClimberRun(0, &m_climber));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYORDIRECTION_STOP", new ConveyorRun(0, &m_conveyor));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYORDIRECTION_UP", new ConveyorRun(1, &m_conveyor));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYORDIRECTION_DOWN", new ConveyorRun(-1, &m_conveyor));
    frc::SmartDashboard::PutData("Drive Align Turn", new DriveAlignTurn( &m_drivetrain ));
    frc::SmartDashboard::PutData("Drive Bump Ramp: BUMP_UP", new DriveBumpRamp(true, &m_drivetrain));
    frc::SmartDashboard::PutData("Drive Bump Ramp: BUMP_DOWN", new DriveBumpRamp(false, &m_drivetrain));
    frc::SmartDashboard::PutData("Drive Mode Toggle", new DriveModeToggle( &m_drivetrain ));
    frc::SmartDashboard::PutData("Drive Quick Turn", new DriveQuickTurn( &m_drivetrain ));
    frc::SmartDashboard::PutData("Drive Reset", new DriveReset( &m_drivetrain ));
    frc::SmartDashboard::PutData("Drive Shift: GEARSETTING_LOW", new DriveShift(false, &m_drivetrain));
    frc::SmartDashboard::PutData("Drive Shift: GEARSETTING_HIGH", new DriveShift(true, &m_drivetrain));
    frc::SmartDashboard::PutData("Indexer Deploy: INDEXER_CLOSE", new IndexerDeploy(false, &m_shooter));
    frc::SmartDashboard::PutData("Indexer Deploy: INDEXER_OPEN", new IndexerDeploy(true, &m_shooter));
    frc::SmartDashboard::PutData("Intake Deploy: INTAKE_DEPLOY", new IntakeDeploy(true, &m_intake));
    frc::SmartDashboard::PutData("Intake Deploy: INTAKE_STOW", new IntakeDeploy(false, &m_intake));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_STOP", new IntakeRun(0, &m_intake));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_ACQUIRE", new IntakeRun(1, &m_intake));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_EXPEL", new IntakeRun(-1, &m_intake));
    frc::SmartDashboard::PutData("LED Set", new LEDSet( &m_led ));
    frc::SmartDashboard::PutData("Shooter Run: SHOOTERSPEED_REVERSE", new ShooterRun(-1, &m_shooter));
    frc::SmartDashboard::PutData("Shooter Run: SHOOTERSPEED_STOP", new ShooterRun(0, &m_shooter));
    frc::SmartDashboard::PutData("Shooter Run: SHOOTERSPEED_FORWARD", new ShooterRun(1, &m_shooter));
    frc::SmartDashboard::PutData("Spin Color", new SpinColor( &m_spinner ));
    frc::SmartDashboard::PutData("Spin Rotation", new SpinRotation( &m_spinner ));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=SMARTDASHBOARD

    ConfigureButtonBindings();

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT-COMMANDS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT-COMMANDS

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS


    m_chooser.SetDefaultOption("Auto Stop", new AutoStop( &m_drivetrain ));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

    frc::SmartDashboard::PutData("Auto Mode", &m_chooser);

}

RobotContainer* RobotContainer::GetInstance()
{
    if (m_robotContainer == NULL) {
        m_robotContainer = new RobotContainer();
    }
    return(m_robotContainer);
}



void RobotContainer::ConfigureButtonBindings()
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=BUTTONS

frc2::JoystickButton m_shFire{&m_operatorPad, 2};
frc2::JoystickButton m_shRun{&m_operatorPad, 6};
frc2::JoystickButton m_clAscend{&m_driverPad, 1};
frc2::JoystickButton m_clDeploy{&m_driverPad, 4};
frc2::JoystickButton m_dtAlignTurn{&m_driverPad, 6};
frc2::JoystickButton m_dtQuickTurn{&m_driverPad, 5};

m_shFire.WhenPressed(IndexerDeploy(false, &m_shooter), true);
m_shRun.WhileHeld(ShooterRun(0, &m_shooter), true);
m_clAscend.WhileHeld(ClimberRun(0, &m_climber), true);
m_clDeploy.WhenPressed(ClimberDeploy(false, &m_climber), true);
m_dtAlignTurn.WhenPressed(DriveAlignTurn( &m_drivetrain ), true);
m_dtQuickTurn.WhenPressed(DriveQuickTurn( &m_drivetrain ), true);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=BUTTONS

    //shFire is B
    //shRun is RightBumper
    //clAscend is A
    //clDeploy is Y
    //dtAlignTurn is RightBumper
    //dtQuickTurn is LeftBumper

    //not defined in RobotBuilder

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

frc::XboxController* RobotContainer::getOperatorPad() {
   return &m_operatorPad;
}
frc::XboxController* RobotContainer::getDriverPad() {
   return &m_driverPad;
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS


frc2::Command* RobotContainer::GetAutonomousCommand()
{
  // The selected command will be run in autonomous
  return m_chooser.GetSelected();
}
