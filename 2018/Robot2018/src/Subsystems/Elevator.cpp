// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Elevator.h"

#include "../Commands/ElevatorRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevator::Elevator() : frc::Subsystem("Elevator") {

    std::printf("2135: EL Elevator Constructor\n");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL7 = RobotMap::elevatorMotorL7;
    motorR8 = RobotMap::elevatorMotorR8;
    hallLimit = RobotMap::elevatorHallLimit;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidL7 = frc2135::TalonSRXUtils::TalonSRXCheck(motorL7, "EL", "L7");
    m_talonValidR8 = frc2135::TalonSRXUtils::TalonSRXCheck(motorR8, "EL", "R8");

    // Get any config file settings
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("EL_CalibSpeed", m_calibrationSpeed, 0.25);
    config->GetValueAsDouble("EL_PidKp", m_pidKp, 0.250);
    config->GetValueAsDouble("EL_PidMaxOut", m_pidMaxOut, 1.0);
    config->GetValueAsDouble("EL_CLRampRate", m_CLRampRate, 0.250);
    config->GetValueAsInt("EL_CLAllowedError", m_CLAllowedError, 0);
	config->GetValueAsDouble("EL_ToleranceInches", m_toleranceInches, 2.0);
    config->GetValueAsDouble("EL_MaxHeight", m_elevatorMaxHeight, 35.0);
    config->GetValueAsDouble("EL_MinHeight", m_elevatorMinHeight, 0.0);
	config->GetValueAsDouble("EL_BumpHeight", m_bumpHeight, 1.0);
	config->GetValueAsDouble("EL_FloorHeight", m_floorHeight, 0.5);
	config->GetValueAsDouble("EL_SwitchHeight", m_switchHeight, 13.5);
	config->GetValueAsDouble("EL_ScaleLoHeight", m_scaleLoHeight, 32.0);
	config->GetValueAsDouble("EL_ScaleHiHeight", m_scaleHiHeight, 33.0);
	config->GetValueAsDouble("EL_ClimbHeight", m_climbHeight, 31.0);
	config->GetValueAsDouble("EL_LevitateHeight", m_levitateHeight, 16.0);
	config->GetValueAsDouble("EL_LowGearHeight", m_lowGearHeight, 15.00);

    // Initialize Talon SRX motor controller direction and encoder sensor slot
    // Set the control mode and target to disable any movement
    // Set to brake mode (in comparison to coast)
    // Set encoder as a CTRE magnetic in relative mode with sensor in phase with output
	if (m_talonValidL7) {
	    motorL7->SetInverted(false);			// Sets the Talon inversion to false
	    motorL7->SetNeutralMode(NeutralMode::Brake);
	    motorL7->Set(ControlMode::PercentOutput, 0.0);
	    motorL7->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
	    motorL7->SetSensorPhase(true);
	    motorL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
	}

	if (m_talonValidR8) {
	    motorR8->SetInverted(false);			// Sets the Talon inversion to false
	    motorR8->SetNeutralMode(NeutralMode::Brake);
	    motorR8->Set(ControlMode::Follower, 7);
	}

	// Set maximum power and ramp rate
    // Set proportional
    // Set allowable closed loop error
	// Set maximum current draw allowed
	if (m_talonValidL7) {
		motorL7->ConfigPeakOutputForward(m_pidMaxOut, m_timeout);
		motorL7->ConfigPeakOutputReverse(-m_pidMaxOut, m_timeout);
		motorL7->ConfigClosedloopRamp(m_CLRampRate, m_timeout);
	    motorL7->Config_kP(m_slotIndex, m_pidKp, m_timeout);
//	    motorL7->Config_kD(m_slotIndex, 10 * m_pidKp, m_timeout);
	    motorL7->ConfigAllowableClosedloopError(m_slotIndex, m_CLAllowedError, m_timeout);

	    motorL7->ConfigForwardSoftLimitThreshold(InchesToCounts(m_elevatorMaxHeight), m_timeout);
	    motorL7->ConfigReverseSoftLimitThreshold(InchesToCounts(m_elevatorMinHeight), m_timeout);
	    motorL7->ConfigForwardSoftLimitEnable(true, m_timeout);
	    motorL7->ConfigReverseSoftLimitEnable(true, m_timeout);

		motorL7->ConfigPeakCurrentLimit(10.0, m_timeout);
		motorL7->EnableCurrentLimit(false);
	}

	if (m_talonValidR8) {
		motorR8->ConfigPeakCurrentLimit(10.0, m_timeout);
		motorR8->EnableCurrentLimit(false);
	}

    // Initialize variables
    m_curInches = 0.0;
    m_targetInches = 0.0;
    m_targetCounts = 0;
    m_calibrated = false;
    m_calibrationState = 0;

    // Field for manually progamming elevator height
	SmartDashboard::PutNumber("EL Setpoint", 0.0);
	SmartDashboard::PutBoolean("EL Calibrated", m_calibrated);
}

void Elevator::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ElevatorRun(-1));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Elevator::Periodic() {
	double	curCounts = 0.0;
	double	outputL7 = 0.0, currentL7 = 0.0;
	double	outputR8 = 0.0, currentR8 = 0.0;

	if (m_talonValidL7) {
		curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);
		outputL7 = motorL7->GetMotorOutputVoltage();
		currentL7 = motorL7->GetOutputCurrent();
	}

	if (m_talonValidR8) {
		outputR8 = motorR8->GetMotorOutputVoltage();
		currentR8 = motorR8->GetOutputCurrent();
	}

    // Put code here to be run every loop
	SmartDashboard::PutBoolean("EL Calibrated", m_calibrated);
	SmartDashboard::PutNumber("EL Height", CountsToInches(curCounts));
	if (m_elevatorDebug) {
		SmartDashboard::PutBoolean("EL Hall Sensor", HallSensorIsTriggered());
		SmartDashboard::PutNumber("Cube Height", 2 * CountsToInches(curCounts));

		SmartDashboard::PutNumber("EL_Output_L7", outputL7);
		SmartDashboard::PutNumber("EL_Current_L7", currentL7);
		SmartDashboard::PutNumber("EL_Output_R8", outputR8);
		SmartDashboard::PutNumber("EL_Current_R8", currentR8);
	}
}

///////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::Initialize(void) {
	double	curCounts = 0.0;

	std::printf("2135: EL Init\n");
	// Set PID target to current encoder reading
	if (m_talonValidL7)
		curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);

	m_targetInches = CountsToInches(curCounts);
}

int Elevator::InchesToCounts(double inches) {
	int counts;

	counts = (int) round((inches / m_circumInches) * COUNTS_PER_ROTATION);
	return counts;
}

double Elevator::CountsToInches(int counts) {
	double inches;

	inches = ((double) counts / COUNTS_PER_ROTATION) * m_circumInches;
	return inches;
}

double Elevator::GetCurrentInches () {
	double curCounts = 0.0;

	if (m_talonValidL7)
		curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);

	m_curInches = CountsToInches(curCounts);
	return m_curInches;
}

bool Elevator::HallSensorIsTriggered() {
	// Hall sensor is false when magnet is nearby
	return !hallLimit->Get();
}

bool Elevator::HeightLimitToLowGear() {

	return (Robot::elevator->GetCurrentInches() > m_lowGearHeight);
}

//	Elevator PID loop state management

void Elevator::MoveToPosition(int level) {
	int curCounts = 0;

	m_elevatorLevel = level;

	// Validate and set the requested position to move
	switch (level) {
	case NOCHANGE_HEIGHT:	// Do not change from current level!
		// m_targetInches = m_targetInches;
		break;
	case FLOOR_HEIGHT:
		m_targetInches = m_floorHeight;
		break;
	case SWITCH_HEIGHT:
		m_targetInches = m_switchHeight;
		break;
	case SCALE_LO_HEIGHT:
		m_targetInches = m_scaleLoHeight;
		break;
	case SCALE_HI_HEIGHT:
		m_targetInches = m_scaleHiHeight;
		break;
	case CLIMB_HEIGHT:
		m_targetInches = m_climbHeight;
		break;
	case LEVITATE_HEIGHT:
		m_targetInches = m_levitateHeight;
		break;
	case SMARTDASH_HEIGHT:
		m_targetInches = SmartDashboard::GetNumber("EL Setpoint", 0.0);
		break;
	case BUMP_HEIGHT:
		double bumpHeight;
		bumpHeight = (m_bumpDir) ? m_bumpHeight : -m_bumpHeight;
		m_targetInches += bumpHeight;
		break;
	default:
		std::printf("2135: EL invalid height requested - %d\n", level);
		return;
	}

	std::printf("2135: EL m_targetInches: %f, InchesToCounts: %d\n",
			m_targetInches, InchesToCounts(m_targetInches));

	// Save the requested target height inches
	if (m_calibrated == true) {

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
		if (m_talonValidL7)
			curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);
		m_curInches = CountsToInches(curCounts);

		//Start the safety timer.
		m_safetyTimeout = 4.0;
		m_safetyTimer.Reset();
		m_safetyTimer.Start();

		motorL7->Set(ControlMode::Position, (double)m_targetCounts);

		std::printf("2135: EL Move inches %f -> %f counts %d -> %d\n",
				m_curInches, m_targetInches, curCounts, m_targetCounts);
	}
	else {
		std::printf("2135: EL is not calibrated\n");

		if (m_talonValidL7)
			motorL7->Set(ControlMode::PercentOutput, 0.0);
	}
}

// Elevator PID loop completion monitoring

bool Elevator::MoveToPositionIsFinished() {
	bool pidFinished = false;
	int curCounts = 0;
	int closedLoopError = 0;
	double motorOutput = 0.0;
	double errorInInches = 0;

	// If a real move was requested, check for completion
	if (m_elevatorLevel != NOCHANGE_HEIGHT) {
		if (m_talonValidL7) {
			curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);
			motorOutput = motorL7->GetMotorOutputPercent();
		}

		double secs = (double)RobotController::GetFPGATime() / 1000000.0;

		closedLoopError = m_targetCounts - curCounts;
		errorInInches = CountsToInches(m_targetCounts - curCounts);

		// cts = Encoder Counts, CLE = Closed Loop Error, Out = Motor Output
		std::printf("2135: EL %5.3f cts %d, in %5.2f, CLE %d, Out %4.2f\n", secs,
				curCounts, CountsToInches(curCounts), closedLoopError, motorOutput);

		// Check to see if the error is in an acceptable number of inches.
		if (fabs(errorInInches) < m_toleranceInches) {
			pidFinished = true;
			m_safetyTimer.Stop();
			std::printf("2135: EL Move Finished - Time %f\n", m_safetyTimer.Get());
		}

		// Check to see if the Safety Timer has timed out.
		if (m_safetyTimer.Get() >= m_safetyTimeout) {
			pidFinished = true;
			m_safetyTimer.Stop();
			std::printf("2135: EL Move Safety timer has timed out\n");
		}
	}

	return pidFinished;
}

// Elevator PID loop setup to do a bump movement

void Elevator::BumpToPosition(bool direction) {
	m_bumpDir = direction;

	MoveToPosition(BUMP_HEIGHT);
}

// Elevator PID calibration setup and initialization

void Elevator::CalibrationInit() {
	m_calibrated = false;
	m_calibrationState = CALIB_START;

	if (m_talonValidL7)
		motorL7->Set(ControlMode::PercentOutput, 0.0);

	//Set safety timer.
	m_safetyTimeout = 3.0;
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
}

// Elevator PID calibration execution loop

void Elevator::CalibrationExecute() {
	int		curCounts = 0;

	// Calibration state machine
	static int lastCalibState = -1;

	switch (m_calibrationState) {
	case CALIB_START:
		// Hall sensor is false when near magnet
		if (HallSensorIsTriggered()) {
			// Near magnet, reset encoder and move up a little using encoder
			std::printf("2135: EL Calibration - move UP first\n");
			if (m_talonValidL7) {
				motorL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
				motorL7->Set(ControlMode::PercentOutput, m_calibrationSpeed);
			}
			m_calibrationState = CALIB_MOVE_UP;
		}
		else {
			std::printf("2135: EL Calibration - move DOWN first\n");
			// Not near magnet, start moving down
			m_calibrationState = CALIB_START_DOWN;
		}
		break;
	case CALIB_MOVE_UP:
		// Check to see if moved up 3 rotations
		if (m_talonValidL7)
			curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);
		std::printf("2135: EL Encoder Counts %d\n", curCounts);
		if (abs(curCounts) > (COUNTS_PER_ROTATION)) {
			std::printf("2135: EL Calibration - done moving up\n");
			if (m_talonValidL7)
				motorL7->Set(ControlMode::PercentOutput, 0.0);
			m_calibrationState = CALIB_START_DOWN;
		}
		break;
	case CALIB_START_DOWN:
		std::printf("2135: EL Calibration - start moving down\n");
		if (m_talonValidL7)
			motorL7->Set(ControlMode::PercentOutput, -m_calibrationSpeed);
		m_calibrationState = CALIB_MOVE_DOWN;
		break;
	case CALIB_MOVE_DOWN:
		// Hall sensor is false when near magnet
		if (HallSensorIsTriggered()) {
			// Near magnet, end of calibration
			std::printf("2135: EL Calibration - done moving down - Hall sensor found\n");
			if (m_talonValidL7) {
				motorL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
				motorL7->Set(ControlMode::PercentOutput, 0.0);
			}
			m_calibrationState = CALIB_DONE;
		}
		break;
	case CALIB_DONE:
		if (m_talonValidL7) {
			motorL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
			motorL7->Set(ControlMode::Position, 0.0);
		}
		m_calibrated = true;
		break;
	}

	// If calibration state changes, print new value
	if (m_calibrationState != lastCalibState) {
		std::printf("2135: EL Calibration State: %d\n", m_calibrationState);
		lastCalibState = m_calibrationState;
	}
}

// Elevator PID calibration monitoring

bool Elevator::CalibrationIsFinished() {
	//Check to see if it has passed the safety timeout.
	if (m_safetyTimer.Get() >= m_safetyTimeout) {
		std::printf("2135: EL Calibration - Safety Timer Timeout!\n");
		return true;	// exits without valid calibration
	}

	// Hall sensor is false when near magnet
	return m_calibrated;
}

// Elevator PID calibration movement failed

void Elevator::CalibrationStop() {
	m_safetyTimer.Stop();

	if (m_talonValidL7)
		motorL7->Set(ControlMode::PercentOutput, 0.0);
}

// Elevator PID calibration force step

void Elevator::CalibrationOverride() {
	m_calibrationState = CALIB_DONE;
	CalibrationExecute();
}
