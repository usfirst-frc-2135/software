// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Drivetrain.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS


Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {

    std::printf("2135: DT Drivetrain Constructor\n");
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL1.reset(new WPI_TalonSRX(1));
    
    
    motorR3.reset(new WPI_TalonSRX(3));
    
    
    diffDrive.reset(new frc::DifferentialDrive(*motorL1, *motorR3));
    AddChild("Diff Drive", diffDrive);
    diffDrive->SetSafetyEnabled(true);
        diffDrive->SetExpiration(0.25);
        diffDrive->SetMaxOutput(1.0);

    motorL2.reset(new WPI_TalonSRX(2));
    
    
    motorR4.reset(new WPI_TalonSRX(4));
    
    
    shifter.reset(new frc::DoubleSolenoid(0, 0, 1));
    AddChild("Shifter", shifter);
    

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidL1 = frc2135::TalonSRXUtils::TalonSRXCheck(motorL1, "DT", "L1");
    m_talonValidL2 = frc2135::TalonSRXUtils::TalonSRXCheck(motorL2, "DT", "L2");
    m_talonValidR3 = frc2135::TalonSRXUtils::TalonSRXCheck(motorR3, "DT", "R3");
    m_talonValidR4 = frc2135::TalonSRXUtils::TalonSRXCheck(motorR4, "DT", "R4");


    // Invert the direction of the motors
    // Set to brake mode (in comparison to coast)
    // Set Voltage Compensation to 12V
    // Set encoder as a CTRE magnetic in relative mode with sensor in phase with output
    if (m_talonValidL1) {
        motorL1->SetInverted(true);
        motorL1->SetNeutralMode(NeutralMode::Coast);
        motorL1->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorL1->EnableVoltageCompensation(true);

        motorL1->Set(ControlMode::PercentOutput, 0.0);
        motorL1->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorL1->SetSensorPhase(false);
        motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    }

    if (m_talonValidL2) {
        motorL2->Set(ControlMode::Follower, 1);
    	motorL2->SetInverted(InvertType::FollowMaster);
        motorL2->SetNeutralMode(NeutralMode::Coast);
        motorL2->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorL2->EnableVoltageCompensation(true);
    }

    if (m_talonValidR3) {
        motorR3->SetInverted(true);
        motorR3->SetNeutralMode(NeutralMode::Coast);
        motorR3->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorR3->EnableVoltageCompensation(true);

        motorR3->Set(ControlMode::PercentOutput, 0.0);
        motorR3->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorR3->SetSensorPhase(false);
        motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    }

    if (m_talonValidR4) {
        motorR4->Set(ControlMode::Follower, 3);
        motorR4->SetInverted(InvertType::FollowMaster);
        motorR4->SetNeutralMode(NeutralMode::Coast);
        motorR4->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorR4->EnableVoltageCompensation(true);
   }

    // Set to low gear (default)
    m_lowGear = true;
    MoveShiftGears(m_lowGear);

    // If either master drive talons are valid, enable safety timer
    diffDrive->SetSafetyEnabled(m_talonValidL1 || m_talonValidR3);
}

void Drivetrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Drivetrain::Periodic() {
    // Put code here to be run every loop
static int 	i = 0;
    int			encoderLeft = 0;
	int			encoderRight = 0;

    if (m_talonValidL1) {
		encoderLeft = motorL1->GetSelectedSensorPosition(m_pidIndex);
	}

	if (m_talonValidR3) {
		encoderRight = -motorR3->GetSelectedSensorPosition(m_pidIndex);
	}

	frc::SmartDashboard::PutNumber("DT_Encoder_L", encoderLeft);
	frc::SmartDashboard::PutNumber("DT_Encoder_R", encoderRight);

    if (m_driveDebug > 1 || (m_driveDebug > 0 && m_isMovingAuto)) {

		// SLow debug message rate to every 5 * 20ms periods
		if (i++ % 5 == 0) {
			double	outputL1 = 0.0, currentL1 = 0.0, currentL2 = 0.0;
			double	outputR3 = 0.0, currentR3 = 0.0, currentR4 = 0.0;

			if (m_talonValidL1) {
				outputL1 = motorL1->GetMotorOutputPercent();
				currentL1 = motorL1->GetOutputCurrent();
			}

			if (m_talonValidL2) {
				currentL2 = motorL2->GetOutputCurrent();
			}

			if (m_talonValidR3) {
				outputR3 = motorR3->GetMotorOutputPercent();
				currentR3 = motorR3->GetOutputCurrent();
			}

			if (m_talonValidR4) {
				currentR4 = motorR4->GetOutputCurrent();
			}

			double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

			std::printf("2135: DT %6.3f LR cts %5d %5d out %4.2f %4.2f amps %6.3f %6.3f %6.3f %6.3f\n",
				secs, encoderLeft, encoderRight, outputL1, outputR3, currentL1, currentL2, currentR3, currentR4);

			frc::SmartDashboard::PutNumber("DT_Output_L1", outputL1);
			frc::SmartDashboard::PutNumber("DT_Current_L1", currentL1);
			frc::SmartDashboard::PutNumber("DT_Current_L2", currentL2);

			frc::SmartDashboard::PutNumber("DT_Output_R3", outputR3);
			frc::SmartDashboard::PutNumber("DT_Current_R3", currentR3);
			frc::SmartDashboard::PutNumber("DT_Current_R4", currentR4);
		}
	}
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.


void Drivetrain::Initialize(void) {
	std::printf("2135: DT Initialize\n");

	// When disabled, low gear and coast mode to allow easier pushing
	m_lowGear = true;
	m_brakeMode = false;
	m_throttleZeroed = false;
	// If ENABLED and AUTON mode, set brake mode
	if (!frc::RobotState::IsDisabled()) {
		if (!frc::RobotState::IsOperatorControl()) {
			m_brakeMode = true;
		}
	}

	MoveShiftGears(m_lowGear);
    MoveSetBrakeMode(m_brakeMode);
	MoveStop();
}

void Drivetrain::FaultDump(void) {
	
	//	Dump all Talon faults
	frc2135::TalonSRXUtils::TalonSRXFaultDump("DT L1", motorL1);
	frc2135::TalonSRXUtils::TalonSRXFaultDump("DT L2", motorL2);
	frc2135::TalonSRXUtils::TalonSRXFaultDump("DT R3", motorR3);
	frc2135::TalonSRXUtils::TalonSRXFaultDump("DT R4", motorR4);

	// Dump Pigeon faults
	//frc2135::TalonSRXUtils::PigeonIMUFaultDump("DT IMU", gyro);
}

//	Joystick movement during Teleop

void Drivetrain::MoveWithJoystick(std::shared_ptr<frc::Joystick> throttleJstick, std::shared_ptr<frc::Joystick> turnJstick) {
	double xValue = 0.0;
	double yValue = 0.0;

	// If no separate turn stick, then assume Thrustmaster HOTAS 4
    if (turnJstick == nullptr) {
        xValue = throttleJstick->GetX();
	    yValue = throttleJstick->GetZ();
    }
    else {	// Separate throttle and turn stick
        xValue = turnJstick->GetX();
	    yValue = throttleJstick->GetY();
    }

    xValue *= m_driveXScaling;
	if (!m_lowGear) {
		yValue *= m_driveYScaling;
	}

	if (m_talonValidL1 || m_talonValidR3) {
	// If joystick reports a very small throttle value
		if (fabs(yValue) < 0.05) 
			m_throttleZeroed = true;

	// If throttle not zeroed, prevent joystick inputs from entering drive
		if (!m_throttleZeroed) {
			xValue = 0.0;
			yValue = 0.0;
		}
			
	diffDrive->ArcadeDrive(-yValue, xValue, true);

	}
}

//	Automatic Drive Spin movement

void Drivetrain::MoveSpin(bool spinRight) {
	double spinSpeed = m_driveSpin;

	if (!spinRight)
		spinSpeed *= -1.0;

	if (m_talonValidL1 || m_talonValidR3)
		diffDrive->TankDrive(spinSpeed, -spinSpeed, false);
}

void Drivetrain::MoveStop() {
	if (m_talonValidL1 || m_talonValidR3)
		diffDrive->TankDrive(0.0, 0.0, false);
}

//	Shift transmission gears

void Drivetrain::MoveShiftGears(bool lowGear) {
    m_lowGear = lowGear;

    std::printf("2135: DT %s Gear\n", (lowGear) ? "LOW" : "HIGH");
    frc::SmartDashboard::PutBoolean("DT Low Gear", lowGear);

    shifter->Set( (lowGear) ? shifter->kForward : shifter->kReverse);
}

//	Set Talon brake mode

void Drivetrain::MoveSetBrakeMode(bool brakeMode) {
	m_brakeMode = brakeMode;

	std::printf("2135: DT %s Mode\n", (brakeMode) ? "BRAKE" : "COAST");
	frc::SmartDashboard::PutBoolean("DT Brake Mode", brakeMode);

	NeutralMode brakeOutput;
	brakeOutput = (brakeMode) ? NeutralMode::Brake : NeutralMode::Coast;
	if (m_talonValidL1)
		motorL1->SetNeutralMode(brakeOutput);
	if (m_talonValidL2)
		motorL2->SetNeutralMode(brakeOutput);
	if (m_talonValidR3)
		motorR3->SetNeutralMode(brakeOutput);
	if (m_talonValidR4)
		motorR4->SetNeutralMode(brakeOutput);
}

double Drivetrain::InchesToCounts(double inches) {
	double counts;

	counts = (inches / m_circumInches) * COUNTS_PER_ROTATION;
	return counts;
}

double Drivetrain::CountsToInches(int counts) {
	double inches;

	inches = ((double) counts / COUNTS_PER_ROTATION) * m_circumInches;
	return inches;
}

double Drivetrain::GetEncoderPosition(int motorID) {
	int		ret = 0;

	switch (motorID) {
		case 1:			// Left Master
			if (m_talonValidL1)
				ret = motorL1->GetSelectedSensorPosition(m_pidIndex);
			break;
		case 3:			// Right Master
			if (m_talonValidR3)
				ret = motorR3->GetSelectedSensorPosition(m_pidIndex);
			break;
		default:
			break;
	}

	return ret;
}

void Drivetrain::ResetSensors(void) {
	if (m_talonValidL1) 
		motorL1->SetSelectedSensorPosition(0, m_pidIndex, 0);
	if (m_talonValidR3) 
		motorR3->SetSelectedSensorPosition(0, m_pidIndex, 0);
}

