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
#include "Commands/AutonomousCommand.h"
#include "Commands/AzimuthLeft.h"
#include "Commands/AzimuthOff.h"
#include "Commands/AzimuthRight.h"
#include "Commands/CameraDown.h"
#include "Commands/CameraUp.h"
#include "Commands/CompressorSetOff.h"
#include "Commands/CompressorSetOn.h"
#include "Commands/ConveyorDown.h"
#include "Commands/ConveyorOff.h"
#include "Commands/ConveyorUp.h"
#include "Commands/DriveSpinLeft.h"
#include "Commands/DriveSpinRight.h"
#include "Commands/DriveSpinSlowLeft.h"
#include "Commands/DriveSpinSlowRight.h"
#include "Commands/DriveStraightDistance.h"
#include "Commands/DriveStraightDistanceLow.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTrainOff.h"
#include "Commands/ShiftHighGear.h"
#include "Commands/ShiftLowGear.h"
#include "Commands/ShooterOff.h"
#include "Commands/ShooterOn.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorStick = new Joystick(2);
	
	operatorButton10 = new JoystickButton(operatorStick, 10);
	operatorButton10->WhileHeld(new CameraDown());
	operatorButton9 = new JoystickButton(operatorStick, 9);
	operatorButton9->WhileHeld(new ConveyorDown());
	operatorButton8 = new JoystickButton(operatorStick, 8);
	operatorButton8->WhileHeld(new CameraUp());
	operatorButton7 = new JoystickButton(operatorStick, 7);
	operatorButton7->WhileHeld(new ConveyorUp());
	operatorButton4 = new JoystickButton(operatorStick, 4);
	operatorButton4->WhileHeld(new AzimuthRight());
	operatorButton3 = new JoystickButton(operatorStick, 3);
	operatorButton3->WhileHeld(new AzimuthLeft());
	operatorTrigger = new JoystickButton(operatorStick, 1);
	operatorTrigger->WhileHeld(new ShooterOn());
	driverStick2 = new Joystick(3);
	
	driverStick1 = new Joystick(1);
	
	driver1Button9 = new JoystickButton(driverStick1, 9);
	driver1Button9->WhileHeld(new ConveyorDown());
	driver1Button7 = new JoystickButton(driverStick1, 7);
	driver1Button7->WhileHeld(new ConveyorUp());
	driver1Button6 = new JoystickButton(driverStick1, 6);
	driver1Button6->WhileHeld(new DriveSpinRight());
	driver1Button5 = new JoystickButton(driverStick1, 5);
	driver1Button5->WhileHeld(new DriveSpinLeft());
	driver1Button4 = new JoystickButton(driverStick1, 4);
	driver1Button4->WhileHeld(new DriveSpinSlowRight());
	driver1Button3 = new JoystickButton(driverStick1, 3);
	driver1Button3->WhileHeld(new DriveSpinSlowLeft());
	driver1Trigger = new JoystickButton(driverStick1, 1);
	driver1Trigger->WhileHeld(new ShiftLowGear());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
	SmartDashboard::PutData("Drive Straight Distance", new DriveStraightDistance());
	SmartDashboard::PutData("Drive Straight Distance Low", new DriveStraightDistanceLow());
	SmartDashboard::PutData("Drive Spin Left", new DriveSpinLeft());
	SmartDashboard::PutData("Drive Spin Slow Left", new DriveSpinSlowLeft());
	SmartDashboard::PutData("Drive Spin Right", new DriveSpinRight());
	SmartDashboard::PutData("Drive Spin Slow Right", new DriveSpinSlowRight());
	SmartDashboard::PutData("Drive Teleop", new DriveTeleop());
	SmartDashboard::PutData("Drive Train Off", new DriveTrainOff());
	SmartDashboard::PutData("Shift Low Gear", new ShiftLowGear());
	SmartDashboard::PutData("Shift High Gear", new ShiftHighGear());
	SmartDashboard::PutData("Conveyor Off", new ConveyorOff());
	SmartDashboard::PutData("Conveyor Up", new ConveyorUp());
	SmartDashboard::PutData("Conveyor Down", new ConveyorDown());
	SmartDashboard::PutData("Azimuth Off", new AzimuthOff());
	SmartDashboard::PutData("Azimuth Left", new AzimuthLeft());
	SmartDashboard::PutData("Azimuth Right", new AzimuthRight());
	SmartDashboard::PutData("Shooter Off", new ShooterOff());
	SmartDashboard::PutData("Shooter On", new ShooterOn());
	SmartDashboard::PutData("Compressor Set On", new CompressorSetOn());
	SmartDashboard::PutData("Compressor Set Off", new CompressorSetOff());
	SmartDashboard::PutData("Camera Up", new CameraUp());
	SmartDashboard::PutData("Camera Down", new CameraDown());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
Joystick* OI::getOperatorStick() {
	return operatorStick;
}
Joystick* OI::getDriverStick2() {
	return driverStick2;
}
Joystick* OI::getDriverStick1() {
	return driverStick1;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS