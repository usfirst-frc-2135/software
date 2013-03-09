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
#include "Commands/AutonomousCommandGroup.h"
#include "Commands/Climb.h"
#include "Commands/ClimbStop.h"
#include "Commands/CompressorSetOff.h"
#include "Commands/CompressorSetOn.h"
#include "Commands/DriveSpin.h"
#include "Commands/DriveSpinSlow.h"
#include "Commands/DriveStraight.h"
#include "Commands/DriveStraightDistance.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTrainOff.h"
#include "Commands/DriveTurn.h"
#include "Commands/FireFrisbee.h"
#include "Commands/FireFrisbeeTimed.h"
#include "Commands/FireReload.h"
#include "Commands/FireReloadTimed.h"
#include "Commands/FiringSequence.h"
#include "Commands/ShiftHighGear.h"
#include "Commands/ShiftLowGear.h"
#include "Commands/ShootFrisbee.h"
#include "Commands/ShooterSetDirection.h"
#include "Commands/ShooterSetSpeed.h"
#include "Commands/ShooterStop.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
	// DriveSpin input requires DriveSpin::kSpinLeft and kSpinRight
	//driverButton6 = new JoystickButton(driverStick, 6);
	//driverButton6->WhileHeld(new DriveSpin(DriveSpin::kSpinRight));
	//driverButton5 = new JoystickButton(driverStick, 5);
	//driverButton5->WhileHeld(new DriveSpin(DriveSpin::kSpinLeft));
	//driverButton4 = new JoystickButton(driverStick, 4);
	//driverButton4->WhileHeld(new DriveSpin(DriveSpin::kSpinRight));
	//driverButton3 = new JoystickButton(driverStick, 3);
	//driverButton3->WhileHeld(new DriveSpin(DriveSpin::kSpinLeft));
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorStick = new Joystick(2);
	
	operatorButton8 = new JoystickButton(operatorStick, 8);
	operatorButton8->WhileHeld(new ShooterSetSpeed());
	operatorButton7 = new JoystickButton(operatorStick, 7);
	operatorButton7->WhileHeld(new AimDown());
	operatorButton2 = new JoystickButton(operatorStick, 2);
	operatorButton2->WhileHeld(new ShootFrisbee());
	operatorTrigger = new JoystickButton(operatorStick, 1);
	operatorTrigger->WhileHeld(new FireFrisbee());
	driverStick = new Joystick(1);
	
	driverButton8 = new JoystickButton(driverStick, 8);
	driverButton8->WhileHeld(new DriveTurn());
	driverButton7 = new JoystickButton(driverStick, 7);
	driverButton7->WhileHeld(new DriveStraight());
	driverButton6 = new JoystickButton(driverStick, 6);
	driverButton6->WhileHeld(new DriveSpin(DriveSpin::kSpinRight));
	driverButton5 = new JoystickButton(driverStick, 5);
	driverButton5->WhileHeld(new DriveSpin(DriveSpin::kSpinLeft));
	driverButton4 = new JoystickButton(driverStick, 4);
	driverButton4->WhileHeld(new DriveSpinSlow(DriveSpinSlow::kSpinRight));
	driverButton3 = new JoystickButton(driverStick, 3);
	driverButton3->WhileHeld(new DriveSpinSlow(DriveSpinSlow::kSpinLeft));
	driverButton2 = new JoystickButton(driverStick, 2);
	driverButton2->WhileHeld(new ShiftHighGear());
	driverTrigger = new JoystickButton(driverStick, 1);
	driverTrigger->WhileHeld(new ShiftHighGear());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Autonomous Command Group", new AutonomousCommandGroup());
	SmartDashboard::PutData("Drive Teleop", new DriveTeleop());
	SmartDashboard::PutData("Drive Straight", new DriveStraight());
	SmartDashboard::PutData("Drive Turn", new DriveTurn());
	SmartDashboard::PutData("Drive Spin", new DriveSpin());
	SmartDashboard::PutData("DriveTrain Off", new DriveTrainOff());
	SmartDashboard::PutData("Shift High Gear", new ShiftHighGear());
	SmartDashboard::PutData("Shift Low Gear", new ShiftLowGear());
	SmartDashboard::PutData("Aim Up", new AimUp());
	SmartDashboard::PutData("Aim Down", new AimDown());
	SmartDashboard::PutData("Fire Frisbee", new FireFrisbee());
	SmartDashboard::PutData("Fire Reload", new FireReload());
	SmartDashboard::PutData("Shoot Frisbee", new ShootFrisbee());
	SmartDashboard::PutData("Shooter Set Speed", new ShooterSetSpeed());
	SmartDashboard::PutData("Shooter Set Direction", new ShooterSetDirection());
	SmartDashboard::PutData("Shooter Stop", new ShooterStop());
	SmartDashboard::PutData("Climb", new Climb());
	SmartDashboard::PutData("Climb Stop", new ClimbStop());
	SmartDashboard::PutData("Compressor Set On", new CompressorSetOn());
	SmartDashboard::PutData("Compressor Set Off", new CompressorSetOff());
	SmartDashboard::PutData("Firing Sequence", new FiringSequence());
	SmartDashboard::PutData("Fire Frisbee Timed", new FireFrisbeeTimed());
	SmartDashboard::PutData("Fire Reload Timed", new FireReloadTimed());
	SmartDashboard::PutData("Drive Spin Slow", new DriveSpinSlow());
	SmartDashboard::PutData("Drive Straight Distance", new DriveStraightDistance());
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
