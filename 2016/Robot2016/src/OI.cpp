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
#include "Commands/DriveShifterChange.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTrainInvert.h"
#include "Commands/Shoot.h"
#include "Commands/ShootFrameControl.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    operatorJoystick.reset(new Joystick(1));
    
    retractClimb.reset(new JoystickButton(operatorJoystick.get(), 9));
    retractClimb->WhenPressed(new Climb(false));
    extendClimb.reset(new JoystickButton(operatorJoystick.get(), 8));
    extendClimb->WhenPressed(new Climb(true));
    expel.reset(new JoystickButton(operatorJoystick.get(), 7));
    expel->WhenPressed(new ArmMotorEnable(0));
    acquire.reset(new JoystickButton(operatorJoystick.get(), 6));
    acquire->WhenPressed(new ArmMotorEnable(0));
    retractArm.reset(new JoystickButton(operatorJoystick.get(), 5));
    retractArm->WhenPressed(new ArmExtend(false));
    extendArm.reset(new JoystickButton(operatorJoystick.get(), 4));
    extendArm->WhenPressed(new ArmExtend(true));
    frameDown.reset(new JoystickButton(operatorJoystick.get(), 3));
    frameDown->WhenPressed(new ShootFrameControl(false));
    frameUp.reset(new JoystickButton(operatorJoystick.get(), 2));
    frameUp->WhenPressed(new ShootFrameControl(true));
    fire.reset(new JoystickButton(operatorJoystick.get(), 1));
    fire->WhileHeld(new Shoot(0, 0));
    driverJoystick.reset(new Joystick(0));
    
    driverInvertDirection.reset(new JoystickButton(driverJoystick.get(), 2));
    driverInvertDirection->WhenPressed(new DriveTrainInvert(false));
    driveGear.reset(new JoystickButton(driverJoystick.get(), 1));
    driveGear->WhileHeld(new DriveShifterChange(false));

    // SmartDashboard Buttons
    SmartDashboard::PutData("Shoot", new Shoot(1.0, 1.0));
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