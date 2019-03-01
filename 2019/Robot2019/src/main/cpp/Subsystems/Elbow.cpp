// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Elbow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/EBRun.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elbow::Elbow() : frc::Subsystem("Elbow") {
    std::printf("2135: EL Elbow Constructor\n");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorEB10.reset(new WPI_TalonSRX(10));
    
    

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    m_talonValidEB10 = frc2135::TalonSRXUtils::TalonSRXCheck(motorEB10, "EB", "EB10");

    // Retrieve elbow modified parameters from RobotConfig
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("EB_PidKp", m_pidKp, 0.25);
    config->GetValueAsDouble("EB_PidMaxOut", m_pidMaxOut, 0.6);
    config->GetValueAsDouble("EB_Velocity", m_velocity, 0.000);
    config->GetValueAsDouble("EB_Acceleration", m_acceleration, 0.000);
    config->GetValueAsDouble("EB_PidKp", m_pidKf, 0.000);
    config->GetValueAsDouble("EB_PidKp", m_pidKp, 0.000);
    config->GetValueAsDouble("EB_PidKi", m_pidKi, 0.000);
    config->GetValueAsDouble("EB_PidKd", m_pidKd, 0.000);
	config->GetValueAsDouble("EB_ArbFeedForward", m_arbFeedForward, 0.2);
	config->GetValueAsDouble("EB_ToleranceDegrees", m_toleranceDegrees, 5.0);
    config->GetValueAsInt("EB_MaxCounts", m_elbowMaxCounts, 1800);
    config->GetValueAsInt("EB_MinCounts", m_elbowMinCounts, 0);
	config->GetValueAsDouble("EB_BumpAngle", m_bumpAngle, 10.0);
	config->GetValueAsDouble("EB_GroundCargoAngle", m_groundCargoAngle, 0.0);
	config->GetValueAsDouble("EB_GroundHatchAngle", m_groundHatchAngle, 0.0);
	config->GetValueAsDouble("EB_ShipCargoAngle", m_shipCargoAngle, 20.0);
	config->GetValueAsDouble("EB_ShipHatchAngle", m_shipHatchAngle, 20.0);
	config->GetValueAsDouble("EB_RocketL1CargoAngle", m_rocketL1CargoAngle, 20.0);
	config->GetValueAsDouble("EB_RocketL1HatchAngle", m_rocketL1HatchAngle, 20.0);
	config->GetValueAsDouble("EB_RocketL2CargoAngle", m_rocketL2CargoAngle, 20.0);
	config->GetValueAsDouble("EB_RocketL2HatchAngle", m_rocketL2HatchAngle, 20.0);
	config->GetValueAsDouble("EB_RocketL3CargoAngle", m_rocketL3CargoAngle, 20.0);
	config->GetValueAsDouble("EB_RocketL3HatchAngle", m_rocketL3HatchAngle, 20.0);
	config->GetValueAsDouble("EB_StowAngle", m_stowedAngle, 20.0); 

     if (m_talonValidEB10) {
		// Set the motor direction for the elbow
	    // Set the control mode and target to initially disable any movement
	    // Set to brake mode (in comparison to coast)
	    // Configure the encoder
		 motorEB10->SetInverted(false);
	     motorEB10->SetNeutralMode(NeutralMode::Brake);
		 motorEB10->Set(ControlMode::PercentOutput, 0.0);
		 motorEB10->SetSafetyEnabled(false);
		
		// Enable voltage compensation
		 motorEB10->ConfigVoltageCompSaturation(12.0, 0);
         motorEB10->EnableVoltageCompensation(true);

		 motorEB10->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, m_pidIndex, m_timeout);
		 motorEB10->SetSensorPhase(false);
		 m_curDegrees = CountsToDegrees(motorEB10->GetSelectedSensorPosition(m_pidIndex)); // TODO: WRITE COUNTS TO DEGREES 

		// Set maximum power
		 motorEB10->ConfigPeakOutputForward(m_pidMaxOut, m_timeout);
		 motorEB10->ConfigPeakOutputReverse(-m_pidMaxOut, m_timeout);
		 motorEB10->ConfigClosedLoopPeakOutput(m_pidMaxOut, m_timeout);

		// Set maximum current draw allowed
		 motorEB10->ConfigPeakCurrentLimit(20.0, m_timeout);
		 motorEB10->EnableCurrentLimit(true);

		// Set soft limits
		 motorEB10->ConfigForwardSoftLimitThreshold(m_elbowMaxCounts, m_timeout);
		 motorEB10->ConfigReverseSoftLimitThreshold(m_elbowMinCounts, m_timeout);
		 motorEB10->ConfigForwardSoftLimitEnable(true, m_timeout);
		 motorEB10->ConfigReverseSoftLimitEnable(true, m_timeout);

		// Configure Magic Motion settings
		 motorEB10->SelectProfileSlot(0, 0);
         motorEB10->Config_kF(0, m_pidKf, m_timeout);      
         motorEB10->Config_kP(0, m_pidKp, m_timeout);
         motorEB10->Config_kI(0, m_pidKi, m_timeout);
         motorEB10->Config_kD(0, m_pidKd, m_timeout);
         motorEB10->ConfigMotionCruiseVelocity(m_velocity, m_timeout);   	// 90 degree rotation in 0.5*2 seconds
         motorEB10->ConfigMotionAcceleration(m_acceleration, m_timeout);		// 1 second to accelerate to max velocity

		// Enable elbow Motion Magic with existing sensor reading (no movement)
//		 motorEB10->Set(ControlMode::MotionMagic, (double)DegreesToCounts(m_curDegrees), DemandType::DemandType_ArbitraryFeedForward, m_arbFeedForward);
     }

    // Initialize Variables
    m_targetDegrees = m_curDegrees;
    m_targetCounts = DegreesToCounts(m_curDegrees);

    // Field for manually progamming elbow angle
	frc::SmartDashboard::PutNumber("EB Setpoint", m_curDegrees);
	frc::SmartDashboard::PutBoolean("EB Calibrated", false);

}

void Elbow::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new EBRun(-1));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Elbow::Periodic() {
    // Put code here to be run every loop
    int		curCounts = 0;

	if (m_talonValidEB10) {
		curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);
	}

	frc::SmartDashboard::PutNumber("EB Counts", curCounts);
	frc::SmartDashboard::PutNumber("EB Degrees", CountsToDegrees(curCounts));

	if (m_elbowDebug > 0) {
		double	outputEB10 = 0.0, currentEB10 = 0.0;
		double 	errorInDegrees = 0.0;

		errorInDegrees = CountsToDegrees(m_targetCounts - curCounts);

		if (m_talonValidEB10) {
			outputEB10 = motorEB10->GetMotorOutputPercent();
			currentEB10 = motorEB10->GetOutputCurrent();
		}
	
		double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

		// cts = Encoder Counts, error = Error In Degrees, Out = Motor Output
		std::printf("2135: EB MM %5.3f cts %d, degrees %5.2f, error %5.2f, Out %4.2f, Amps %6.3f\n", 
			secs, curCounts, CountsToDegrees(curCounts), errorInDegrees, outputEB10, currentEB10);

		frc::SmartDashboard::PutNumber("EB_Output_EB10", outputEB10);
		frc::SmartDashboard::PutNumber("EB_Current_EB10", currentEB10);
	}
}

///////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elbow::Initialize(void) {
	double	curCounts = 0.0;

	std::printf("2135: EB Elbow Init\n");
	// Set PID target to current encoder reading

	if (m_talonValidEB10)
		curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);

	m_targetDegrees = CountsToDegrees(curCounts);
	m_isCargo = false;
}

void Elbow::FaultDump(void) {
	//	Dump all Talon faults
	frc2135::TalonSRXUtils::TalonSRXFaultDump("EB 10", motorEB10);
}

int Elbow::DegreesToCounts(double degrees) {
	int counts;

	// counts = -degrees * (counts / degree) * reduction
	counts = (int) round(-degrees * (COUNTS_PER_ROTATION / 360.0) * OUTPUT_SHAFT_REDUCTION);
	return counts;
}

double Elbow::CountsToDegrees(int counts) {
	double degrees;

	// degrees = -counts * (degrees / count) / reduction
	degrees = -(double)counts * (360.0 / COUNTS_PER_ROTATION) / OUTPUT_SHAFT_REDUCTION;
	return degrees;
}

double Elbow::GetCurrentDegrees() {
	int curCounts = 0;

	if (m_talonValidEB10)
		curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);

	m_curDegrees = CountsToDegrees(curCounts);
	return m_curDegrees;
}

void Elbow::MoveToPositionInit(int level) {
	int curCounts = 0;

	m_elbowLevel = level;

	// Validate and set the requested level to move
	switch (level) {
	case NOCHANGE_ANGLE:	// Do not change from current level!
		// m_targetDegrees = m_targetDegrees;
		break;
	case GROUND_ANGLE:
		m_targetDegrees = (m_isCargo) ? m_groundCargoAngle : m_groundHatchAngle;
		break;
	case SHIP_ANGLE:
		m_targetDegrees = (m_isCargo) ? m_shipCargoAngle : m_shipHatchAngle;
		break;
	case ROCKET_L1_ANGLE:
		m_targetDegrees = (m_isCargo) ? m_rocketL1CargoAngle : m_rocketL1HatchAngle;
		break;
	case ROCKET_L2_ANGLE:
		m_targetDegrees = (m_isCargo) ? m_rocketL2CargoAngle : m_rocketL2HatchAngle;
		break;
	case ROCKET_L3_ANGLE:
		m_targetDegrees = (m_isCargo) ? m_rocketL3CargoAngle : m_rocketL3HatchAngle;
		break;
	case SMARTDASH_ANGLE:
		m_targetDegrees = frc::SmartDashboard::GetNumber("EB Setpoint", 0.0);
		break;
	case BUMP_ANGLE:
		double bumpAngle;
		bumpAngle = (m_bumpDir) ? m_bumpAngle : -m_bumpAngle;
		m_targetDegrees += bumpAngle;
		break;
	case STOW_ANGLE: 
		m_targetDegrees = m_stowedAngle; 
		break;
	default:
		std::printf("2135: EB invalid angle requested - %d\n", level);
		return;
	}

	m_targetCounts = DegreesToCounts(m_targetDegrees);
    std::printf("2135: EB MM Init %d counts, %5.2f degrees\n", (int) m_targetCounts, m_targetDegrees);
	
	if (m_calibrated) {

		// Constrain input request to a valid and safe range
		if (m_targetCounts < m_elbowMinCounts) {
			std::printf("2135: EB MM m_targetCounts limited by m_elbowMinCounts %d\n", m_elbowMinCounts);
			m_targetCounts = m_elbowMinCounts;
		}
		if (m_targetCounts > m_elbowMaxCounts) {
			std::printf("2135: EB MM m_targetCounts limited by m_elbowMaxCounts %d\n", m_elbowMaxCounts);
			m_targetCounts = m_elbowMaxCounts;
		}

		// Get current position in inches and set position mode and target counts
		if (m_talonValidEB10)
			curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);
		m_curDegrees = CountsToDegrees(curCounts);

		//Start the safety timer.
		m_safetyTimeout = 1.5;
		m_safetyTimer.Reset();
		m_safetyTimer.Start();
 
		// motorEB10->Set(ControlMode::MotionMagic, m_targetCounts);
		motorEB10->Set(ControlMode::MotionMagic, m_targetCounts, DemandType::DemandType_ArbitraryFeedForward, m_arbFeedForward);

		std::printf("2135: EB MM Move degrees %5.2f -> %5.2f counts %d -> %d\n",
			m_curDegrees, m_targetDegrees, curCounts, m_targetCounts);		
	}
	else {
		std::printf("2135: Elbow is not calibrated\n");

		if (m_talonValidEB10)
			motorEB10->Set(ControlMode::PercentOutput, 0.0);
	}
}

bool Elbow::MoveToPositionIsFinished(void) {
	bool isFinished = false;
	int curCounts = 0;
	double errorInDegrees = 0.0;

	// If a real move was requested, check for completion
	if (m_elbowLevel != NOCHANGE_ANGLE) {
		if (m_talonValidEB10) {
			curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);
		}

		errorInDegrees = CountsToDegrees(m_targetCounts - curCounts);

		// Check to see if the error is in an acceptable number of inches.
		if (fabs(errorInDegrees) < m_toleranceDegrees) {
			isFinished = true;
			std::printf("2135: EB MM Move Finished - Time %f\n", m_safetyTimer.Get());
		}
		
		// Check to see if the Safety Timer has timed out.
		if (m_safetyTimer.Get() >= m_safetyTimeout) {
			isFinished = true;
			std::printf("2135: EB Move Safety timer has timed out\n");
		}
	}

	if (isFinished) {
		m_safetyTimer.Stop();
	}

	return isFinished;
}

void Elbow::BumpToPosition(bool direction) {
	m_bumpDir = direction;

	MoveToPositionInit(BUMP_ANGLE);
}

void Elbow::Calibrate() {

	if (m_talonValidEB10)
		motorEB10->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

	frc::SmartDashboard::PutBoolean("EB Calibrated", true);
	m_calibrated = true;
}

void Elbow::SetGamePiece(bool cargo) {
	m_isCargo = cargo;
}


