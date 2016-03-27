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
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/ArmExtend.h"
#include "Commands/ArmMotorEnable.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/Climb.h"
#include "Commands/CompressorControl.h"
#include "Commands/DriveDistanceDelayed.h"
#include "Commands/DriveDistancePID.h"
#include "Commands/DriveDistanceTimed.h"
#include "Commands/DriveFast.h"
#include "Commands/DriveShiftHigh.h"
#include "Commands/DriveShiftLow.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTrainInvert.h"
#include "Commands/DriveWait.h"
#include "Commands/FireBoulder.h"
#include "Commands/IndexerMotorEnable.h"
#include "Commands/LoadShooter.h"
#include "Commands/Shoot.h"
#include "Commands/ShootFrameControl.h"
#include "Commands/ShootPresets.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    controlBoardB.reset(new Joystick(2));
    
    retractClimb.reset(new JoystickButton(controlBoardB.get(), 4));
    retractClimb->WhenPressed(new Climb(false));
    extendClimb.reset(new JoystickButton(controlBoardB.get(), 3));
    extendClimb->WhenPressed(new Climb(true));
    shootReverse.reset(new JoystickButton(controlBoardB.get(), 2));
    shootReverse->WhileHeld(new ShootPresets(4));
    fire.reset(new JoystickButton(controlBoardB.get(), 1));
    fire->WhileHeld(new FireBoulder());
    controlBoardA.reset(new Joystick(1));
    
    shootLow.reset(new JoystickButton(controlBoardA.get(), 11));
    shootLow->WhileHeld(new ShootPresets(3));
    shootHigh.reset(new JoystickButton(controlBoardA.get(), 10));
    shootHigh->WhileHeld(new ShootPresets(1));
    frameDown.reset(new JoystickButton(controlBoardA.get(), 9));
    frameDown->WhenPressed(new ShootFrameControl(false));
    frameUp.reset(new JoystickButton(controlBoardA.get(), 8));
    frameUp->WhenPressed(new ShootFrameControl(true));
    indexerExpel.reset(new JoystickButton(controlBoardA.get(), 6));
    indexerExpel->WhileHeld(new LoadShooter(-1, -1));
    indexerAcquire.reset(new JoystickButton(controlBoardA.get(), 5));
    indexerAcquire->WhileHeld(new LoadShooter(1, 1));
    sweeperExpel.reset(new JoystickButton(controlBoardA.get(), 4));
    sweeperExpel->WhileHeld(new ArmMotorEnable(-1));
    sweeperAcquire.reset(new JoystickButton(controlBoardA.get(), 3));
    sweeperAcquire->WhileHeld(new ArmMotorEnable(1));
    retractArm.reset(new JoystickButton(controlBoardA.get(), 2));
    retractArm->WhenPressed(new ArmExtend(false));
    extendArm.reset(new JoystickButton(controlBoardA.get(), 1));
    extendArm->WhenPressed(new ArmExtend(true));
    driverJoystick.reset(new Joystick(0));
    
    sweeperExpelDstick.reset(new JoystickButton(driverJoystick.get(), 11));
    sweeperExpelDstick->WhileHeld(new ArmMotorEnable(0));
    retractArmDstick.reset(new JoystickButton(driverJoystick.get(), 10));
    retractArmDstick->WhenPressed(new ArmExtend(false));
    indexerAcquireDstick.reset(new JoystickButton(driverJoystick.get(), 9));
    indexerAcquireDstick->WhileHeld(new LoadShooter(1, 1));
    sweeperAcquireDstick.reset(new JoystickButton(driverJoystick.get(), 8));
    sweeperAcquireDstick->WhileHeld(new ArmMotorEnable(0));
    extendArmDstick.reset(new JoystickButton(driverJoystick.get(), 7));
    extendArmDstick->WhenPressed(new ArmExtend(false));
    fireDstick.reset(new JoystickButton(driverJoystick.get(), 6));
    fireDstick->WhileHeld(new FireBoulder());
    shootHighDstick.reset(new JoystickButton(driverJoystick.get(), 5));
    shootHighDstick->WhileHeld(new Shoot(0, 0));
    frameUpDstick.reset(new JoystickButton(driverJoystick.get(), 4));
    frameUpDstick->WhenPressed(new ShootFrameControl(false));
    frameDownDstick.reset(new JoystickButton(driverJoystick.get(), 3));
    frameDownDstick->WhenPressed(new ShootFrameControl(false));
    driveInvertDirection.reset(new JoystickButton(driverJoystick.get(), 2));
    driveInvertDirection->WhenPressed(new DriveTrainInvert(false));
    driveShift.reset(new JoystickButton(driverJoystick.get(), 1));
    driveShift->WhileHeld(new DriveShiftHigh(false));

    // SmartDashboard Buttons
    SmartDashboard::PutData("Fire Boulder", new FireBoulder());
    SmartDashboard::PutData("Shoot Presets: DEFAULT", new ShootPresets(0));
    SmartDashboard::PutData("Shoot Presets: HIGH", new ShootPresets(1));
    SmartDashboard::PutData("Shoot Presets: MID", new ShootPresets(2));
    SmartDashboard::PutData("Shoot Presets: LOW", new ShootPresets(3));
    SmartDashboard::PutData("Shoot Presets: REVERSE", new ShootPresets(4));
    SmartDashboard::PutData("Shoot: DEFAULT", new Shoot(1, 1));
    SmartDashboard::PutData("Shoot Frame Control: DEFAULT", new ShootFrameControl(false));
    SmartDashboard::PutData("Shoot Frame Control: EXTEND", new ShootFrameControl(true));
    SmartDashboard::PutData("Shoot Frame Control: RETRACT", new ShootFrameControl(false));
    SmartDashboard::PutData("Arm Extend: DEFAULT", new ArmExtend(false));
    SmartDashboard::PutData("Arm Extend: EXTENDED", new ArmExtend(true));
    SmartDashboard::PutData("Arm Extend: RETRACTED", new ArmExtend(false));
    SmartDashboard::PutData("Drive Distance PID: DEFAULT", new DriveDistancePID(0, 0));
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getDriverJoystick() {
   return driverJoystick;
}

std::shared_ptr<Joystick> OI::getControlBoardA() {
   return controlBoardA;
}

std::shared_ptr<Joystick> OI::getControlBoardB() {
   return controlBoardB;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
