// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "OI.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AimSetAngle.h"
#include "Commands/AimStop.h"
#include "Commands/AutonomousCommandGroup.h"
#include "Commands/Climb.h"
#include "Commands/ClimbStop.h"
#include "Commands/CompressorSetOff.h"
#include "Commands/CompressorSetOn.h"
#include "Commands/DriveSpin.h"
#include "Commands/DriveStraight.h"
#include "Commands/DriveTrainOff.h"
#include "Commands/DriveTurn.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/ShiftHighGear.h"
#include "Commands/ShiftLowGear.h"
#include "Commands/ShootFrisbee.h"
#include "Commands/ShooterSetDirection.h"
#include "Commands/ShooterSetSpeed.h"
#include "Commands/ShooterStop.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorStick = new Joystick(2);
	
	operatorButton2 = new JoystickButton(operatorStick, 2);
	operatorButton2->WhileHeld(new ShooterSetSpeed());
	operatorTrigger = new JoystickButton(operatorStick, 1);
	operatorTrigger->WhileHeld(new ShootFrisbee());
	driverStick = new Joystick(1);
	
	driverButton2 = new JoystickButton(driverStick, 2);
	driverButton2->WhileHeld(new ShiftHighGear());
	driveButton6 = new JoystickButton(driverStick, 6);
	driveButton6->WhileHeld(new DriveSpin());
	driveButton5 = new JoystickButton(driverStick, 5);
	driveButton5->WhileHeld(new DriveSpin());
	driverTrigger = new JoystickButton(driverStick, 1);
	driverTrigger->WhileHeld(new DriveStraight());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Autonomous Command Group", new AutonomousCommandGroup());
	SmartDashboard::PutData("Drive With Joystick", new DriveWithJoystick());
	SmartDashboard::PutData("Drive Straight", new DriveStraight());
	SmartDashboard::PutData("Drive Turn", new DriveTurn());
	SmartDashboard::PutData("DriveTrain Off", new DriveTrainOff());
	SmartDashboard::PutData("Drive Spin", new DriveSpin());
	SmartDashboard::PutData("Shift High Gear", new ShiftHighGear());
	SmartDashboard::PutData("Shift Low Gear", new ShiftLowGear());
	SmartDashboard::PutData("Shoot Frisbee", new ShootFrisbee());
	SmartDashboard::PutData("Shooter Set Speed", new ShooterSetSpeed());
	SmartDashboard::PutData("Shooter Set Direction", new ShooterSetDirection());
	SmartDashboard::PutData("Shooter Stop", new ShooterStop());
	SmartDashboard::PutData("Climb", new Climb());
	SmartDashboard::PutData("Climb Stop", new ClimbStop());
	SmartDashboard::PutData("Compressor Set On", new CompressorSetOn());
	SmartDashboard::PutData("Compressor Set Off", new CompressorSetOff());
	SmartDashboard::PutData("Aim Stop", new AimStop());
	SmartDashboard::PutData("Aim Set Angle", new AimSetAngle());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
Joystick* OI::getOperatorStick() {
	return operatorStick;
}
Joystick* OI::getDriverStick() {
	return driverStick;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
//	Get driver joystick throttle setting
double OI::getDriverThrottle() {
	return driverStick->GetAxis( Joystick::kTwistAxis );
}
//	Get operator joystick throttle setting
double OI::getOperatorThrottle() {
	return operatorStick->GetAxis( Joystick::kTwistAxis );
}
