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
    config->GetValueAsDouble("EB_PeakOut", m_peakOut, 0.8);
    config->GetValueAsInt("EB_Velocity", m_velocity, 249);
    config->GetValueAsInt("EB_Acceleration", m_acceleration, 499);
    config->GetValueAsInt("EB_SCurveStrength", m_sCurveStrength, 0);
    config->GetValueAsDouble("EB_PidKf", m_pidKf, 3.283);
    config->GetValueAsDouble("EB_PidKp", m_pidKp, 2.616);
    config->GetValueAsDouble("EB_PidKi", m_pidKi, 0.000);
    config->GetValueAsDouble("EB_PidKd", m_pidKd, 0.000);
	config->GetValueAsDouble("EB_ArbFeedForward", m_arbFeedForward, 0.18);
	config->GetValueAsDouble("EB_WristArbFF", m_wristArbFF, 0.07);
	config->GetValueAsDouble("EB_NeutralDeadband", m_neutralDeadband, 0.004);
	config->GetValueAsDouble("EB_ToleranceDegrees", m_toleranceDegrees, 5.0);
    config->GetValueAsInt("EB_MaxCounts", m_elbowMaxCounts, 0);
    config->GetValueAsInt("EB_MinCounts", m_elbowMinCounts, -2200);
	config->GetValueAsDouble("EB_CalibAngle", m_calibAngle, 108.3);
	config->GetValueAsDouble("EB_BumpAngle", m_bumpAngle, 5.0);
	config->GetValueAsDouble("EB_GroundCargoAngle", m_groundCargoAngle, 108.3);
	config->GetValueAsDouble("EB_GroundHatchAngle", m_groundHatchAngle, 108.3);
	config->GetValueAsDouble("EB_LoadingCargoAngle", m_loadingCargoAngle, 30.5);
	config->GetValueAsDouble("EB_LoadingHatchAngle", m_loadingHatchAngle, 108.3);
	config->GetValueAsDouble("EB_ShipCargoAngle", m_shipCargoAngle, 20.0);
	config->GetValueAsDouble("EB_ShipHatchAngle", m_shipHatchAngle, 108.3);
	config->GetValueAsDouble("EB_RocketL1CargoAngle", m_rocketL1CargoAngle, 108.3);
	config->GetValueAsDouble("EB_RocketL1HatchAngle", m_rocketL1HatchAngle, 108.3);
	config->GetValueAsDouble("EB_RocketL2CargoAngle", m_rocketL2CargoAngle, 9.91);
	config->GetValueAsDouble("EB_RocketL2HatchAngle", m_rocketL2HatchAngle, 9.91);
	config->GetValueAsDouble("EB_RocketL3CargoAngle", m_rocketL3CargoAngle, 9.91);
	config->GetValueAsDouble("EB_RocketL3HatchAngle", m_rocketL3HatchAngle, 9.91);
	config->GetValueAsDouble("EB_StowAngle", m_stowedAngle, 30.0); 

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
		motorEB10->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorEB10->EnableVoltageCompensation(true);
		motorEB10->ConfigNeutralDeadband(m_neutralDeadband, m_timeout);

		motorEB10->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, m_pidIndex, m_timeout);
		motorEB10->SetSensorPhase(false);
		m_curDegrees = CountsToDegrees(motorEB10->GetSelectedSensorPosition(m_pidIndex)); // TODO: WRITE COUNTS TO DEGREES 

		// Set maximum power
		motorEB10->ConfigPeakOutputForward(m_peakOut, m_timeout);
		motorEB10->ConfigPeakOutputReverse(-m_peakOut, m_timeout);

		// Set maximum current draw allowed - JVN predicts 10.8A
		motorEB10->ConfigPeakCurrentLimit(30, m_timeout);
		motorEB10->ConfigPeakCurrentDuration(2000, m_timeout);
		motorEB10->ConfigContinuousCurrentLimit(20, m_timeout);
		motorEB10->EnableCurrentLimit(true);

		// Set soft limits
		motorEB10->ConfigForwardSoftLimitThreshold(m_elbowMaxCounts, m_timeout);
		motorEB10->ConfigReverseSoftLimitThreshold(m_elbowMinCounts, m_timeout);
		motorEB10->ConfigForwardSoftLimitEnable(false, m_timeout);
		motorEB10->ConfigReverseSoftLimitEnable(false, m_timeout);

		// Configure Magic Motion settings
		motorEB10->SelectProfileSlot(0, 0);
		motorEB10->ConfigClosedLoopPeakOutput(0, m_peakOut, m_timeout);
        motorEB10->Config_kF(0, m_pidKf, m_timeout);      
        motorEB10->Config_kP(0, m_pidKp, m_timeout);
        motorEB10->Config_kI(0, m_pidKi, m_timeout);
        motorEB10->Config_kD(0, m_pidKd, m_timeout);
        motorEB10->ConfigMotionCruiseVelocity(m_velocity, m_timeout);   	// 90 degree rotation in 0.5*2 seconds
        motorEB10->ConfigMotionAcceleration(m_acceleration, m_timeout);		// 1 second to accelerate to max velocity
		motorEB10->ConfigMotionSCurveStrength(m_sCurveStrength, m_timeout);

		// Do not enable elbow Motion Magic - wait for calibration
     }

    // Initialize Variables
    m_targetDegrees = m_curDegrees;
    m_targetCounts = DegreesToCounts(m_curDegrees);
    m_calibrated = false;

    // Field for manually progamming elbow angle
	frc::SmartDashboard::PutNumber("EB Setpoint", m_curDegrees);
	frc::SmartDashboard::PutBoolean("EB Calibrated", m_calibrated);
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
	static int	i = 0;
    int			curCounts = 0;

	if (m_talonValidEB10) {
		curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);
	}
	m_curDegrees = CountsToDegrees(curCounts);

	frc::SmartDashboard::PutNumber("EB Counts", curCounts);
	frc::SmartDashboard::PutNumber("EB Degrees", m_curDegrees);

	// Update arbitrary feed forward if calibrated
	if (m_calibrated) {
		double	arbFF;

		arbFF = GetCurrentArbFeedForward();
		motorEB10->Set(ControlMode::MotionMagic, m_targetCounts, 
			DemandType::DemandType_ArbitraryFeedForward, arbFF);
	
		frc::SmartDashboard::PutNumber("EB ArbFF", arbFF);
	}

	if ((m_elbowDebug > 1) || (m_elbowDebug > 0 && m_isMoving)) {

		// SLow debug message rate to every 5 * 20ms periods
		if (i++ % 5 == 0) {
			double	outputEB10 = 0.0, currentEB10 = 0.0;
			double 	errorInDegrees = 0.0;

			errorInDegrees = CountsToDegrees(m_targetCounts - curCounts);

			if (m_talonValidEB10) {
				outputEB10 = motorEB10->GetMotorOutputPercent();
				currentEB10 = motorEB10->GetOutputCurrent();
			}
		
			double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

			// cts = Encoder Counts, error = Error In Degrees, Out = Motor Output
			std::printf("2135: EB %6.3f cts %5d deg %4.1f err %5.2f out %4.2f amp %6.3f\n", 
				secs, curCounts, CountsToDegrees(curCounts), errorInDegrees, outputEB10, currentEB10);

			frc::SmartDashboard::PutNumber("EB_Output_EB10", outputEB10);
			frc::SmartDashboard::PutNumber("EB_Current_EB10", currentEB10);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elbow::Initialize(void) {
	double	curCounts = 0.0;

	std::printf("2135: EB Elbow Init\n");
	// Set PID target to current encoder reading

	if (m_talonValidEB10) {
		motorEB10->Set(ControlMode::PercentOutput, 0.0);
		curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);
	}

	m_curDegrees = CountsToDegrees(curCounts);
	m_targetCounts = curCounts;
	m_targetDegrees = m_curDegrees;
	m_isMoving = false;
}

void Elbow::FaultDump(void) {
	//	Dump all Talon faults
	frc2135::TalonSRXUtils::TalonSRXFaultDump("EB 10", motorEB10);
}

double Elbow::DegreesToRadians(double degrees) {
	double radians;

	radians = degrees * (M_PI / 180);
	return radians;
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

double Elbow::GetCurrentDegrees(void) {
	int curCounts = 0;

	if (m_talonValidEB10)
		curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);

	m_curDegrees = CountsToDegrees(curCounts);
	return m_curDegrees;
}

double Elbow::GetCurrentArbFeedForward(void) {
	double	wristEffectiveAngle;
	double	wristArbFF;
	double	curArbFeedForward;

	// Wrist adjustment for effect on Elbow
	wristEffectiveAngle = Robot::wrist->GetCurrentDegrees() + m_curDegrees - 180.0;
	wristArbFF = sin(DegreesToRadians(wristEffectiveAngle)) * m_wristArbFF;
	curArbFeedForward = sin(DegreesToRadians(m_curDegrees)) * (m_arbFeedForward + wristArbFF);

	return curArbFeedForward;
}

void Elbow::BumpToPosition(bool direction) {
	m_bumpDir = direction;

	MoveToPositionInit(BUMP_ANGLE);
}

void Elbow::Calibrate() {

	if (m_talonValidEB10)
		motorEB10->SetSelectedSensorPosition(DegreesToCounts(m_calibAngle), m_pidIndex, m_timeout);

	m_calibrated = true;
	frc::SmartDashboard::PutBoolean("EB Calibrated", m_calibrated);
}

///////////////////////// MOTION MAGIC ///////////////////////////////////

void Elbow::MoveToPositionInit(int angle) {
	int curCounts = 0;
	bool isCargo;

	m_elbowAngle = angle;
	isCargo = Robot::oi->IsCargo();

	// Validate and set the requested angle to move
	switch (angle) {
	case NOCHANGE_ANGLE:	// Do not change from current angle!
		// m_targetDegrees = m_targetDegrees;
		break;
	case GROUND_ANGLE:
		m_targetDegrees = (isCargo) ? m_groundCargoAngle : m_groundHatchAngle;
		break;
	case SHIP_ANGLE:
		m_targetDegrees = (isCargo) ? m_shipCargoAngle : m_shipHatchAngle;
		break;
	case ROCKET_L1_ANGLE:
		m_targetDegrees = (isCargo) ? m_rocketL1CargoAngle : m_rocketL1HatchAngle;
		break;
	case ROCKET_L2_ANGLE:
		m_targetDegrees = (isCargo) ? m_rocketL2CargoAngle : m_rocketL2HatchAngle;
		break;
	case ROCKET_L3_ANGLE:
		m_targetDegrees = (isCargo) ? m_rocketL3CargoAngle : m_rocketL3HatchAngle;
		break;
	case SMARTDASH_ANGLE:
		m_targetDegrees = frc::SmartDashboard::GetNumber("EB Setpoint", 0.0);
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
		m_targetDegrees = (isCargo) ? m_loadingCargoAngle : m_loadingHatchAngle;
		break;
	default:
		std::printf("2135: EB invalid angle requested - %d\n", angle);
		return;
	}

	m_targetCounts = DegreesToCounts(m_targetDegrees);
	
	if (m_calibrated) {

		// Constrain input request to a valid and safe range
		// if (m_targetCounts < m_elbowMinCounts) {
		// 	std::printf("2135: EB m_targetCounts limited by m_elbowMinCounts %d\n", m_elbowMinCounts);
		// 	m_targetCounts = m_elbowMinCounts;
		// }
		// if (m_targetCounts > m_elbowMaxCounts) {
		// 	std::printf("2135: EB m_targetCounts limited by m_elbowMaxCounts %d\n", m_elbowMaxCounts);
		// 	m_targetCounts = m_elbowMaxCounts;
		// }

		// Get current position in inches and set position mode and target counts
		if (m_talonValidEB10)
			curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);
		m_curDegrees = CountsToDegrees(curCounts);

		//Start the safety timer.
		m_safetyTimeout = 1.5;
		m_safetyTimer.Reset();
		m_safetyTimer.Start();
 
		// Set Motion Magic control mode
		motorEB10->Set(ControlMode::MotionMagic, m_targetCounts, 
			DemandType::DemandType_ArbitraryFeedForward, GetCurrentArbFeedForward());

		std::printf("2135: EB Move degrees %5.2f -> %5.2f counts %d -> %d\n",
			m_curDegrees, m_targetDegrees, curCounts, m_targetCounts);

		if (angle != NOCHANGE_ANGLE)
			m_isMoving = true;
	}
	else {
		std::printf("2135: Elbow is not calibrated\n");
    	std::printf("2135: EB Init %d cts %5.2f deg\n", (int) m_targetCounts, m_targetDegrees);

		if (m_talonValidEB10)
			motorEB10->Set(ControlMode::PercentOutput, 0.0);
	}
}

bool Elbow::MoveToPositionIsFinished(void) {
	static int	withinTolerance = 0;
	bool 		isFinished = false;
	int 		curCounts = 0;
	double 		errorInDegrees = 0.0;

	// If a real move was requested, check for completion
	if (m_elbowAngle != NOCHANGE_ANGLE) {
		if (m_talonValidEB10) {
			curCounts = motorEB10->GetSelectedSensorPosition(m_pidIndex);
		}

		errorInDegrees = CountsToDegrees(m_targetCounts - curCounts);

		// Check to see if the error is in an acceptable number of inches.
		if (fabs(errorInDegrees) < m_toleranceDegrees) {
			if (++withinTolerance >= 5) {
				isFinished = true;
				std::printf("2135: EB Move Finished - Time %f\n", m_safetyTimer.Get());
			}
		}
		else {
			withinTolerance = 0;
		}
		
		// Check to see if the Safety Timer has timed out.
		if (m_safetyTimer.Get() >= m_safetyTimeout) {
			isFinished = true;
			std::printf("2135: EB Move Safety timer has timed out\n");
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
