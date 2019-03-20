// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Wrist.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/WRRun.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Wrist::Wrist() : frc::Subsystem("Wrist") {
    std::printf("2135: WR Wrist Constructor\n");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorWR12.reset(new WPI_TalonSRX(12));
    
    

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
     m_talonValidWR12 = frc2135::TalonSRXUtils::TalonSRXCheck(motorWR12, "WR", "W12");

    // Retrieve wrist modified parameters from RobotConfig
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("WR_PeakOut", m_peakOut, 0.8);
    config->GetValueAsInt("WR_Velocity", m_velocity, 240);
    config->GetValueAsInt("WR_Acceleration", m_acceleration, 240);
    config->GetValueAsInt("WR_SCurveStrength", m_sCurveStrength, 0);
    config->GetValueAsDouble("WR_PidKf", m_pidKf, 0.000);
    config->GetValueAsDouble("WR_PidKp", m_pidKp, 2.250);
    config->GetValueAsDouble("WR_PidKi", m_pidKi, 0.000);
    config->GetValueAsDouble("WR_PidKd", m_pidKd, 0.000);
	config->GetValueAsDouble("WR_ArbFeedForward", m_arbFeedForward, 0.09);
	config->GetValueAsDouble("WR_ToleranceDegrees", m_toleranceDegrees, 5.0);
    config->GetValueAsInt("WR_MaxCounts", m_wristMaxCounts, 0);
    config->GetValueAsInt("WR_MinCounts", m_wristMinCounts, -3000);
	config->GetValueAsDouble("WR_CalibAngle", m_calibAngle, 28.9);
	config->GetValueAsDouble("WR_BumpAngle", m_bumpAngle, 5.0);
	config->GetValueAsDouble("WR_GroundCargoAngle", m_groundCargoAngle, 81.0);
	config->GetValueAsDouble("WR_GroundHatchAngle", m_groundHatchAngle, 134.0);
	config->GetValueAsDouble("WR_LoadingCargoAngle", m_loadingCargoAngle, 42.8);
	config->GetValueAsDouble("WR_LoadingHatchAngle", m_loadingHatchAngle, 42.8);
	config->GetValueAsDouble("WR_ShipCargoAngle", m_shipCargoAngle, 42.8);
	config->GetValueAsDouble("WR_ShipHatchAngle", m_shipHatchAngle, 42.8);
	config->GetValueAsDouble("WR_RocketL1CargoAngle", m_rocketL1CargoAngle, 42.8);
	config->GetValueAsDouble("WR_RocketL1HatchAngle", m_rocketL1HatchAngle, 42.8);
	config->GetValueAsDouble("WR_RocketL2CargoAngle", m_rocketL2CargoAngle, 170.1);
	config->GetValueAsDouble("WR_RocketL2HatchAngle", m_rocketL2HatchAngle, 170.1);
	config->GetValueAsDouble("WR_RocketL3CargoAngle", m_rocketL3CargoAngle, 171);
	config->GetValueAsDouble("WR_RocketL3HatchAngle", m_rocketL3HatchAngle, 171);
	config->GetValueAsDouble("WR_StowAngle", m_stowedAngle, 133.0);

     if (m_talonValidWR12) {
		// Set the motor direction for the wrist
		// Set to brake mode (in comparison to coast)
	    // Set the control mode and target to initially disable any movement
	    // Configure the encoder
		 motorWR12->SetInverted(true);
	     motorWR12->SetNeutralMode(NeutralMode::Brake);
		 motorWR12->Set(ControlMode::PercentOutput, 0.0);
		 motorWR12->SetSafetyEnabled(false);

		// Enable voltage compensation
		motorWR12->ConfigVoltageCompSaturation(12.0, 0);
        motorWR12->EnableVoltageCompensation(true);

		// Configure sensor settings
		motorWR12->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, m_pidIndex, m_timeout);
		motorWR12->SetSensorPhase(false);
		m_curDegrees = CountsToDegrees(motorWR12->GetSelectedSensorPosition(m_pidIndex)); 

		// Set maximum power
		 motorWR12->ConfigPeakOutputForward(m_peakOut, m_timeout);
		 motorWR12->ConfigPeakOutputReverse(-m_peakOut, m_timeout);

		// Set maximum current draw allowed
		 motorWR12->ConfigPeakCurrentLimit(20.0, m_timeout);
		 motorWR12->EnableCurrentLimit(true);

		// Set soft limits
		 motorWR12->ConfigForwardSoftLimitThreshold(m_wristMaxCounts, m_timeout);
		 motorWR12->ConfigReverseSoftLimitThreshold(m_wristMinCounts, m_timeout);
		 motorWR12->ConfigForwardSoftLimitEnable(false, m_timeout);
		 motorWR12->ConfigReverseSoftLimitEnable(false, m_timeout);

	 	// Configure Magic Motion settings
		 motorWR12->SelectProfileSlot(0, 0);
		 motorWR12->ConfigClosedLoopPeakOutput(0, m_peakOut, m_timeout);
         motorWR12->Config_kF(0, m_pidKf, m_timeout);      
         motorWR12->Config_kP(0, m_pidKp, m_timeout);
         motorWR12->Config_kI(0, m_pidKi, m_timeout);
         motorWR12->Config_kD(0, m_pidKd, m_timeout);
         motorWR12->ConfigMotionCruiseVelocity(m_velocity, m_timeout);   // 90 degree rotation in 0.4*2 seconds
         motorWR12->ConfigMotionAcceleration(m_acceleration, m_timeout);		// 1 second to accelerate to max velocity
		 motorWR12->ConfigMotionSCurveStrength(m_sCurveStrength, m_timeout);

		// Enable wrist Motion Magic with existing sensor reading (no movement)
//		 motorWR12->Set(ControlMode::MotionMagic, (double)DegreesToCounts(m_curDegrees), DemandType::DemandType_ArbitraryFeedForward, m_arbFeedForward);
     }

    // Initialize Variables
    m_targetDegrees = m_curDegrees;
    m_targetCounts = DegreesToCounts(m_curDegrees);

    // Field for manually progamming wrist angle
	frc::SmartDashboard::PutNumber("WR Setpoint", m_curDegrees);
	frc::SmartDashboard::PutBoolean("WR Calibrated", false);

}

void Wrist::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new WRRun(-1));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Wrist::Periodic() {
    // Put code here to be run every loop
	static int	i = 0;
    int			curCounts = 0;

	if (m_talonValidWR12) {
		curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);
	}

	frc::SmartDashboard::PutNumber("WR Counts", curCounts);
	frc::SmartDashboard::PutNumber("WR Degrees", CountsToDegrees(curCounts));

	if ((m_wristDebug > 1) || (m_wristDebug > 0 && m_isMoving)) {

		// SLow debug message rate to every 5 * 20ms periods
		if (i++ % 5 == 0) {
			double	outputWR12 = 0.0, currentWR12 = 0.0;
			double 	errorInDegrees = 0.0;

			errorInDegrees = CountsToDegrees(m_targetCounts - curCounts);

			if (m_talonValidWR12) {
				outputWR12 = motorWR12->GetMotorOutputPercent();
				currentWR12 = motorWR12->GetOutputCurrent();
			}

			double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

			// cts = Encoder Counts, error = Error In Degrees, Out = Motor Output
			std::printf("2135: WR %6.3f cts %5d deg %4.1f err %4.1f out %4.2f amps %6.3f\n", 
				secs, curCounts, CountsToDegrees(curCounts), errorInDegrees, outputWR12, currentWR12);

			frc::SmartDashboard::PutNumber("WR_Output_WR12", outputWR12);
			frc::SmartDashboard::PutNumber("WR_Current_WR12", currentWR12);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Wrist::Initialize(void) {
	double	curCounts = 0.0;

	std::printf("2135: WR Wrist Init\n");
	// Set PID target to current encoder reading

	if (m_talonValidWR12) {
		motorWR12->Set(ControlMode::PercentOutput, 0.0);
		curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);
	}

	m_targetDegrees = CountsToDegrees(curCounts);
	m_isCargo = false;
}

void Wrist::FaultDump(void) {
	
	//	Dump all Talon faults
	frc2135::TalonSRXUtils::TalonSRXFaultDump("WR 12", motorWR12);
}

double Wrist::DegreesToRadians(double degrees) {
	double radians;

	radians = degrees * (M_PI / 180);
	return radians;
}

int Wrist::DegreesToCounts(double degrees) {
	int counts;

	// counts = -degrees * (counts / degree) * reduction
	counts = (int) round(-degrees * (COUNTS_PER_ROTATION / 360.0) * OUTPUT_SHAFT_REDUCTION);
	return counts;
}

double Wrist::CountsToDegrees(int counts) {
	double degrees;

	// degrees = -counts * (degrees / count) / reduction
	degrees = -(double)counts * (360.0 / COUNTS_PER_ROTATION) / OUTPUT_SHAFT_REDUCTION;
	return degrees;
}

double Wrist::GetCurrentDegrees() {
	int curCounts = 0;

	if (m_talonValidWR12)
		curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);

	m_curDegrees = CountsToDegrees(curCounts);
	return m_curDegrees;
}

void Wrist::MoveToPositionInit(int angle) {
	int curCounts = 0;

	m_wristLevel = angle;

	// Validate and set the requested angle to move
	switch (angle) {
	case NOCHANGE_ANGLE:	// Do not change from current angle!
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
		m_targetDegrees = frc::SmartDashboard::GetNumber("WR Setpoint", 0.0);
		break;
	case BUMP_ANGLE:
		double bumpAngle;
		bumpAngle = (m_bumpDir) ? -m_bumpAngle : m_bumpAngle;
		m_targetDegrees += bumpAngle;
		break;
	case STOW_ANGLE: 
		m_targetDegrees = m_stowedAngle;
		break;
	case LOADING_ANGLE:
		m_targetDegrees = (m_isCargo) ? m_loadingCargoAngle : m_loadingHatchAngle;
		break;
	default:
		std::printf("2135: WR invalid angle requested - %d\n", angle);
		return;
	}

	m_targetCounts = DegreesToCounts(m_targetDegrees);
    std::printf("2135: WR Init %d cts %5.2f deg\n", (int) m_targetCounts, m_targetDegrees);
	
	if (m_calibrated) {

		// Constrain input request to a valid and safe range
		if (m_targetCounts < m_wristMinCounts) {
			std::printf("2135: WR m_targetCounts limited by m_wristMinCounts %d\n", m_wristMinCounts);
			m_targetCounts = m_wristMinCounts;
		}
		if (m_targetCounts > m_wristMaxCounts) {
			std::printf("2135: WR m_targetCounts limited by m_wristMaxCounts %d\n", m_wristMaxCounts);
			m_targetCounts = m_wristMaxCounts;
		}

		// Get current position in inches and set position mode and target counts
		if (m_talonValidWR12)
			curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);
		m_curDegrees = CountsToDegrees(curCounts);

		//Start the safety timer.
		m_safetyTimeout = 1.5;
		m_safetyTimer.Reset();
		m_safetyTimer.Start();

		double tunedArbFF = sin(DegreesToRadians(m_targetDegrees)) * m_arbFeedForward;
 
		motorWR12->Set(ControlMode::MotionMagic, m_targetCounts, 
			DemandType::DemandType_ArbitraryFeedForward, tunedArbFF);

		std::printf("2135 ARB FEED FORWARD: %f\n", tunedArbFF);

		std::printf("2135: WR Move degrees %f -> %f counts %d -> %d\n",
			m_curDegrees, m_targetDegrees, curCounts, m_targetCounts);
		
		if (angle != NOCHANGE_ANGLE)
			m_isMoving = true;
	}
	else {
		std::printf("2135: Wrist is not calibrated\n");

		if (m_talonValidWR12)
			motorWR12->Set(ControlMode::PercentOutput, 0.0);
	}
}

bool Wrist::MoveToPositionIsFinished(void) {
	bool isFinished = false;
	int curCounts = 0;
	double errorInDegrees = 0.0;

	// If a real move was requested, check for completion
	if (m_wristLevel != NOCHANGE_ANGLE) {
		if (m_talonValidWR12) {
			curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);
		}

		errorInDegrees = CountsToDegrees(m_targetCounts - curCounts);

		// Check to see if the error is in an acceptable number of inches.
		if (fabs(errorInDegrees) < m_toleranceDegrees) {
			isFinished = true;
			std::printf("2135: WR Move Finished - Time %f\n", m_safetyTimer.Get());
		}
		
		// Check to see if the Safety Timer has timed out.
		if (m_safetyTimer.Get() >= m_safetyTimeout) {
			isFinished = true;
			std::printf("2135: WR Move Safety timer has timed out\n");
		}
	}

	if (isFinished) {
		m_safetyTimer.Stop();
		m_isMoving = false;
	}

	return isFinished;
}

void Wrist::BumpToPosition(bool direction) {
	m_bumpDir = direction;

	MoveToPositionInit(BUMP_ANGLE);
}

void Wrist::Calibrate() {

	if (m_talonValidWR12)

		motorWR12->SetSelectedSensorPosition(DegreesToCounts(m_calibAngle), m_pidIndex, m_timeout);

	frc::SmartDashboard::PutBoolean("WR Calibrated", true);
	m_calibrated = true;
}

void Wrist::SetGamePiece(bool cargo) {
	m_isCargo = cargo;
}
