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
#include "Commands/AimDown.h"
#include "Commands/AimUp.h"
#include "Commands/AutoClimbGroup.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/ClimberExtend.h"
#include "Commands/ClimberRetract.h"
#include "Commands/CompressorSetOff.h"
#include "Commands/CompressorSetOn.h"
#include "Commands/DriveSpinLeft.h"
#include "Commands/DriveSpinLeftLow.h"
#include "Commands/DriveSpinRight.h"
#include "Commands/DriveSpinRightLow.h"
#include "Commands/DriveSpinSlowLeft.h"
#include "Commands/DriveSpinSlowRight.h"
#include "Commands/DriveStraightDistance.h"
#include "Commands/DriveStraightDistanceLow.h"
#include "Commands/DriveStraightLeft.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTrainOff.h"
#include "Commands/FireFrisbee.h"
#include "Commands/FireFrisbeeTimed.h"
#include "Commands/FireReload.h"
#include "Commands/FireReloadTimed.h"
#include "Commands/ShiftHighGear.h"
#include "Commands/ShiftLowGear.h"
#include "Commands/ShooterAutoSetpoint.h"
#include "Commands/ShooterRun.h"
#include "Commands/ShooterSetSpeed.h"
#include "Commands/ShooterStop.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorStick = new Joystick(2);
	
	operatorButton12 = new JoystickButton(operatorStick, 12);
	operatorButton12->WhileHeld(new ClimberRetract());
	operatorButton11 = new JoystickButton(operatorStick, 11);
	operatorButton11->WhileHeld(new AimDown());
	operatorButton10 = new JoystickButton(operatorStick, 10);
	operatorButton10->WhileHeld(new AutoClimbGroup());
	operatorButton9 = new JoystickButton(operatorStick, 9);
	operatorButton9->WhileHeld(new AutonomousCommand());
	operatorButton8 = new JoystickButton(operatorStick, 8);
	operatorButton8->WhileHeld(new ClimberExtend());
	operatorButton7 = new JoystickButton(operatorStick, 7);
	operatorButton7->WhileHeld(new AimUp());
	operatorButton6 = new JoystickButton(operatorStick, 6);
	operatorButton6->WhileHeld(new DriveSpinRight());
	operatorButton5 = new JoystickButton(operatorStick, 5);
	operatorButton5->WhileHeld(new DriveSpinLeft());
	operatorButton4 = new JoystickButton(operatorStick, 4);
	operatorButton4->WhileHeld(new DriveSpinRightLow());
	operatorButton3 = new JoystickButton(operatorStick, 3);
	operatorButton3->WhileHeld(new DriveSpinLeftLow());
	operatorButton2 = new JoystickButton(operatorStick, 2);
	operatorButton2->WhileHeld(new ShooterRun());
	operatorTrigger = new JoystickButton(operatorStick, 1);
	operatorTrigger->WhileHeld(new FireFrisbee());
	driverStick = new Joystick(1);
	
	driverButton12 = new JoystickButton(driverStick, 12);
	driverButton12->WhileHeld(new ClimberRetract());
	driverButton11 = new JoystickButton(driverStick, 11);
	driverButton11->WhileHeld(new AimDown());
	driverButton10 = new JoystickButton(driverStick, 10);
	driverButton10->WhileHeld(new DriveStraightDistance());
	driverButton9 = new JoystickButton(driverStick, 9);
	driverButton9->WhileHeld(new DriveStraightDistanceLow());
	driverButton8 = new JoystickButton(driverStick, 8);
	driverButton8->WhileHeld(new ClimberExtend());
	driverButton7 = new JoystickButton(driverStick, 7);
	driverButton7->WhileHeld(new AimUp());
	driverButton6 = new JoystickButton(driverStick, 6);
	driverButton6->WhileHeld(new DriveSpinRight());
	driverButton5 = new JoystickButton(driverStick, 5);
	driverButton5->WhileHeld(new DriveSpinLeft());
	driverButton4 = new JoystickButton(driverStick, 4);
	driverButton4->WhileHeld(new DriveSpinRightLow());
	driverButton3 = new JoystickButton(driverStick, 3);
	driverButton3->WhileHeld(new DriveSpinLeftLow());
	driverButton2 = new JoystickButton(driverStick, 2);
	driverButton2->WhileHeld(new ShiftLowGear());
	driverTrigger = new JoystickButton(driverStick, 1);
	driverTrigger->WhileHeld(new ShiftLowGear());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
	SmartDashboard::PutData("Drive Straight Distance", new DriveStraightDistance());
	SmartDashboard::PutData("Drive Straight Distance Low", new DriveStraightDistanceLow());
	SmartDashboard::PutData("Drive Straight Left", new DriveStraightLeft());
	SmartDashboard::PutData("Drive Spin Left", new DriveSpinLeft());
	SmartDashboard::PutData("Drive Spin Right", new DriveSpinRight());
	SmartDashboard::PutData("Drive Spin Slow Left", new DriveSpinSlowLeft());
	SmartDashboard::PutData("Drive Spin Slow Right", new DriveSpinSlowRight());
	SmartDashboard::PutData("Drive Teleop", new DriveTeleop());
	SmartDashboard::PutData("Drive Train Off", new DriveTrainOff());
	SmartDashboard::PutData("Shift High Gear", new ShiftHighGear());
	SmartDashboard::PutData("Shift Low Gear", new ShiftLowGear());
	SmartDashboard::PutData("Aim Down", new AimDown());
	SmartDashboard::PutData("Aim Up", new AimUp());
	SmartDashboard::PutData("Fire Frisbee", new FireFrisbee());
	SmartDashboard::PutData("Fire Frisbee Timed", new FireFrisbeeTimed());
	SmartDashboard::PutData("Fire Reload", new FireReload());
	SmartDashboard::PutData("Fire Reload Timed", new FireReloadTimed());
	SmartDashboard::PutData("Shooter Auto Setpoint", new ShooterAutoSetpoint());
	SmartDashboard::PutData("Shooter Run", new ShooterRun());
	SmartDashboard::PutData("Shooter Set Speed", new ShooterSetSpeed());
	SmartDashboard::PutData("Shooter Stop", new ShooterStop());
	SmartDashboard::PutData("Auto Climb Group", new AutoClimbGroup());
	SmartDashboard::PutData("Climber Extend", new ClimberExtend());
	SmartDashboard::PutData("Climber Retract", new ClimberRetract());
	SmartDashboard::PutData("Compressor Set On", new CompressorSetOn());
	SmartDashboard::PutData("Compressor Set Off", new CompressorSetOff());
	SmartDashboard::PutData("Drive Spin Left Low", new DriveSpinLeftLow());
	SmartDashboard::PutData("Drive Spin Right Low", new DriveSpinRightLow());
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
