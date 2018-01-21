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
#include "Commands/AutonDriveDistance.h"
#include "Commands/DriveShift.h"
#include "Commands/DriveSpin.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/Elevate.h"
#include "Commands/Intake.h"
#include "Commands/LoadConfig.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driverStick.reset(new frc::Joystick(0));
    
    elevatorDown.reset(new frc::JoystickButton(driverStick.get(), 10));
    elevatorDown->WhileHeld(new Elevate(false));
    elevatorUp.reset(new frc::JoystickButton(driverStick.get(), 11));
    elevatorUp->WhileHeld(new Elevate(true));
    gripperExpel.reset(new frc::JoystickButton(driverStick.get(), 7));
    gripperExpel->WhileHeld(new Intake(false));
    gripperAcquire.reset(new frc::JoystickButton(driverStick.get(), 6));
    gripperAcquire->WhileHeld(new Intake(true));
    driverShiftToggle.reset(new frc::JoystickButton(driverStick.get(), 2));
    driverShiftToggle->WhenPressed(new DriveShift(true));
    driverShift.reset(new frc::JoystickButton(driverStick.get(), 1));
    driverShift->WhileHeld(new DriveShift(true));
    driveSpinLeft.reset(new frc::JoystickButton(driverStick.get(), 4));
    driveSpinLeft->WhileHeld(new DriveSpin(false));
    driveSpinRight.reset(new frc::JoystickButton(driverStick.get(), 5));
    driveSpinRight->WhileHeld(new DriveSpin(true));

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("Load Config", new LoadConfig());
    frc::SmartDashboard::PutData("Auton Drive Distance", new AutonDriveDistance());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDriverStick() {
   return driverStick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
