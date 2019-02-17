// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "frc/smartdashboard/SmartDashboard.h"
#include "Commands/ArmRun.h"
#include "Commands/AutoDriveDist.h"
#include "Commands/AutoDriveTurn.h"
#include "Commands/AutoPos1Level1Ship.h"
#include "Commands/AutoPos1Level2Ship.h"
#include "Commands/AutoPos2Level1Ship.h"
#include "Commands/AutoPos3Level1Ship.h"
#include "Commands/AutoPos3Level2Ship.h"
#include "Commands/AutoPosANYMove.h"
#include "Commands/AutoStop.h"
#include "Commands/DriveShift.h"
#include "Commands/DriveTeleop.h"
#include "Commands/ElbowBump.h"
#include "Commands/ElbowRun.h"
#include "Commands/ElevatorBump.h"
#include "Commands/ElevatorRun.h"
#include "Commands/GPShift.h"
#include "Commands/IntakeDelivery.h"
#include "Commands/IntakeRun.h"
#include "Commands/LifterBackExtend.h"
#include "Commands/LifterExtend.h"
#include "Commands/LifterFrontExtend.h"
#include "Commands/LifterMotorRun.h"
#include "Commands/WristBump.h"
#include "Commands/WristRun.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    controlBoard.reset(new frc::Joystick(1));
    
    wristBumpDown.reset(new frc::JoystickButton(controlBoard.get(), 9));
    wristBumpDown->WhileHeld(new WristBump(false));
    wristBumpUp.reset(new frc::JoystickButton(controlBoard.get(), 8));
    wristBumpUp->WhileHeld(new WristBump(false));
    ebowBumpDown.reset(new frc::JoystickButton(controlBoard.get(), 7));
    ebowBumpDown->WhileHeld(new ElbowBump(false));
    elbowBumpUp.reset(new frc::JoystickButton(controlBoard.get(), 6));
    elbowBumpUp->WhileHeld(new ElbowBump(false));
    elevatorBumpDown.reset(new frc::JoystickButton(controlBoard.get(), 5));
    elevatorBumpDown->WhileHeld(new ElevatorBump(false));
    gPShifter.reset(new frc::JoystickButton(controlBoard.get(), 3));
    gPShifter->WhileHeld(new GPShift(true));
    elevatorBumpUp.reset(new frc::JoystickButton(controlBoard.get(), 4));
    elevatorBumpUp->WhileHeld(new ElevatorBump(false));
    intakePanelDeliver.reset(new frc::JoystickButton(controlBoard.get(), 2));
    intakePanelDeliver->WhileHeld(new IntakeDelivery(true));
    intakeAcquire.reset(new frc::JoystickButton(controlBoard.get(), 1));
    intakeAcquire->WhileHeld(new IntakeRun(1));
    dStick.reset(new frc::Joystick(0));
    
    lifterDeploy.reset(new frc::JoystickButton(dStick.get(), 7));
    lifterDeploy->WhenPressed(new LifterExtend());
    lifterBackRetract.reset(new frc::JoystickButton(dStick.get(), 6));
    lifterBackRetract->WhenPressed(new LifterBackExtend(false));
    lifterFrontRetract.reset(new frc::JoystickButton(dStick.get(), 5));
    lifterFrontRetract->WhenPressed(new LifterFrontExtend(false));
    shiftSpeed.reset(new frc::JoystickButton(dStick.get(), 1));
    shiftSpeed->WhileHeld(new DriveShift(false));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Arm Run", new ArmRun());
    frc::SmartDashboard::PutData("Wrist Bump: UP", new WristBump(true));
    frc::SmartDashboard::PutData("Wrist Bump: DOWN", new WristBump(false));
    frc::SmartDashboard::PutData("Wrist Run: GROUND", new WristRun(0));
    frc::SmartDashboard::PutData("Wrist Run: STOWED", new WristRun(1));
    frc::SmartDashboard::PutData("Wrist Run: DELIVERY", new WristRun(2));
    frc::SmartDashboard::PutData("Wrist Run: SMARTDASH", new WristRun(3));
    frc::SmartDashboard::PutData("Elbow Run: GROUND", new ElbowRun(0));
    frc::SmartDashboard::PutData("Elbow Run: STOWED", new ElbowRun(1));
    frc::SmartDashboard::PutData("Elbow Run: DELIVERY", new ElbowRun(2));
    frc::SmartDashboard::PutData("Elbow Run: SMARTDASH", new ElbowRun(3));
    frc::SmartDashboard::PutData("Elevator Bump: UP", new ElevatorBump(true));
    frc::SmartDashboard::PutData("Elevator Bump: DOWN", new ElevatorBump(false));
    frc::SmartDashboard::PutData("Elbow Bump: UP", new ElbowBump(true));
    frc::SmartDashboard::PutData("Elbow Bump: DOWN", new ElbowBump(false));
    frc::SmartDashboard::PutData("Auto Pos 3 Level 2 Ship", new AutoPos3Level2Ship());
    frc::SmartDashboard::PutData("Auto Pos 1 Level 2 Ship", new AutoPos1Level2Ship());
    frc::SmartDashboard::PutData("Auto Pos 3 Level 1 Ship", new AutoPos3Level1Ship());
    frc::SmartDashboard::PutData("Auto Pos 2 Level 1 Ship", new AutoPos2Level1Ship());
    frc::SmartDashboard::PutData("Auto Pos 1 Level 1 Ship", new AutoPos1Level1Ship());
    frc::SmartDashboard::PutData("Auto Pos ANY Move", new AutoPosANYMove());
    frc::SmartDashboard::PutData("Auto Drive Turn: DEFAULT", new AutoDriveTurn(0));
    frc::SmartDashboard::PutData("Auto Drive Dist: DEFAULT", new AutoDriveDist(0));
    frc::SmartDashboard::PutData("Auto Stop", new AutoStop());

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
