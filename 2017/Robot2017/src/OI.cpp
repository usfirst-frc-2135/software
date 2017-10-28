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
#include "Commands/AgitatorMotorControl.h"
#include "Commands/AutonDefault.h"
#include "Commands/AutonDelay.h"
#include "Commands/AutonDriveDistance.h"
#include "Commands/AutonDrivePeg1Turn.h"
#include "Commands/AutonDrivePeg3Turn.h"
#include "Commands/AutonDrivePegVision.h"
#include "Commands/AutonDriveTurn.h"
#include "Commands/AutonDriveTurnTest.h"
#include "Commands/AutonPos123Move.h"
#include "Commands/AutonPos1DeliverGear.h"
#include "Commands/AutonPos2DeliverGear.h"
#include "Commands/AutonPos2VisionDeliverGear.h"
#include "Commands/AutonPos3DeliverGear.h"
#include "Commands/AutonTestingMode.h"
#include "Commands/ClimberMotorControl.h"
#include "Commands/ClimberMotorLowControl.h"
#include "Commands/DriveShift.h"
#include "Commands/DriveShiftToggle.h"
#include "Commands/DriveSpin.h"
#include "Commands/DriveStop.h"
#include "Commands/DriveTeleop.h"
#include "Commands/DriveTrainInvert.h"
#include "Commands/GearDoorControl.h"
#include "Commands/IntakeMotorControl.h"
#include "Commands/LightToggle.h"
#include "Commands/ShooterGateControl.h"
#include "Commands/ShooterMotorControl.h"
#include "Commands/VisionAllPipelinesOff.h"
#include "Commands/VisionGearPipelineOn.h"
#include "Commands/VisionShooterPipelineOn.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    operatorPanelB.reset(new Joystick(2));
    
    operAllCamerasOff.reset(new JoystickButton(operatorPanelB.get(), 8));
    operAllCamerasOff->WhenPressed(new VisionAllPipelinesOff());
    operShooterCameraOn.reset(new JoystickButton(operatorPanelB.get(), 7));
    operShooterCameraOn->WhenPressed(new VisionShooterPipelineOn());
    operGearCameraOn.reset(new JoystickButton(operatorPanelB.get(), 5));
    operGearCameraOn->WhenPressed(new VisionGearPipelineOn());
    operClimberLowSpeed.reset(new JoystickButton(operatorPanelB.get(), 3));
    operClimberLowSpeed->WhileHeld(new ClimberMotorLowControl(0));
    operClimberReverse.reset(new JoystickButton(operatorPanelB.get(), 2));
    operClimberReverse->WhileHeld(new ClimberMotorControl(-1));
    operClimberForward.reset(new JoystickButton(operatorPanelB.get(), 1));
    operClimberForward->WhileHeld(new ClimberMotorControl(1));
    operatorPanelA.reset(new Joystick(1));
    
    operGearDoorClose.reset(new JoystickButton(operatorPanelA.get(), 11));
    operGearDoorClose->WhenPressed(new GearDoorControl(false));
    operGearDoorOpen.reset(new JoystickButton(operatorPanelA.get(), 10));
    operGearDoorOpen->WhenPressed(new GearDoorControl(true));
    operLightOn.reset(new JoystickButton(operatorPanelA.get(), 9));
    operLightOn->WhenPressed(new LightToggle());
    operShooterOn.reset(new JoystickButton(operatorPanelA.get(), 8));
    operShooterOn->WhileHeld(new ShooterMotorControl(true));
    operBallGateClose.reset(new JoystickButton(operatorPanelA.get(), 6));
    operBallGateClose->WhenPressed(new ShooterGateControl(false));
    operBallGateOpen.reset(new JoystickButton(operatorPanelA.get(), 5));
    operBallGateOpen->WhenPressed(new ShooterGateControl(true));
    operAgitatorReverse.reset(new JoystickButton(operatorPanelA.get(), 4));
    operAgitatorReverse->WhileHeld(new AgitatorMotorControl(-1));
    operAgitatorForward.reset(new JoystickButton(operatorPanelA.get(), 3));
    operAgitatorForward->WhileHeld(new AgitatorMotorControl(1));
    operIntakeExpel.reset(new JoystickButton(operatorPanelA.get(), 2));
    operIntakeExpel->WhileHeld(new IntakeMotorControl(-1));
    operIntakeAcquire.reset(new JoystickButton(operatorPanelA.get(), 1));
    operIntakeAcquire->WhileHeld(new IntakeMotorControl(1));
    driverJoystick.reset(new Joystick(0));
    
    driverGearDoorClose11.reset(new JoystickButton(driverJoystick.get(), 11));
    driverGearDoorClose11->WhenPressed(new GearDoorControl(false));
    driverClimberForward10.reset(new JoystickButton(driverJoystick.get(), 10));
    driverClimberForward10->WhileHeld(new ClimberMotorControl(1));
    driverClimberLowPower9.reset(new JoystickButton(driverJoystick.get(), 9));
    driverClimberLowPower9->WhileHeld(new ClimberMotorLowControl(1));
    driverClimberLowPower8.reset(new JoystickButton(driverJoystick.get(), 8));
    driverClimberLowPower8->WhileHeld(new ClimberMotorLowControl(1));
    driverClimberForward7.reset(new JoystickButton(driverJoystick.get(), 7));
    driverClimberForward7->WhileHeld(new ClimberMotorControl(1));
    driverGearDoorClosed6.reset(new JoystickButton(driverJoystick.get(), 6));
    driverGearDoorClosed6->WhenPressed(new GearDoorControl(false));
    driverSpinRight.reset(new JoystickButton(driverJoystick.get(), 5));
    driverSpinRight->WhileHeld(new DriveSpin(false));
    driverSpinLeft.reset(new JoystickButton(driverJoystick.get(), 4));
    driverSpinLeft->WhileHeld(new DriveSpin(true));
    driverAlignGear.reset(new JoystickButton(driverJoystick.get(), 3));
    driverAlignGear->WhenPressed(new DriveShift(false));
    driverShiftToggle.reset(new JoystickButton(driverJoystick.get(), 2));
    driverShiftToggle->WhenPressed(new DriveShiftToggle());
    driverShift.reset(new JoystickButton(driverJoystick.get(), 1));
    driverShift->WhileHeld(new DriveShift(true));

    // SmartDashboard Buttons
    SmartDashboard::PutData("Auton Pos 2 Vision Deliver Gear", new AutonPos2VisionDeliverGear());
    SmartDashboard::PutData("Auton Testing Mode", new AutonTestingMode());
    SmartDashboard::PutData("Auton Drive Peg Vision", new AutonDrivePegVision());
    SmartDashboard::PutData("Auton Drive Distance: DEFAULT", new AutonDriveDistance(0));
    SmartDashboard::PutData("Auton Drive Turn Test", new AutonDriveTurnTest());
    SmartDashboard::PutData("Auton Pos 3 Deliver Gear", new AutonPos3DeliverGear());
    SmartDashboard::PutData("Auton Pos 2 Deliver Gear", new AutonPos2DeliverGear());
    SmartDashboard::PutData("Auton Pos 1 Deliver Gear", new AutonPos1DeliverGear());
    SmartDashboard::PutData("Auton Pos 123 Move", new AutonPos123Move());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getDriverJoystick() {
   return driverJoystick;
}

std::shared_ptr<Joystick> OI::getOperatorPanelA() {
   return operatorPanelA;
}

std::shared_ptr<Joystick> OI::getOperatorPanelB() {
   return operatorPanelB;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
