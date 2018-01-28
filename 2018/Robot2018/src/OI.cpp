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
#include "Commands/AutoDriveDistance.h"
#include "Commands/AutoDriveTurn.h"
#include "Commands/AutoStop.h"
#include "Commands/DriveShift.h"
#include "Commands/DriveSpin.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/ElevatorRun.h"
#include "Commands/GripperRun.h"
#include "Commands/LoadConfig.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    dStick.reset(new frc::Joystick(0));
    
    elevatorDown.reset(new frc::JoystickButton(dStick.get(), 10));
    elevatorDown->WhileHeld(new ElevatorRun(false));
    elevatorUp.reset(new frc::JoystickButton(dStick.get(), 11));
    elevatorUp->WhileHeld(new ElevatorRun(false));
    cubeExpel.reset(new frc::JoystickButton(dStick.get(), 7));
    cubeExpel->WhileHeld(new GripperRun(false));
    cubeAcquire.reset(new frc::JoystickButton(dStick.get(), 6));
    cubeAcquire->WhileHeld(new GripperRun(true));
    shiftSpeed.reset(new frc::JoystickButton(dStick.get(), 1));
    shiftSpeed->WhileHeld(new DriveShift(true));
    spinLeft.reset(new frc::JoystickButton(dStick.get(), 4));
    spinLeft->WhileHeld(new DriveSpin(false));
    spinRight.reset(new frc::JoystickButton(dStick.get(), 5));
    spinRight->WhileHeld(new DriveSpin(true));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Load Config", new LoadConfig());
    frc::SmartDashboard::PutData("Auto Drive Turn", new AutoDriveTurn());
    frc::SmartDashboard::PutData("Auto Drive Distance", new AutoDriveDistance());
    frc::SmartDashboard::PutData("Auto Stop", new AutoStop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    frc::SmartDashboard::PutData("Elevator Run", new ElevatorRun(true));
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDStick() {
   return dStick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
