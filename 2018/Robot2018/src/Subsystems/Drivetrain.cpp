// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ctre/Phoenix.h"


#include "Drivetrain.h"
#include "../RobotMap.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/DriveTeleop.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {
	std::printf("2135: Drivetrain Constructor\n");
#ifdef ROBOTNOTSTANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL1 = RobotMap::drivetrainMotorL1;
    motorR3 = RobotMap::drivetrainMotorR3;
    diffDrive = RobotMap::drivetrainDiffDrive;
    motorL2 = RobotMap::drivetrainMotorL2;
    motorR4 = RobotMap::drivetrainMotorR4;
    shifter = RobotMap::drivetrainShifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    m_driveSpin = 0.0;

    //Invert the direction of the left hand side motors
    motorL1->SetInverted(false);
    motorL2->SetInverted(false);
    motorR3->SetInverted(true);
    motorR4->SetInverted(true);
    motorL1->Set(ControlMode::PercentOutput, 0.0);
    motorL2->Set(ControlMode::Follower, 1);
    motorR3->Set(ControlMode::PercentOutput, 0.0);
    motorR4->Set(ControlMode::Follower, 3);
    std::printf("2135: Motor L1 ID %d ver %d.%d\n", motorL1->GetDeviceID(), motorL1->GetFirmwareVersion()/256, motorL1->GetFirmwareVersion()%256);
    std::printf("2135: Motor L2 ID %d ver %d.%d\n", motorL2->GetDeviceID(), motorL2->GetFirmwareVersion()/256, motorL2->GetFirmwareVersion()%256);
    std::printf("2135: Motor R3 ID %d ver %d.%d\n", motorR3->GetDeviceID(), motorR3->GetFirmwareVersion()/256, motorR3->GetFirmwareVersion()%256);
    std::printf("2135: Motor R4 ID %d ver %d.%d\n", motorR4->GetDeviceID(), motorR4->GetFirmwareVersion()/256, motorR4->GetFirmwareVersion()%256);

    //Initialize drivetrain modifiers
    m_driveSpin = 0.5; 		//Initialize power setting used for spin turns

#endif
}

void Drivetrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
#ifdef ROBOTNOTSTANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
#endif
}

void Drivetrain::Periodic() {
    // Put code here to be run every loop

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivetrain::MoveWithJoystick(std::shared_ptr<Joystick> joystick)
{
#ifdef ROBOTNOTSTANDALONE
	diffDrive->ArcadeDrive(joystick->GetX(), joystick->GetY(), true);
#endif
}

//TODO: Replace numbers for DriveSpin with variables

void Drivetrain::MoveSpin(bool spinRight)
{
#ifdef ROBOTNOTSTANDALONE
	if(spinRight)
		diffDrive->TankDrive(0.5, 0.5, false);
	else
		diffDrive->TankDrive(-0.5, -0.5, false);
#endif
}

void Drivetrain::MoveShiftGears(bool lowGear)
{
#ifdef ROBOTNOTSTANDALONE
	if(lowGear) {
	    shifter->Set(shifter->kForward);
		m_lowGear = true;

	}

	else {
		shifter->Set(shifter->kReverse);
		m_lowGear = false;
	}
#endif
}
