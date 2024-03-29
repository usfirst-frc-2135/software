// RobotBuilder Version: 1.0
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
#include "Commands/AutoCommand.h"
#include "Commands/AutoDriveAndShoot.h"
#include "Commands/BallGateClose.h"
#include "Commands/BallGateOpen.h"
#include "Commands/CompressorOff.h"
#include "Commands/CompressorOn.h"
#include "Commands/DriveDistance.h"
#include "Commands/DriveSpinLeft.h"
#include "Commands/DriveSpinRight.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTrainInvert.h"
#include "Commands/ShiftHighGear.h"
#include "Commands/ShiftLowGear.h"
#include "Commands/ShooterFire.h"
#include "Commands/ShooterFireAuto.h"
#include "Commands/ShooterIdle.h"
#include "Commands/ShooterReload.h"
#include "Commands/SweeperArmDeploy.h"
#include "Commands/SweeperArmRetract.h"
#include "Commands/SweeperMotorAcquire.h"
#include "Commands/SweeperMotorOff.h"
#include "Commands/SweeperMotorReject.h"
#include "Commands/TimeDelay.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorJoystick = new Joystick(2);
	
	operatorBallGateOpen2 = new JoystickButton(operatorJoystick, 5);
	operatorBallGateOpen2->WhileHeld(new BallGateOpen());
	operatorBallGateClose2 = new JoystickButton(operatorJoystick, 12);
	operatorBallGateClose2->WhenPressed(new BallGateClose());
	operatorBallGateClose = new JoystickButton(operatorJoystick, 6);
	operatorBallGateClose->WhenPressed(new BallGateClose());
	operatorBallGateOpen = new JoystickButton(operatorJoystick, 11);
	operatorBallGateOpen->WhenPressed(new BallGateOpen());
	operatorSweeperRetract = new JoystickButton(operatorJoystick, 9);
	operatorSweeperRetract->WhenPressed(new SweeperArmRetract());
	operatorSweeperDeploy = new JoystickButton(operatorJoystick, 7);
	operatorSweeperDeploy->WhenPressed(new SweeperArmDeploy());
	operatorSweeperReject = new JoystickButton(operatorJoystick, 10);
	operatorSweeperReject->WhileHeld(new SweeperMotorReject());
	operatorSweeperAquire = new JoystickButton(operatorJoystick, 8);
	operatorSweeperAquire->WhileHeld(new SweeperMotorAcquire());
	operatorShooterReload = new JoystickButton(operatorJoystick, 2);
	operatorShooterReload->WhenPressed(new ShooterReload());
	operatorShooterFire = new JoystickButton(operatorJoystick, 1);
	operatorShooterFire->WhenPressed(new ShooterFire());
	driverJoystick = new Joystick(1);
	
	driverBallGateClose = new JoystickButton(driverJoystick, 12);
	driverBallGateClose->WhenPressed(new BallGateClose());
	driverBallGateOpen = new JoystickButton(driverJoystick, 11);
	driverBallGateOpen->WhenPressed(new BallGateOpen());
	driverSweeperRetract = new JoystickButton(driverJoystick, 9);
	driverSweeperRetract->WhenPressed(new SweeperArmRetract());
	driverSweeperDeploy = new JoystickButton(driverJoystick, 7);
	driverSweeperDeploy->WhenPressed(new SweeperArmDeploy());
	driverSweeperReject = new JoystickButton(driverJoystick, 10);
	driverSweeperReject->WhileHeld(new SweeperMotorReject());
	driverSweeperAcquire = new JoystickButton(driverJoystick, 8);
	driverSweeperAcquire->WhileHeld(new SweeperMotorAcquire());
	driverDriveSpinLeft = new JoystickButton(driverJoystick, 5);
	driverDriveSpinLeft->WhileHeld(new DriveSpinLeft());
	driverDriveSpinRight = new JoystickButton(driverJoystick, 6);
	driverDriveSpinRight->WhileHeld(new DriveSpinRight());
	driverDrivetrainInvert = new JoystickButton(driverJoystick, 2);
	driverDrivetrainInvert->WhenPressed(new DriveTrainInvert());
	shifter = new JoystickButton(driverJoystick, 1);
	shifter->WhileHeld(new ShiftLowGear());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Auto Command", new AutoCommand());
	SmartDashboard::PutData("Auto Drive And Shoot", new AutoDriveAndShoot());
	SmartDashboard::PutData("Drive Stop", new DriveStop());
	SmartDashboard::PutData("Drive Teleop", new DriveTeleop());
	SmartDashboard::PutData("Drive Distance", new DriveDistance());
	SmartDashboard::PutData("Drive Train Invert", new DriveTrainInvert());
	SmartDashboard::PutData("Drive Spin Right", new DriveSpinRight());
	SmartDashboard::PutData("Drive Spin Left", new DriveSpinLeft());
	SmartDashboard::PutData("Shift Low Gear", new ShiftLowGear());
	SmartDashboard::PutData("Shift High Gear", new ShiftHighGear());
	SmartDashboard::PutData("Sweeper Arm Retract", new SweeperArmRetract());
	SmartDashboard::PutData("Sweeper Arm Deploy", new SweeperArmDeploy());
	SmartDashboard::PutData("Sweeper Motor Off", new SweeperMotorOff());
	SmartDashboard::PutData("Sweeper Motor Acquire", new SweeperMotorAcquire());
	SmartDashboard::PutData("Sweeper Motor Reject", new SweeperMotorReject());
	SmartDashboard::PutData("Ball Gate Close", new BallGateClose());
	SmartDashboard::PutData("Ball Gate Open", new BallGateOpen());
	SmartDashboard::PutData("Compressor On", new CompressorOn());
	SmartDashboard::PutData("Compressor Off", new CompressorOff());
	SmartDashboard::PutData("Shooter Reload", new ShooterReload());
	SmartDashboard::PutData("Shooter Fire", new ShooterFire());
	SmartDashboard::PutData("Shooter Idle", new ShooterIdle());
	SmartDashboard::PutData("Shooter Fire Auto", new ShooterFireAuto());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	printf( "2135: OI constructor\n" );
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
Joystick* OI::getOperatorJoystick() {
	return operatorJoystick;
}
Joystick* OI::getDriverJoystick() {
	return driverJoystick;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
