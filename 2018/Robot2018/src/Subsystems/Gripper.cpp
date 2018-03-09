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

#include "Gripper.h"
#include "../RobotMap.h"
#include "../Commands/GripperRun.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Gripper::Gripper() : frc::Subsystem("Gripper") {
	std::printf("2135: Gripper Constructor\n");

#ifndef ROBORIO_STANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL11 = RobotMap::gripperMotorL11;
    motorR12 = RobotMap::gripperMotorR12;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    std::printf("2135: Motor L11 ID %d ver %d.%d\n", motorL11->GetDeviceID(),
    		motorL11->GetFirmwareVersion()/256, motorL11->GetFirmwareVersion()%256);
    std::printf("2135: Motor R12 ID %d ver %d.%d\n", motorR12->GetDeviceID(),
    		motorR12->GetFirmwareVersion()/256, motorR12->GetFirmwareVersion()%256);

    // Initialize Variables
    RobotConfig* config = RobotConfig::GetInstance();
    config->GetValueAsDouble("GR_MotorSpeed", m_gripperSpeed, 1.0);

    // Set motor directions
    motorL11->SetInverted(false);
    motorR12->SetInverted(true);

    // Turn on Brake mode (not coast)
    motorL11->SetNeutralMode(NeutralMode::Brake);
    motorR12->SetNeutralMode(NeutralMode::Brake);

    // Set motor peak outputs
    motorL11->ConfigPeakOutputForward(m_gripperSpeed, m_timeout);
    motorL11->ConfigPeakOutputReverse(-m_gripperSpeed, m_timeout);
    motorR12->ConfigPeakOutputForward(m_gripperSpeed, m_timeout);
    motorR12->ConfigPeakOutputReverse(-m_gripperSpeed, m_timeout);

    // Initialize modes and set power to off
    motorL11->Set(ControlMode::PercentOutput, 0.0);
    motorR12->Set(ControlMode::PercentOutput, 0.0);
#endif
}

void Gripper::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
#ifndef ROBORIO_STANDALONE
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new GripperRun(0));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
#endif
}

void Gripper::Periodic() {
    // Put code here to be run every loop
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Gripper::Initialize(frc::Preferences *RobotConfig)
{
	std::printf("2135: Gripper Init\n");
}

void Gripper::SetGripperMotorSpeed(int direction)
{
	double outputL = 0.0; 		//Default: off
	double outputR = 0.0; 		//Default: off

	switch (direction)
	{
	default:
	case GRIPPER_STOP:
		outputL = 0.0;
		outputR = 0.0;
		break;
	case GRIPPER_FORWARD:
		outputL = m_gripperSpeed;
		outputR = m_gripperSpeed;
		break;
	case GRIPPER_REVERSE:
		outputL = -m_gripperSpeed;
		outputR = -m_gripperSpeed;
		break;
	case GRIPPER_SPIN:
		outputL = m_gripperSpeed;
		outputR = -m_gripperSpeed;
		break;
	}

#ifndef ROBORIO_STANDALONE
	motorL11->Set(ControlMode::PercentOutput, outputL);
	motorR12->Set(ControlMode::PercentOutput, outputR);
#endif
}
