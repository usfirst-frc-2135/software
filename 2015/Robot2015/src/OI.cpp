// RobotBuilder Version: 1.5
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
#include "Commands/AutoCommand.h"
#include "Commands/AutoContainerSet.h"
#include "Commands/AutoStackTote.h"
#include "Commands/AutoToteSet.h"
#include "Commands/CompressorOff.h"
#include "Commands/CompressorOn.h"
#include "Commands/DriveDistance.h"
#include "Commands/DriveDistanceTimed.h"
#include "Commands/DriveHWheel.h"
#include "Commands/DriveReverseDirection.h"
#include "Commands/DriveSlow.h"
#include "Commands/DriveSpinLeft.h"
#include "Commands/DriveSpinRight.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTurn.h"
#include "Commands/ElevatorDisablePID.h"
#include "Commands/ElevatorDown.h"
#include "Commands/ElevatorEnablePID.h"
#include "Commands/ElevatorIdle.h"
#include "Commands/ElevatorMoveToPosition.h"
#include "Commands/ElevatorMoveToPosition1.h"
#include "Commands/ElevatorMoveToPosition2.h"
#include "Commands/ElevatorMoveToPosition3.h"
#include "Commands/ElevatorMoveToPosition4.h"
#include "Commands/ElevatorUp.h"
#include "Commands/GripperHold.h"
#include "Commands/GripperRelease.h"
#include "Commands/IntakeAcquireBoth.h"
#include "Commands/IntakeAcquireL.h"
#include "Commands/IntakeAcquireR.h"
#include "Commands/IntakeExpelBoth.h"
#include "Commands/IntakeExpelL.h"
#include "Commands/IntakeExpelR.h"
#include "Commands/IntakeIdleBoth.h"
#include "Commands/IntakeIdleL.h"
#include "Commands/IntakeIdleR.h"
#include "Commands/IntakeSpinL.h"
#include "Commands/IntakeSpinR.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	printf("2135: OI init\n");
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	joystick3 = new Joystick(2);
	
	operatorElevatorUp = new JoystickButton(joystick3, 4);
	operatorElevatorUp->WhileHeld(new ElevatorUp());
	operatorStackerExpel = new JoystickButton(joystick3, 9);
	operatorStackerExpel->WhileHeld(new IntakeExpelBoth());
	operatorStackerAcquire = new JoystickButton(joystick3, 8);
	operatorStackerAcquire->WhileHeld(new IntakeAcquireBoth());
	operatorGripperRelease = new JoystickButton(joystick3, 5);
	operatorGripperRelease->WhenPressed(new GripperRelease());
	operatorGripperHold = new JoystickButton(joystick3, 3);
	operatorGripperHold->WhenPressed(new GripperHold());
	operatorIntakeExpelR = new JoystickButton(joystick3, 6);
	operatorIntakeExpelR->WhileHeld(new IntakeExpelR());
	operatorIntakeExpelL = new JoystickButton(joystick3, 11);
	operatorIntakeExpelL->WhileHeld(new IntakeExpelL());
	operatorIntakeAcquireR = new JoystickButton(joystick3, 2);
	operatorIntakeAcquireR->WhileHeld(new IntakeAcquireR());
	operatorIntakeAcquireL = new JoystickButton(joystick3, 1);
	operatorIntakeAcquireL->WhileHeld(new IntakeAcquireL());
	joystick2 = new Joystick(1);
	
	operatorElevatorPosition4 = new JoystickButton(joystick2, 5);
	operatorElevatorPosition4->WhenPressed(new ElevatorMoveToPosition4());
	operatorElevatorPosition3 = new JoystickButton(joystick2, 4);
	operatorElevatorPosition3->WhileHeld(new ElevatorMoveToPosition3());
	operatorElevatorPosition2 = new JoystickButton(joystick2, 3);
	operatorElevatorPosition2->WhenPressed(new ElevatorMoveToPosition2());
	operatorElevatorPosition1 = new JoystickButton(joystick2, 2);
	operatorElevatorPosition1->WhenPressed(new ElevatorMoveToPosition1());
	operatorElevatorDown = new JoystickButton(joystick2, 1);
	operatorElevatorDown->WhileHeld(new ElevatorDown());
	joystick1 = new Joystick(0);
	
	driveSpinRight2 = new JoystickButton(joystick1, 12);
	driveSpinRight2->WhileHeld(new DriveSpinRight());
	driveSpinLeft2 = new JoystickButton(joystick1, 11);
	driveSpinLeft2->WhileHeld(new DriveSpinLeft());
	driverDisableElevatorPID = new JoystickButton(joystick1, 8);
	driverDisableElevatorPID->WhenPressed(new ElevatorDisablePID());
	driverEnableElevatorPID = new JoystickButton(joystick1, 7);
	driverEnableElevatorPID->WhenPressed(new ElevatorEnablePID());
	driverSpinRight = new JoystickButton(joystick1, 4);
	driverSpinRight->WhileHeld(new DriveSpinRight());
	driverSpinLeft = new JoystickButton(joystick1, 3);
	driverSpinLeft->WhileHeld(new DriveSpinLeft());
	driverHWheel = new JoystickButton(joystick1, 2);
	driverHWheel->WhileHeld(new DriveHWheel());
	driverDriveTeleop = new JoystickButton(joystick1, 1);
	driverDriveTeleop->WhileHeld(new DriveTeleop());
     

        // SmartDashboard Buttons
	SmartDashboard::PutData("Drive H Wheel", new DriveHWheel());


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

Joystick* OI::getJoystick3() {
	return joystick3;
}

Joystick* OI::getJoystick2() {
	return joystick2;
}

Joystick* OI::getJoystick1() {
	return joystick1;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
