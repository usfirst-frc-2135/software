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
#include "Commands/ElevatorCalibrate.h"
#include "Commands/ElevatorCalibrateOverride.h"
#include "Commands/ElevatorRun.h"
#include "Commands/GripperExtend.h"
#include "Commands/GripperRun.h"
#include "Commands/LoadConfig.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    dStick.reset(new frc::Joystick(0));
    
    elevatorDown.reset(new frc::JoystickButton(dStick.get(), 10));
    elevatorDown->WhileHeld(new ElevatorRun(0));
    elevatorUp.reset(new frc::JoystickButton(dStick.get(), 11));
    elevatorUp->WhileHeld(new ElevatorRun(0));
    cubeExpel.reset(new frc::JoystickButton(dStick.get(), 7));
    cubeExpel->WhileHeld(new GripperRun(-1));
    cubeAcquire.reset(new frc::JoystickButton(dStick.get(), 6));
    cubeAcquire->WhileHeld(new GripperRun(1));
    shiftSpeed.reset(new frc::JoystickButton(dStick.get(), 1));
    shiftSpeed->WhileHeld(new DriveShift(true));
    spinLeft.reset(new frc::JoystickButton(dStick.get(), 4));
    spinLeft->WhileHeld(new DriveSpin(false));
    spinRight.reset(new frc::JoystickButton(dStick.get(), 5));
    spinRight->WhileHeld(new DriveSpin(true));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Load Config", new LoadConfig());
    frc::SmartDashboard::PutData("Elevator Calibrate Override", new ElevatorCalibrateOverride());
    frc::SmartDashboard::PutData("Elevator Calibrate", new ElevatorCalibrate());
    frc::SmartDashboard::PutData("Gripper Extend: extend", new GripperExtend(false));
    frc::SmartDashboard::PutData("Auto Drive Turn", new AutoDriveTurn());
    frc::SmartDashboard::PutData("Auto Stop", new AutoStop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    frc::SmartDashboard::PutData("Auto Drive Distance", new AutoDriveDistance(0));
    frc::SmartDashboard::PutData("Elevator Run", new ElevatorRun(5)); //Eventually pass in variable in inches
    frc::SmartDashboard::PutData("Elevator Run For 17", new ElevatorRun(17)); // For testing
    frc::SmartDashboard::PutData("Elevator Run For -2", new ElevatorRun(-2)); // For testing negative safety
    frc::SmartDashboard::PutData("Elevator Run for 5", new ElevatorRun(5));   // For testing
    frc::SmartDashboard::PutData("Elevator Run For 10", new ElevatorRun(10)); // For testing
    frc::SmartDashboard::PutData("Elevator Run For 26", new ElevatorRun(26)); // For testing
    frc::SmartDashboard::PutData("Elevator Run For 33", new ElevatorRun(33)); // For testing

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDStick() {
   return dStick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
