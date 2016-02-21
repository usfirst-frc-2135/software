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
#include "Commands/CompressorEnable.h"
#include "Commands/DriveDistancePID.h"
#include "Commands/DriveDistanceTimed.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTrainInvert.h"
#include "Commands/Shoot.h"
#include "Commands/ShootFrameControl.h"
#include "Commands/ShootJoystick.h"
#include "Commands/ShootPresets.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    operatorJoystick.reset(new Joystick(1));
    
    retractClimb.reset(new JoystickButton(operatorJoystick.get(), 12));
    retractClimb->WhenPressed(new Climb(false));
    extendClimb.reset(new JoystickButton(operatorJoystick.get(), 11));
    extendClimb->WhenPressed(new Climb(true));
    shootHigh.reset(new JoystickButton(operatorJoystick.get(), 10));
    shootHigh->WhileHeld(new ShootPresets(1));
    shootMid.reset(new JoystickButton(operatorJoystick.get(), 9));
    shootMid->WhileHeld(new ShootPresets(2));
    shootLow.reset(new JoystickButton(operatorJoystick.get(), 8));
    shootLow->WhileHeld(new ShootPresets(3));
    fire.reset(new JoystickButton(operatorJoystick.get(), 7));
    fire->WhileHeld(new ShootJoystick());
    frameDown.reset(new JoystickButton(operatorJoystick.get(), 6));
    frameDown->WhenPressed(new ShootFrameControl(false));
    frameUp.reset(new JoystickButton(operatorJoystick.get(), 5));
    frameUp->WhenPressed(new ShootFrameControl(true));
    expel.reset(new JoystickButton(operatorJoystick.get(), 4));
    expel->WhileHeld(new ArmMotorEnable(2));
    acquire.reset(new JoystickButton(operatorJoystick.get(), 3));
    acquire->WhileHeld(new ArmMotorEnable(1));
    retractArm.reset(new JoystickButton(operatorJoystick.get(), 2));
    retractArm->WhenPressed(new ArmExtend(false));
    extendArm.reset(new JoystickButton(operatorJoystick.get(), 1));
    extendArm->WhenPressed(new ArmExtend(true));
    driverJoystick.reset(new Joystick(0));
    
    driverInvertDirection.reset(new JoystickButton(driverJoystick.get(), 2));
    driverInvertDirection->WhenPressed(new DriveTrainInvert(false));

    // SmartDashboard Buttons
    SmartDashboard::PutData("Shoot Presets: DEFAULT", new ShootPresets(0));
    SmartDashboard::PutData("Shoot Presets: HIGH", new ShootPresets(1));
    SmartDashboard::PutData("Shoot Presets: MID", new ShootPresets(2));
    SmartDashboard::PutData("Shoot Presets: LOW", new ShootPresets(3));
    SmartDashboard::PutData("Shoot: DEFAULT", new Shoot(1, 1));
    SmartDashboard::PutData("Drive Distance PID: DEFAULT", new DriveDistancePID(0, 0));
    SmartDashboard::PutData("Drive Distance Timed: DEFAULT", new DriveDistanceTimed(3.0, 0));
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getDriverJoystick() {
   return driverJoystick;
}

std::shared_ptr<Joystick> OI::getOperatorJoystick() {
   return operatorJoystick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
