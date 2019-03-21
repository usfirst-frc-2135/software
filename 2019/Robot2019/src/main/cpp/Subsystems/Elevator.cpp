// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Elevator.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/ELRun.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevator::Elevator() : frc::Subsystem("Elevator") {

    std::printf("2135: EL Elevator Constructor\n");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorEL7.reset(new WPI_TalonSRX(7));
    motorEL8.reset(new WPI_TalonSRX(8));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
	m_talonValidEL7 = frc2135::TalonSRXUtils::TalonSRXCheck(motorEL7, "EL", "7");
    m_talonValidEL8 = frc2135::TalonSRXUtils::TalonSRXCheck(motorEL8, "EL", "8");

    // Get any config file settings
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("EL_CalibSpeed", m_calibrationSpeed, 0.25);
	config->GetValueAsDouble("EL_PeakOut", m_peakOut, 1.0);
    config->GetValueAsInt("EL_Velocity", m_velocity, 1918);
    config->GetValueAsInt("EL_Acceleration", m_acceleration, 3836);
    config->GetValueAsInt("EL_SCurveStrength", m_sCurveStrength, 0);
    config->GetValueAsDouble("EL_PidKf", m_pidKf, 0.000);
    config->GetValueAsDouble("EL_PidKp", m_pidKp, 0.250);
    config->GetValueAsDouble("EL_PidKi", m_pidKi, 0.000);
    config->GetValueAsDouble("EL_PidKd", m_pidKd, 0.000);
	config->GetValueAsDouble("EL_ArbFeedForward", m_arbFeedForward, 0.06);
    config->GetValueAsDouble("EL_CLRampRate", m_CLRampRate, 0.250);
    config->GetValueAsInt("EL_CLAllowedError", m_CLAllowedError, 0);
	config->GetValueAsDouble("EL_ToleranceInches", m_toleranceInches, 0.5);
    config->GetValueAsDouble("EL_MaxHeight", m_elevatorMaxHeight, 32.0);
    config->GetValueAsDouble("EL_MinHeight", m_elevatorMinHeight, 0.0);
	config->GetValueAsDouble("EL_LowGearHeight", m_lowGearHeight, 15.00);
	config->GetValueAsDouble("EL_BumpHeight", m_bumpHeight, 1.0);
	config->GetValueAsDouble("EL_GroundCargoHeight", m_groundCargoHeight, 0.0);
	config->GetValueAsDouble("EL_GroundHatchHeight", m_groundHatchHeight, 0.0);
	config->GetValueAsDouble("EL_LoadingCargoHeight", m_loadingCargoHeight, 3.0);
	config->GetValueAsDouble("EL_LoadingHatchHeight", m_loadingHatchHeight, 3.0);
	config->GetValueAsDouble("EL_ShipCargoHeight", m_shipCargoHeight, 3.0);
	config->GetValueAsDouble("EL_ShipHatchHeight", m_shipHatchHeight, 3.0);
	config->GetValueAsDouble("EL_RocketL1CargoHeight", m_rocketL1CargoHeight, 6.5);
	config->GetValueAsDouble("EL_RocketL1HatchHeight", m_rocketL1HatchHeight, 3.0);
	config->GetValueAsDouble("EL_RocketL2CargoHeight", m_rocketL2CargoHeight, 0.0);
	config->GetValueAsDouble("EL_RocketL2HatchHeight", m_rocketL2HatchHeight, 11.0);
	config->GetValueAsDouble("EL_RocketL3CargoHeight", m_rocketL3CargoHeight, 10.5);
	config->GetValueAsDouble("EL_RocketL3HatchHeight", m_rocketL3HatchHeight, 10.5);

	// Initialize Talon SRX motor controller direction and encoder sensor slot
    // Set the control mode and target to disable any movement
    // Set to brake mode (in comparison to coast)
    // Set encoder as a CTRE magnetic in relative mode with sensor in phase with output
    if (m_talonValidEL7) {
	    motorEL7->SetInverted(false);						// Sets the Talon inversion to false
	    motorEL7->SetNeutralMode(NeutralMode::Brake);		// Set to brake mode (as opposed to coast)
		motorEL7->SetSafetyEnabled(false);

		// Enable voltage compensation
		 motorEL7->ConfigVoltageCompSaturation(12.0, m_timeout);
		 motorEL7->EnableVoltageCompensation(true);

		// Configure sensor settings
	    motorEL7->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
	    motorEL7->SetSensorPhase(true);
	    motorEL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

		// Set maximum power and ramp rate
		 motorEL7->ConfigPeakOutputForward(m_peakOut, m_timeout);
		 motorEL7->ConfigPeakOutputReverse(-m_peakOut, m_timeout);
		 motorEL7->ConfigClosedloopRamp(m_CLRampRate, m_timeout);

   		// Set allowable closed loop error
		 motorEL7->ConfigAllowableClosedloopError(m_slotIndex, m_CLAllowedError, m_timeout);

		// Set maximum current draw allowed
		 motorEL7->ConfigPeakCurrentLimit(20.0, m_timeout);
		 motorEL7->EnableCurrentLimit(false);
		
		// Set soft limits
		 motorEL7->ConfigForwardSoftLimitThreshold(InchesToCounts(m_elevatorMaxHeight), m_timeout);
	     motorEL7->ConfigReverseSoftLimitThreshold(InchesToCounts(m_elevatorMinHeight), m_timeout);
	     motorEL7->ConfigForwardSoftLimitEnable(true, m_timeout);
	     motorEL7->ConfigReverseSoftLimitEnable(true, m_timeout);

		// Configure Magic Motion settings
		 motorEL7->SelectProfileSlot(0, 0);
		 motorEL7->ConfigClosedLoopPeakOutput(0, m_peakOut, m_timeout);
         motorEL7->Config_kF(0, m_pidKf, m_timeout);      
         motorEL7->Config_kP(0, m_pidKp, m_timeout);
         motorEL7->Config_kI(0, m_pidKi, m_timeout);
         motorEL7->Config_kD(0, m_pidKd, m_timeout);
         motorEL7->ConfigMotionCruiseVelocity(m_velocity, m_timeout);   	// TODO: calculate
         motorEL7->ConfigMotionAcceleration(m_acceleration, m_timeout);
		 motorEL7->ConfigMotionSCurveStrength(m_sCurveStrength, m_timeout);

		 motorEL7->Set(ControlMode::PercentOutput, 0.0);
	}
	
	if (m_talonValidEL8) {
	    motorEL8->Set(ControlMode::Follower, 7);			// Set to follow Elevator Motor 7
	    motorEL8->SetInverted(InvertType::FollowMaster);	// Sets the Talon inversion to false
	    motorEL8->SetNeutralMode(NeutralMode::Brake);		// Set to brake mode (as opposed to coast)
		motorEL8->SetSafetyEnabled(false);

		// Enable voltage compensation
		motorEL8->ConfigVoltageCompSaturation(12.0, m_timeout);
		motorEL8->EnableVoltageCompensation(true);

		// Set maximum current draw allowed
		motorEL8->ConfigPeakCurrentLimit(20.0, m_timeout);
		motorEL8->EnableCurrentLimit(false);
	}

    // Initialize variables
    m_curInches = 0.0;
    m_targetInches = 0.0;
    m_targetCounts = 0;
    m_calibrated = false;
    m_calibrationState = 0;
	
    // Field for manually progamming elevator height
	frc::SmartDashboard::PutNumber("EL Setpoint", 0.0);
	frc::SmartDashboard::PutBoolean("EL Calibrated", m_calibrated);
}

void Elevator::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ELRun(-1));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Elevator::Periodic() {
    // Put code here to be run every loop
	static int	i = 0;
    int			curCounts = 0;

	if (m_talonValidEL7) {
		curCounts = motorEL7->GetSelectedSensorPosition(m_pidIndex);
	}

	// Put code here to be run every loop
	frc::SmartDashboard::PutBoolean("EL Calibrated", m_calibrated);
	frc::SmartDashboard::PutNumber("EL Height", CountsToInches(curCounts));
	frc::SmartDashboard::PutNumber("Del Height", 2 * CountsToInches(curCounts));

	if ((m_elevatorDebug > 1) || (m_elevatorDebug > 0 && m_isMoving)) {

		// SLow debug message rate to every 5 * 20ms periods
		if (i++ % 5 == 0) {
			double	outputEL7 = 0.0, currentEL7 = 0.0;
			double	outputEL8 = 0.0, currentEL8 = 0.0;
			double	errorInInches = 0.0;

			errorInInches = CountsToInches(m_targetCounts - curCounts);

			if (m_talonValidEL7) {
				outputEL7 = motorEL7->GetMotorOutputPercent();
				currentEL7 = motorEL7->GetOutputCurrent();
			}

			if (m_talonValidEL8) {
				outputEL8 = motorEL8->GetMotorOutputPercent();
				currentEL8 = motorEL8->GetOutputCurrent();
			}

			double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

			// cts = Encoder Counts, error = Error In Inches, Out = Motor Output
			std::printf("2135: EL %6.3f cts %5d in %5.2f err %5.2f out %4.2f %4.2f amps %6.3f %6.3f\n", 
				secs, (int)curCounts, CountsToInches(curCounts), errorInInches, outputEL7, outputEL8, currentEL7, currentEL8);

			frc::SmartDashboard::PutNumber("EL_Output_EL7", outputEL7);
			frc::SmartDashboard::PutNumber("EL_Current_EL7", currentEL7);
			frc::SmartDashboard::PutNumber("EL_Output_EL8", outputEL8);
			frc::SmartDashboard::PutNumber("EL_Current_EL8", currentEL8);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator:: Initialize(void) {
    double 	curCounts = 0.0;

    std::printf("2135: EL Elevator Init\n");

    // PID Target is set to current encoder counts
    if (m_talonValidEL7) {
		motorEL7->Set(ControlMode::PercentOutput, 0.0);
        curCounts = motorEL7->GetSelectedSensorPosition(m_pidIndex);
	}

    m_targetInches = CountsToInches(curCounts);
	m_isCargo = false;
	m_isMoving = false;
	std::printf("2135: EL Init Target Inches: %5.2f\n", m_targetInches);
}

void Elevator::FaultDump(void) {
	//	Dump all Talon faults
	frc2135::TalonSRXUtils::TalonSRXFaultDump("EL  7", motorEL7);
	frc2135::TalonSRXUtils::TalonSRXFaultDump("EL  8", motorEL8);
}

int Elevator::InchesToCounts(double inches) {
	int 	counts;

	counts = (int) round((inches / m_circumInches) * COUNTS_PER_ROTATION);
	return counts;
}

double Elevator::CountsToInches(int counts) {
	double 	inches;

	inches = ((double) counts / COUNTS_PER_ROTATION) * m_circumInches;
	return 	inches;
}

double Elevator::GetCurrentInches () {
	double 	curCounts = 0.0;

	if (m_talonValidEL7)
		curCounts = motorEL7->GetSelectedSensorPosition(m_pidIndex);

	m_curInches = CountsToInches(curCounts);
	return m_curInches;
}

// Elevator PID loop setup to do a bump movement

void Elevator::BumpToPosition(bool direction) {
	m_bumpDir = direction;

	MoveToPositionInit(BUMP_HEIGHT);
}

// Elevator PID calibration setup and initialization

void Elevator::CalibrationOverride() {
	if (m_talonValidEL7) {
		motorEL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
		motorEL7->Set(ControlMode::Position, 0.0);
	}
	m_calibrated = true;
}

void Elevator::SetGamePiece(bool cargo) {
	m_isCargo = cargo;
}

///////////////////////// MOTION MAGIC ///////////////////////////////////

void Elevator::MoveToPositionInit(int level) {
	int 	curCounts = 0;

	m_elevatorLevel = level;

	// Validate and set the requested position to move
	switch (level) {
	case NOCHANGE_HEIGHT:	// Do not change from current level!
		// m_targetInches = m_targetInches;
		break;
	case GROUND_HEIGHT:
		m_targetInches = (m_isCargo) ? m_groundCargoHeight : m_groundHatchHeight;
		break;
	case SHIP_HEIGHT:
		m_targetInches = (m_isCargo) ? m_shipCargoHeight : m_shipHatchHeight;
		break;
	case ROCKET_L1_HEIGHT:
		m_targetInches = (m_isCargo) ? m_rocketL1CargoHeight : m_rocketL1HatchHeight;
		break;
	case ROCKET_L2_HEIGHT:
		m_targetInches = (m_isCargo) ? m_rocketL2CargoHeight : m_rocketL2HatchHeight;
		break;
	case ROCKET_L3_HEIGHT:
		m_targetInches = (m_isCargo) ? m_rocketL3CargoHeight : m_rocketL3HatchHeight;
		break;
	case SMARTDASH_HEIGHT:
		m_targetInches = frc::SmartDashboard::GetNumber("EL Setpoint", 0.0);
		break;
	case BUMP_HEIGHT:
		double 	bumpHeight;
		bumpHeight = (m_bumpDir) ? m_bumpHeight : -m_bumpHeight;
		m_targetInches += bumpHeight;
		break;
	case LOADING_HEIGHT:
		m_targetInches = (m_isCargo) ? m_loadingCargoHeight : m_loadingHatchHeight;
		break;
	default:
		std::printf("2135: EL invalid height requested - %d\n", level);
		return;
	}

    m_targetCounts = InchesToCounts(m_targetInches);
    std::printf("2135: EL Init %d cts %5.2f in\n", (int) m_targetCounts, m_targetInches);
	
	if (m_calibrated) {

		// Constrain input request to a valid and safe range between full down and max height
		if (m_targetInches < m_elevatorMinHeight) {
			std::printf("2135: EL m_targetInches limited by m_elevatorMinHeight %f\n", m_elevatorMinHeight);
			m_targetInches = m_elevatorMinHeight;
		}
		if (m_targetInches > m_elevatorMaxHeight) {
			std::printf("2135: EL m_targetInches limited by m_elevatorMaxHeight %f\n", m_elevatorMaxHeight);
			m_targetInches = m_elevatorMaxHeight;
		}
		
		m_targetCounts = InchesToCounts(m_targetInches);

		// Get current position in inches and set position mode and target counts
		if (m_talonValidEL7)
			curCounts = motorEL7->GetSelectedSensorPosition(m_pidIndex);
		m_curInches = CountsToInches(curCounts);

		//Start the safety timer.
		m_safetyTimeout = 3.0;
		m_safetyTimer.Reset();
		m_safetyTimer.Start();

		motorEL7->Set(ControlMode::MotionMagic, m_targetCounts, 
			DemandType::DemandType_ArbitraryFeedForward, m_arbFeedForward);

		std::printf("2135: EL Move inches %f -> %f counts %d -> %d\n",
			m_curInches, m_targetInches, curCounts, m_targetCounts);
			
		if (level != NOCHANGE_HEIGHT)
			m_isMoving = true;
	}
	else {
		std::printf("2135: EL is not calibrated\n");

		if (m_talonValidEL7)
			motorEL7->Set(ControlMode::PercentOutput, 0.0);
		if (m_talonValidEL8)
			motorEL8->Set(ControlMode::PercentOutput, 0.0);
	}
}

bool Elevator::MoveToPositionIsFinished() {
	static int	withinTolerance = 0;
    bool 	isFinished = false;
    int 	curCounts = 0;
    double 	errorInInches = 0.0;

	// If a real move was requested, check for completion
	if (m_elevatorLevel != NOCHANGE_HEIGHT) {
		if (m_talonValidEL7) {
			curCounts = motorEL7->GetSelectedSensorPosition(m_pidIndex);
		}

		errorInInches = CountsToInches(m_targetCounts - curCounts);

		// Check to see if the error is in an acceptable number of inches.
		if (fabs(errorInInches) < m_toleranceInches) {
			if (++withinTolerance >= 5) {
			isFinished = true;
			std::printf("2135: EL Move Finished - Time %f\n", m_safetyTimer.Get());
		}
		}
		else {
			withinTolerance = 0;
		}
		
		// Check to see if the Safety Timer has timed out.
		if (m_safetyTimer.Get() >= m_safetyTimeout) {
			isFinished = true;
			std::printf("2135: EL Move Safety timer has timed out\n");
		}

	}

	// If completed, clean up
		if (isFinished) {
		withinTolerance = 0;
			m_safetyTimer.Stop();
			m_isMoving = false;
		}

    return isFinished;
}
