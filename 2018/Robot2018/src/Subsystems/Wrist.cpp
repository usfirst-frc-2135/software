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

#include "Wrist.h"
#include "../RobotMap.h"
#include "../Commands/WristRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Wrist::Wrist() : frc::Subsystem("Wrist") {
	std::printf("2135: Wrist Constructor\n");

#ifndef ROBORIO_STANDALONE
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorW14 = RobotMap::wristMotorW14;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

#ifdef TALON_W14_PRESENT	// If wrist motor is on CAN bus
    std::printf("2135: Motor W14 ID %d ver %d.%d\n", motorW14->GetDeviceID(), motorW14->GetFirmwareVersion()/256, motorW14->GetFirmwareVersion()%256);

    // Get any config file settings
    RobotConfig* config = RobotConfig::GetInstance();
    config->GetValueAsDouble("WR_PidSpeed", m_pidSpeed, 0.4);
    config->GetValueAsDouble("WR_PidKp", m_pidKp, 0.25);
    config->GetValueAsInt("WR_PidAllowableCLE", m_pidAllowableCLE, 0);
    config->GetValueAsInt("WR_MaxCounts", m_wristMaxCounts, 0);
    config->GetValueAsInt("WR_MinCounts", m_wristMinCounts, 0);
    config->GetValueAsDouble("WR_OffsetDegrees", m_offsetDegrees);
	config->GetValueAsDouble("WR_BumpAngle", m_bumpAngle, 1.0);
	config->GetValueAsDouble("WR_WristFlat", m_flatAngle, 0);
	config->GetValueAsDouble("WR_WristDelivery", m_deliveryAngle, 0);
	config->GetValueAsDouble("WR_WristStowed", m_stowedAngle, 0);
	config->GetValueAsDouble("WR_SafetyTimeout", m_safetyTimeout, 4.0);

	motorW14->SetInverted(false);

    // Set the control mode and target to disable any movement
    motorW14->Set(ControlMode::PercentOutput, 0.0);

    // Set to brake mode (in comparison to coast)
    motorW14->SetNeutralMode(NeutralMode::Brake);

	motorW14->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Absolute, m_pidIndex, m_timeout);
	motorW14->SetSensorPhase(false);
	m_curDegrees = CountsToDegrees(motorW14->GetSelectedSensorPosition(m_pidIndex));

	// Set maximum power and ramp rate
	motorW14->ConfigPeakOutputForward(m_pidSpeed, m_timeout);
	motorW14->ConfigPeakOutputReverse(-m_pidSpeed, m_timeout);
//	motorW14->ConfigClosedLoopRamp(0.25, m_timeout);

	// Set maximum current draw allowed
	motorW14->ConfigPeakCurrentLimit(10.0, m_timeout);
	motorW14->EnableCurrentLimit(false);

 	// Set proportional constant
	motorW14->Config_kP(0, m_pidKp, m_timeout); // TODO: Set the proportional
	//    motorW14->Config_kD(m_slotIndex, 10 * m_pidKp, m_timeout);

	motorW14->ConfigForwardSoftLimitThreshold(m_wristMaxCounts, m_timeout);
	motorW14->ConfigReverseSoftLimitThreshold(m_wristMinCounts, m_timeout);
	motorW14->ConfigForwardSoftLimitEnable(true, m_timeout);
	motorW14->ConfigReverseSoftLimitEnable(true, m_timeout);

	// Set closed loop error
	motorW14->ConfigAllowableClosedloopError(0, m_pidAllowableCLE, m_timeout);

	// Enable wrist PID with existing sensor reading (no movement)
	motorW14->Set(ControlMode::Position, DegreesToCounts(m_curDegrees));
	// Disable motor output until calibrated
//	motorW14->Set(ControlMode::PercentOutput, 0.0);
#endif

#endif

	//Initialize Variables
    m_targetDegrees = m_curDegrees;
    m_targetCounts = DegreesToCounts(m_curDegrees);

    // Field for manually progamming elevator height
	SmartDashboard::PutNumber("WR Setpoint", CountsToDegrees(m_curDegrees));
}

void Wrist::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
#ifndef ROBORIO_STANDALONE
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new WristRun(-1));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
#endif
}

void Wrist::Periodic() {
    // Put code here to be run every loop
#ifndef ROBORIO_STANDALONE
	int	curCounts = 0;

#ifdef TALON_W14_PRESENT	// If wrist motor is on CAN bus
	curCounts = motorW14->GetSelectedSensorPosition(m_pidIndex);
#endif
	SmartDashboard::PutNumber("WR Counts", curCounts);
	SmartDashboard::PutNumber("WR Degrees", CountsToDegrees(curCounts));
#endif
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
double Wrist::DegreesToCounts(double degrees) {
	double counts;

	counts = -1 * (degrees * ((COUNTS_PER_ROTATION * 2)/ 360) );
	return counts;
}

double Wrist::CountsToDegrees(int counts) {
	double degrees;

	degrees = -1 *( (double) counts * (360 / (COUNTS_PER_ROTATION *2)) );
	return degrees;
}

double Wrist::GetCurrentDegrees() {
	int curCounts = 0;

#ifdef TALON_W14_PRESENT	// If wrist motor is on CAN bus
	curCounts = motorW14->GetSelectedSensorPosition(m_pidIndex);
#endif
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
		m_targetDegrees = m_targetDegrees;
		break;
	case WRIST_FLAT:
		m_targetDegrees = m_flatAngle;
		break;
	case WRIST_DELIVER:
		m_targetDegrees = m_deliveryAngle;
		break;
	case WRIST_STOWED:
		m_targetDegrees = m_stowedAngle;
		break;
	case WRIST_SMARTDASH:
		m_targetDegrees = SmartDashboard::GetNumber("WR Setpoint", 0.0);
		break;
	case BUMP_ANGLE:
		double bumpAngle;
		bumpAngle = (m_bumpDir) ? m_bumpAngle : -m_bumpAngle;
		m_targetDegrees = GetCurrentDegrees() + bumpAngle;
		break;
	default:
		std::printf("2135: Wrist invalid angle requested - %d\n", level);
		return;
	}

	// Constrain input request to a valid and safe range between full down and max height
	//std::printf("2135: m_targetDegrees: %f, CountstoDegrees: %f\n", m_targetDegrees, CountstoDegrees(m_targetCounts));

	if (m_targetDegrees > CountsToDegrees(m_wristMinCounts)) {
		m_targetDegrees = CountsToDegrees(m_wristMinCounts);
	}
	if (m_targetDegrees < CountsToDegrees(m_wristMaxCounts)) {
		m_targetDegrees = CountsToDegrees(m_wristMaxCounts);
	}

	m_targetCounts = DegreesToCounts(m_targetDegrees);

#ifndef ROBORIO_STANDALONE
	// Set the mode and target
#ifdef TALON_W14_PRESENT	// If wrist motor is on CAN bus
	motorW14->Set(ControlMode::Position, m_targetCounts);
#else
	(void) m_targetDegrees;
#endif

#endif
	std::printf("2135: Wrist Move degrees %f -> %f counts %d -> %f\n",
			CountsToDegrees(curCounts), m_targetDegrees, curCounts, m_targetCounts);
}

bool Wrist::MoveToPositionIsFinished(void)
{
	bool pidFinished = false;
	int curCounts = 0;
	int closedLoopError = 0;
	double motorOutput = 0.0;
	double errorInDegrees = 0;

	if (m_wristLevel != WRIST_NOCHANGE)
	{
#ifndef ROBORIO_STANDALONE
#ifdef TALON_W14_PRESENT	// If wrist motor is on CAN bus
		curCounts = motorW14->GetSelectedSensorPosition(m_pidIndex);
		closedLoopError = motorW14->GetClosedLoopError(m_pidIndex);
		motorOutput = motorW14->GetMotorOutputPercent();
#endif
#endif

		// EncCount = Encoder Counts, CLE = Closed Loop Error, M_Output = Motor Output
		std::printf("2135: Wrist EncCount %d, CLE %d, M_Output %f\n", curCounts, closedLoopError, motorOutput);

		// Check to see if the Safety Timer has timed out.
		if (m_safetyTimer.Get() >= m_safetyTimeout) {
			MoveToPositionStop();
		}

		// Check to see if the error is in an acceptable number of inches.
		errorInDegrees = CountsToDegrees(m_targetCounts - (double)curCounts);
		if (fabs(errorInDegrees < 2.0)) {
			pidFinished = true;
			m_safetyTimer.Stop();
			std::printf("2135: Wrist Move Finished\n");
		}
	}

	return pidFinished;
}

void Wrist::MoveToPositionStop() {
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
//	motorW14->Set(ControlMode::PercentOutput, 0.0);
	std::printf("2135: Wrist Move Safety timer has timed out\n");
#endif
}

void Wrist::BumpToPosition(bool direction) {
	m_bumpDir = direction;

	MoveToPosition(BUMP_ANGLE);
}

void Wrist::ZeroEncoder() {
	motorW14->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
}
