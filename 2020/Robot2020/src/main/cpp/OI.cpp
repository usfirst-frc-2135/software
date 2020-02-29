// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <OI.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "frc/smartdashboard/SmartDashboard.h"
#include "Commands/AutoDriveDist.h"
#include "Commands/AutoStop.h"
#include "Commands/ClimberRun.h"
#include "Commands/ConveyorRun.h"
#include "Commands/DriveAlignPIDTurn.h"
#include "Commands/DriveAlignTurn.h"
#include "Commands/DriveMode.h"
#include "Commands/DriveReset.h"
#include "Commands/DriveShift.h"
#include "Commands/DriveTeleop.h"
#include "Commands/IndexerSet.h"
#include "Commands/IntakeRun.h"
#include "Commands/LEDSet.h"
#include "Commands/ShooterRun.h"
#include "Commands/SpinColor.h"
#include "Commands/SpinRotation.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
controlBoard.reset(new frc::Joystick(1));

intakeExpel.reset(new frc::JoystickButton(controlBoard.get(), 10));
intakeExpel->WhenPressed(new IntakeRun(0));
intakeAquire.reset(new frc::JoystickButton(controlBoard.get(), 10));
intakeAquire->WhenPressed(new IntakeRun(0));
indexerToggle.reset(new frc::JoystickButton(controlBoard.get(), 9));
indexerToggle->WhenPressed(new IndexerSet(false));
conveyorOn.reset(new frc::JoystickButton(controlBoard.get(), 8));
conveyorOn->WhileHeld(new ConveyorRun(0));
shooterToggle.reset(new frc::JoystickButton(controlBoard.get(), 7));
shooterToggle->WhenPressed(new ShooterRun(0));
lEDToggle.reset(new frc::JoystickButton(controlBoard.get(), 5));
lEDToggle->WhenPressed(new LEDSet());
climberRetract.reset(new frc::JoystickButton(controlBoard.get(), 4));
climberRetract->WhenPressed(new ClimberRun());
climberExtend.reset(new frc::JoystickButton(controlBoard.get(), 3));
climberExtend->WhenPressed(new ClimberRun());
sPRotation.reset(new frc::JoystickButton(controlBoard.get(), 2));
sPRotation->WhenPressed(new SpinRotation());
sPColor.reset(new frc::JoystickButton(controlBoard.get(), 1));
sPColor->WhenPressed(new SpinColor());
dStick.reset(new frc::Joystick(0));

changeDriveMode.reset(new frc::JoystickButton(dStick.get(), 3));
changeDriveMode->WhenPressed(new DriveMode(3));
alignTurn.reset(new frc::JoystickButton(dStick.get(), 4));
alignTurn->WhenPressed(new DriveAlignTurn());
pIDAlignTurn.reset(new frc::JoystickButton(dStick.get(), 2));
pIDAlignTurn->WhenPressed(new DriveAlignPIDTurn(0));
shiftSpeed.reset(new frc::JoystickButton(dStick.get(), 1));
shiftSpeed->WhileHeld(new DriveShift(false));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Drive Mode: default", new DriveMode(3));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_STOP", new IntakeRun(0));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_FORWARD", new IntakeRun(1));
    frc::SmartDashboard::PutData("Intake Run: INTAKE_REVERSE", new IntakeRun(-1));
    frc::SmartDashboard::PutData("Indexer Set: INDEXER_ON", new IndexerSet(true));
    frc::SmartDashboard::PutData("Indexer Set: INDEXER_OFF", new IndexerSet(false));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYOR_STOP", new ConveyorRun(0));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYOR_UP", new ConveyorRun(1));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYOR_DOWN", new ConveyorRun(-1));
    frc::SmartDashboard::PutData("Conveyor Run: CONVEYOR_HOLD", new ConveyorRun(3));
    frc::SmartDashboard::PutData("LED Set", new LEDSet());
    frc::SmartDashboard::PutData("Climber Run", new ClimberRun());
    frc::SmartDashboard::PutData("Spin Rotation", new SpinRotation());
    frc::SmartDashboard::PutData("Spin Color", new SpinColor());
    frc::SmartDashboard::PutData("Shooter Run: REVERSE_SPEED", new ShooterRun(-1));
    frc::SmartDashboard::PutData("Shooter Run: STOP_SPEED", new ShooterRun(0));
    frc::SmartDashboard::PutData("Shooter Run: ON_SPEED", new ShooterRun(1));
    frc::SmartDashboard::PutData("Drive Align PID Turn: default", new DriveAlignPIDTurn(0.0));
    frc::SmartDashboard::PutData("Drive Align Turn", new DriveAlignTurn());
    frc::SmartDashboard::PutData("Drive Reset", new DriveReset());
    frc::SmartDashboard::PutData("Auto Drive Dist: DEFAULT", new AutoDriveDist(0));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

    // Additional joystick if using separate joysticks
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsBool("DT_SeparateJoysticks", m_separateJoysticks, false);
    if (m_separateJoysticks) {
        dStick2.reset(new frc::Joystick(2));
    }
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDStick() {
   return dStick;
}

std::shared_ptr<frc::Joystick> OI::getControlBoard() {
   return controlBoard;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

// Returns null pointer or additional joystick if using separate joysticks
std::shared_ptr<frc::Joystick> OI::getDStick2() {
   return ( (m_separateJoysticks) ? dStick2 : nullptr);
}
