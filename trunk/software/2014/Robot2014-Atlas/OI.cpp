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
#include "Commands/AutonomousCommand.h"
#include "Commands/CompressorOff.h"
#include "Commands/CompressorOn.h"
#include "Commands/DriveDistance.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/ShiftHighGear.h"
#include "Commands/ShiftLowGear.h"
#include "Commands/ShooterEnergize.h"
#include "Commands/ShooterFire.h"
#include "Commands/SweeperArmDeploy.h"
#include "Commands/SweeperArmRetract.h"
#include "Commands/SweeperMotorAcquire.h"
#include "Commands/SweeperMotorReject.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorJoystick = new Joystick(2);
	
	driverJoystick = new Joystick(1);
	
	driverShooterRetract = new JoystickButton(driverJoystick, 12);
	driverShooterRetract->WhenPressed(new ShooterFire());
	driverShooterRelease = new JoystickButton(driverJoystick, 11);
	driverShooterRelease->WhenPressed(new ShooterEnergize());
	driverSweeperDeploy = new JoystickButton(driverJoystick, 5);
	driverSweeperDeploy->WhenPressed(new SweeperArmDeploy());
	driverSweeperRetract = new JoystickButton(driverJoystick, 3);
	driverSweeperRetract->WhenPressed(new SweeperArmRetract());
	driverSweeperReject = new JoystickButton(driverJoystick, 4);
	driverSweeperReject->WhenPressed(new SweeperMotorReject());
	driverSweeperAcquire = new JoystickButton(driverJoystick, 6);
	driverSweeperAcquire->WhenPressed(new SweeperMotorAcquire());
	shifter = new JoystickButton(driverJoystick, 1);
	shifter->WhileHeld(new ShiftHighGear());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
	SmartDashboard::PutData("Compressor On", new CompressorOn());
	SmartDashboard::PutData("Compressor Off", new CompressorOff());
	SmartDashboard::PutData("Drive Distance", new DriveDistance());
	SmartDashboard::PutData("Drive Stop", new DriveStop());
	SmartDashboard::PutData("Drive Teleop", new DriveTeleop());
	SmartDashboard::PutData("Shift High Gear", new ShiftHighGear());
	SmartDashboard::PutData("Shift Low Gear", new ShiftLowGear());
	SmartDashboard::PutData("Sweeper Arm Deploy", new SweeperArmDeploy());
	SmartDashboard::PutData("Sweeper Arm Retract", new SweeperArmRetract());
	SmartDashboard::PutData("Sweeper Motor Acquire", new SweeperMotorAcquire());
	SmartDashboard::PutData("Sweeper Motor Reject", new SweeperMotorReject());
	SmartDashboard::PutData("Shooter Energize", new ShooterEnergize());
	SmartDashboard::PutData("Shooter Fire", new ShooterFire());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	printf("2135: OI constructor\n");
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
Joystick* OI::getOperatorJoystick() {
	return operatorJoystick;
}
Joystick* OI::getDriverJoystick() {
	return driverJoystick;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
