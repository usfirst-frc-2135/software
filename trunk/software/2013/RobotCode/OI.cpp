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
#include "Commands/DriveStraight.h"
#include "Commands/DriveTrainOff.h"
#include "Commands/DriveTurn.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/MagazineFullDown.h"
#include "Commands/MagazineFullUp.h"
#include "Commands/MagazineLoadSlot1.h"
#include "Commands/MagazineLoadSlot2.h"
#include "Commands/MagazineLoadSlot3.h"
#include "Commands/MagazineLoadSlot4.h"
#include "Commands/MagazineShootSlot1.h"
#include "Commands/MagazineShootSlot2.h"
#include "Commands/MagazineShootSlot3.h"
#include "Commands/MagazineShootSlot4.h"
#include "Commands/MagazineStop.h"
#include "Commands/ShiftHighGear.h"
#include "Commands/ShiftLowGear.h"
#include "Commands/ShootFrisbee.h"
#include "Commands/ShooterSetDirection.h"
#include "Commands/ShooterSetSpeed.h"
#include "Commands/ShooterStop.h"
#include "Commands/SweeperAcquire.h"
#include "Commands/SweeperReject.h"
#include "Commands/SweeperStop.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorStick = new Joystick(2);
	
	operatorButton9 = new JoystickButton(operatorStick, 9);
	operatorButton9->WhenPressed(new MagazineShootSlot4());
	operatorButton8 = new JoystickButton(operatorStick, 8);
	operatorButton8->WhenPressed(new MagazineShootSlot3());
	operatorButton7 = new JoystickButton(operatorStick, 7);
	operatorButton7->WhenPressed(new MagazineShootSlot2());
	operatorButton6 = new JoystickButton(operatorStick, 6);
	operatorButton6->WhenPressed(new MagazineShootSlot1());
	operatorTrigger = new JoystickButton(operatorStick, 1);
	operatorTrigger->WhileHeld(new ShooterSetSpeed());
	driverStick = new Joystick(1);
	
	driverButton11 = new JoystickButton(driverStick, 11);
	driverButton11->WhileHeld(new MagazineFullUp());
	driverButton10 = new JoystickButton(driverStick, 10);
	driverButton10->WhileHeld(new MagazineLoadSlot4());
	driverButton9 = new JoystickButton(driverStick, 9);
	driverButton9->WhileHeld(new MagazineShootSlot3());
	driverButton8 = new JoystickButton(driverStick, 8);
	driverButton8->WhileHeld(new MagazineLoadSlot2());
	driverButton7 = new JoystickButton(driverStick, 7);
	driverButton7->WhileHeld(new MagazineLoadSlot1());
	driverButton6 = new JoystickButton(driverStick, 6);
	driverButton6->WhenPressed(new SweeperReject());
	driverButton5 = new JoystickButton(driverStick, 5);
	driverButton5->WhenPressed(new MagazineLoadSlot3());
	driverButton4 = new JoystickButton(driverStick, 4);
	driverButton4->WhenPressed(new SweeperAcquire());
	driverButton3 = new JoystickButton(driverStick, 3);
	driverButton3->WhenPressed(new MagazineLoadSlot1());
	driverButton2 = new JoystickButton(driverStick, 2);
	driverButton2->WhenPressed(new ShiftHighGear());
	driverTrigger = new JoystickButton(driverStick, 1);
	driverTrigger->WhileHeld(new DriveStraight());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Autonomous Command Group", new AutonomousCommandGroup());
	SmartDashboard::PutData("Drive With Joystick", new DriveWithJoystick());
	SmartDashboard::PutData("Drive Straight", new DriveStraight());
	SmartDashboard::PutData("Drive Turn", new DriveTurn());
	SmartDashboard::PutData("DriveTrain Off", new DriveTrainOff());
	SmartDashboard::PutData("Shift High Gear", new ShiftHighGear());
	SmartDashboard::PutData("Shift Low Gear", new ShiftLowGear());
	SmartDashboard::PutData("Sweeper Acquire", new SweeperAcquire());
	SmartDashboard::PutData("Sweeper Reject", new SweeperReject());
	SmartDashboard::PutData("Sweeper Stop", new SweeperStop());
	SmartDashboard::PutData("Magazine Stop", new MagazineStop());
	SmartDashboard::PutData("Magazine Full Down", new MagazineFullDown());
	SmartDashboard::PutData("Magazine Load Slot 1", new MagazineLoadSlot1());
	SmartDashboard::PutData("Magazine Load Slot 2", new MagazineLoadSlot2());
	SmartDashboard::PutData("Magazine Load Slot 3", new MagazineLoadSlot3());
	SmartDashboard::PutData("Magazine Load Slot 4", new MagazineLoadSlot4());
	SmartDashboard::PutData("Magazine Shoot Slot 1", new MagazineShootSlot1());
	SmartDashboard::PutData("Magazine Shoot Slot 2", new MagazineShootSlot2());
	SmartDashboard::PutData("Magazine Shoot Slot 3", new MagazineShootSlot3());
	SmartDashboard::PutData("Magazine Shoot Slot 4", new MagazineShootSlot4());
	SmartDashboard::PutData("Magazine Full Up", new MagazineFullUp());
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
	return driverStick->GetThrottle();
}
//	Get driver joystick throttle setting
double OI::getOperatorThrottle() {
	return operatorStick->GetThrottle();
}
