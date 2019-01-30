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
    config->GetValueAsDouble("WR_PidKp", m_pidKp, 0.375);
    config->GetValueAsDouble("WR_PidMaxOut", m_pidMaxOut, 1.0);
    config->GetValueAsDouble("WR_CLRampRate", m_CLRampRate, 0.080);
    config->GetValueAsInt("WR_CLAllowedError", m_CLAllowedError, 0);
	config->GetValueAsDouble("WR_ToleranceDegrees", m_toleranceDegrees, 5.0);
    config->GetValueAsInt("WR_MaxCounts", m_wristMaxCounts, 0);
    config->GetValueAsInt("WR_MinCounts", m_wristMinCounts, -1800);
	config->GetValueAsDouble("WR_BumpAngle", m_bumpAngle, 10.0);
	// config->GetValueAsDouble("WR_WristFlat", m_flatAngle, 5.0);

     if (m_talonValidWR12) {
		// Set the motor direction for the wrist
	    // Set the control mode and target to initially disable any movement
	    // Set to brake mode (in comparison to coast)
	    // Configure the encoder
		motorWR12->SetInverted(false);
	    motorWR12->SetNeutralMode(NeutralMode::Brake);
	    motorWR12->Set(ControlMode::PercentOutput, 0.0);
		motorWR12->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, m_pidIndex, m_timeout);
		motorWR12->SetSensorPhase(false);
		m_curDegrees = CountsToDegrees(motorWR12->GetSelectedSensorPosition(m_pidIndex)); //WRITE COUNTS TO DEGREES 

		// Set maximum power and ramp rate
		// Set maximum current draw allowed

	 	// Set proportional constant
		// Set closed loop error
		motorWR12->ConfigPeakOutputForward(m_pidMaxOut, m_timeout);
		motorWR12->ConfigPeakOutputReverse(-m_pidMaxOut, m_timeout);
		motorWR12->ConfigClosedloopRamp(m_CLRampRate, m_timeout);
		motorWR12->Config_kP(m_slotIndex, m_pidKp, m_timeout);
		motorWR12->ConfigAllowableClosedloopError(m_slotIndex, m_CLAllowedError, m_timeout);

		motorWR12->ConfigForwardSoftLimitThreshold(m_wristMaxCounts, m_timeout);
		motorWR12->ConfigReverseSoftLimitThreshold(m_wristMinCounts, m_timeout);
		motorWR12->ConfigForwardSoftLimitEnable(true, m_timeout);
		motorWR12->ConfigReverseSoftLimitEnable(true, m_timeout);

		motorWR12->ConfigPeakCurrentLimit(10.0, m_timeout);
		motorWR12->EnableCurrentLimit(true);

		// Enable wrist PID with existing sensor reading (no movement)
		motorWR12->Set(ControlMode::Position, (double)DegreesToCounts(m_curDegrees));
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


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Wrist::Periodic() {
    // Put code here to be run every loop
    int		curCounts = 0;
	double	outputWR12 = 0.0, currentWR12 = 0.0;

	if (m_talonValidWR12) {
		curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);
		outputWR12 = motorWR12->GetMotorOutputVoltage();
		currentWR12 = motorWR12->GetOutputCurrent();
	}

	if (m_wristDebug) {
		frc::SmartDashboard::PutNumber("WR Counts", curCounts);
		frc::SmartDashboard::PutNumber("WR Degrees", CountsToDegrees(curCounts));
		frc::SmartDashboard::PutNumber("WR_Output_WR12", outputWR12);
		frc::SmartDashboard::PutNumber("WR_Current_WR12", currentWR12);
	}

}

///////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Wrist::Initialize(void) {
	double	curCounts = 0.0;

	std::printf("2135: WR Wrist Init\n");
	// Set PID target to current encoder reading

	if (m_talonValidWR12)
		curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);

	m_targetDegrees = CountsToDegrees(curCounts);
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

void Wrist::MoveToPosition(int level)
{
	int curCounts = 0;

	m_wristLevel = level;

	// Validate and set the requested level to move
	switch (level) {
	case WRIST_NOCHANGE:	// Do not change from current level!
		// m_targetDegrees = m_targetDegrees;
		break;
	// case WRIST_FLAT:
	// 	m_targetDegrees = m_flatAngle;
	// 	break;
	case WRIST_SMARTDASH:
		m_targetDegrees = frc::SmartDashboard::GetNumber("WR Setpoint", 0.0);
		break;
	case BUMP_ANGLE:
		double bumpAngle;
		bumpAngle = (m_bumpDir) ? m_bumpAngle : -m_bumpAngle;
		m_targetDegrees += bumpAngle;
		break;
	default:
		std::printf("2135: WR invalid angle requested - %d\n", level);
		return;
	}

	// Constrain input request to a valid and safe range between full down and max height
	std::printf("2135: WR m_targetDegrees: %f, counts: %d\n",
			m_targetDegrees, DegreesToCounts(m_targetDegrees));

	if (m_targetDegrees > CountsToDegrees(m_wristMinCounts)) {
		std::printf("2135: WR m_targetDegrees limited by m_wristMinCounts %d\n", m_wristMinCounts);
		m_targetDegrees = CountsToDegrees(m_wristMinCounts);
	}
	if (m_targetDegrees < CountsToDegrees(m_wristMaxCounts)) {
		std::printf("2135: WR m_targetDegrees limited by m_wristMaxCounts %d\n", m_wristMaxCounts);
		m_targetDegrees = CountsToDegrees(m_wristMaxCounts);
	}

	m_targetCounts = DegreesToCounts(m_targetDegrees);

	if (m_talonValidWR12)
		curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);
	m_curDegrees = CountsToDegrees(curCounts);

	//Start the safety timer.
	m_safetyTimeout = 1.5;
	m_safetyTimer.Reset();
	m_safetyTimer.Start();

	// Set the mode and target
	if (m_talonValidWR12)
		motorWR12->Set(ControlMode::Position, (double)m_targetCounts);

	std::printf("2135: WR Move degrees %f -> %f counts %d -> %d\n",
			m_curDegrees, m_targetDegrees, curCounts, m_targetCounts);
}

bool Wrist::MoveToPositionIsFinished(void) {
	bool pidFinished = false;
	int curCounts = 0;
	int closedLoopError = 0;
	double motorOutput = 0.0;
	double errorInDegrees = 0;

	// If a real move was requested, check for completion
	if (m_wristLevel != WRIST_NOCHANGE) {
		if (m_talonValidWR12) {
			curCounts = motorWR12->GetSelectedSensorPosition(m_pidIndex);
			motorOutput = motorWR12->GetMotorOutputPercent();
		}

		double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

		closedLoopError = m_targetCounts - curCounts;
		errorInDegrees = CountsToDegrees(closedLoopError);

		// cts = Encoder Counts, CLE = Closed Loop Error, Out = Motor Output
		std::printf("2135: WR %5.3f cts %d, deg %4.1f, CLE %d, Out %4.2f\n", secs,
				curCounts, CountsToDegrees(curCounts), closedLoopError, motorOutput);

		// Check to see if the error is in an acceptable number of inches.
		if (fabs(errorInDegrees < m_toleranceDegrees)) {
			pidFinished = true;
			m_safetyTimer.Stop();
			std::printf("2135: WR Move Finished - Time %f\n", m_safetyTimer.Get());
		}

		// Check to see if the Safety Timer has timed out.
		if (m_safetyTimer.Get() >= m_safetyTimeout) {
			pidFinished = true;
			m_safetyTimer.Stop();
			std::printf("2135: WR Move Safety timer has timed out\n");
		}
	}

	return pidFinished;
}

void Wrist::BumpToPosition(bool direction) {
	m_bumpDir = direction;

	MoveToPosition(BUMP_ANGLE);
}

void Wrist::Calibrate() {

	if (m_talonValidWR12)
		motorWR12->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

	frc::SmartDashboard::PutBoolean("WR Calibrated", true);
}


