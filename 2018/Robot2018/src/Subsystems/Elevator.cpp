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

#include "Elevator.h"
#include "../RobotMap.h"
#include "../Commands/ElevatorRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevator::Elevator() : frc::Subsystem("Elevator") {
    std::printf("2135: Elevator Constructor\n");
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL7 = RobotMap::elevatorMotorL7;
    motorR8 = RobotMap::elevatorMotorR8;
    hallLimit = RobotMap::elevatorHallLimit;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Display Talon SRX firmware versions
    std::printf("2135: Motor L7 ID %d ver %d.%d\n", motorL7->GetDeviceID(),
    		motorL7->GetFirmwareVersion()/256, motorL7->GetFirmwareVersion()%256);
    std::printf("2135: Motor R8 ID %d ver %d.%d\n", motorR8->GetDeviceID(),
    		motorR8->GetFirmwareVersion()/256, motorR8->GetFirmwareVersion()%256);

    // Get any config file settings
    RobotConfig* config = RobotConfig::GetInstance();
    config->GetValueAsDouble("EL_CalibSpeed", m_calibrationSpeed, 0.2);
    config->GetValueAsDouble("EL_PidSpeed", m_pidSpeed, 0.4);
    config->GetValueAsDouble("EL_PidKp", m_pidKp, 0.25);
    config->GetValueAsInt("EL_PidAllowableCLE", m_pidAllowableCLE, 0);
    config->GetValueAsDouble("EL_MaxHeight", m_elevatorMaxHeight, 22.0);
    config->GetValueAsDouble("EL_MinHeight", m_elevatorMinHeight, 0.0);
	config->GetValueAsDouble("EL_BumpHeight", m_bumpHeight, 1.0);
	config->GetValueAsDouble("EL_FloorHeight", m_floorHeight, 0.0);
	config->GetValueAsDouble("EL_SwitchHeight", m_switchHeight, 5.0);
	config->GetValueAsDouble("EL_ScaleLoHeight", m_scaleLoHeight, 10.0);
	config->GetValueAsDouble("EL_ScaleHiHeight", m_scaleHiHeight, 15.0);
	config->GetValueAsDouble("EL_ClimbHeight", m_climbHeight, 20.0);
	config->GetValueAsDouble("EL_LevitateHeight", m_levitateHeight, 18.0);
	config->GetValueAsDouble("EL_SafetyTimeout", m_safetyTimeout, 4.0);
	config->GetValueAsDouble("EL_LowGearHeight", m_lowGearHeight, 15.00);

    // Initialize Talon SRX motor controller direction and encoder sensor slot
    motorL7->SetInverted(false);			// Sets the Talon inversion to false
    motorR8->SetInverted(false);			// Sets the Talon inversion to false

    // Set the control mode and target to disable any movement
    motorL7->Set(ControlMode::PercentOutput, 0.0);
    motorR8->Set(ControlMode::Follower, 7);

    // Set to brake mode (in comparison to coast)
    motorL7->SetNeutralMode(NeutralMode::Brake);
    motorR8->SetNeutralMode(NeutralMode::Brake);

    // Set encoder as a CTRE magnetic in relative mode with sensor in phase with output
    motorL7->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
    motorL7->SetSensorPhase(true);
    motorL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

	// Set maximum power and ramp rate
	motorL7->ConfigPeakOutputForward(m_pidSpeed, m_timeout);
	motorL7->ConfigPeakOutputReverse(-m_pidSpeed, m_timeout);
	motorL7->ConfigClosedloopRamp(0.25, m_timeout);

	// Set maximum current draw allowed
	motorL7->ConfigPeakCurrentLimit(10.0, m_timeout);
	motorR8->ConfigPeakCurrentLimit(10.0, m_timeout);
	motorL7->EnableCurrentLimit(false);
	motorR8->EnableCurrentLimit(false);

    // Set proportional
    motorL7->Config_kP(m_slotIndex, m_pidKp, m_timeout);
//    motorL7->Config_kD(m_slotIndex, 10 * m_pidKp, m_timeout);

    motorL7->ConfigForwardSoftLimitThreshold(InchesToCounts(m_elevatorMaxHeight), m_timeout);
    motorL7->ConfigReverseSoftLimitThreshold(InchesToCounts(m_elevatorMinHeight), m_timeout);
    motorL7->ConfigForwardSoftLimitEnable(true, m_timeout);
    motorL7->ConfigReverseSoftLimitEnable(true, m_timeout);

    // Set allowable closed loop error
    motorL7->ConfigAllowableClosedloopError(m_slotIndex, m_pidAllowableCLE, m_timeout);
#endif

    // Initialize variables
    m_curInches = 0.0;
    m_targetInches = 0.0;
    m_targetCounts = 0.0;
    m_calibrated = false;
    m_calibrationState = 0;

    // Field for manually progamming elevator height
	SmartDashboard::PutNumber("EL Setpoint", 0.0);
}

void Elevator::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ElevatorRun(-1));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
#endif
}

void Elevator::Periodic() {
    // Put code here to be run every loop
	SmartDashboard::PutBoolean("EL Calibrated", m_calibrated);
	SmartDashboard::PutBoolean("EL Hall Sensor", HallSensorIsTriggered());
	SmartDashboard::PutNumber("EL Height", CountsToInches(motorL7->GetSelectedSensorPosition(m_pidIndex)));
	SmartDashboard::PutNumber("Cube Height", 2 * CountsToInches(motorL7->GetSelectedSensorPosition(m_pidIndex)));
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::Initialize(frc::Preferences *RobotConfig)
{
	std::printf("2135: Elevator Init\n");
}

double Elevator::InchesToCounts(double inches) {
	double counts;

	counts = (inches / m_circumInches) * COUNTS_PER_ROTATION;
	return counts;
}

double Elevator::CountsToInches(int counts) {
	double inches;

	inches = ((double) counts / COUNTS_PER_ROTATION) * m_circumInches;
	return inches;
}

double Elevator::GetCurrentInches () {
	double curCounts;

	curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);
	m_curInches = CountsToInches(curCounts);
	return m_curInches;
}

bool Elevator::HallSensorIsTriggered() {
	// Hall sensor is false when magnet is nearby
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
	return !hallLimit->Get();
#endif
}

bool Elevator::HeightLimitToLowGear() {

	return (Robot::elevator->GetCurrentInches() > m_lowGearHeight);
}

//	Elevator PID loop state management

void Elevator::MoveToPosition(int height) {

	double curInches = 0.0;
	int curCounts = 0;

	m_elevatorLevel = height;

	// Validate and set the requested position to move
	switch (height) {
	case NOCHANGE_HEIGHT:	// Do not change from current height!
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
		m_targetInches = GetCurrentInches() + bumpHeight;
		break;
	default:
		std::printf("2135: Elevator invalid height requested - %d\n", height);
		return;
	}

	// Save the requested target height inches
	if (m_calibrated == true) {

		// Constrain input request to a valid and safe range between full down and max height
		if (m_targetInches < m_elevatorMinHeight) {
			m_targetInches = m_elevatorMinHeight;
		}
		if (m_targetInches > m_elevatorMaxHeight) { //TODO Determine upwards limit
			m_targetInches = m_elevatorMaxHeight;
		}

		m_targetCounts = InchesToCounts(m_targetInches);

#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
		// Get current position in inches and set position mode and target counts
		curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);
		curInches = CountsToInches(curCounts);
		m_curInches = curInches;

		//Start the safety timer.
		m_safetyTimer.Reset();
		m_safetyTimer.Start();

		motorL7->Set(ControlMode::Position, m_targetCounts);
#endif

		std::printf("2135: Elevator Move inches %f -> %f counts %d -> %f\n",
				curInches, m_targetInches, curCounts, m_targetCounts);
	}
	else {
		std::printf("2135: Elevator is not calibrated\n");
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
		motorL7->Set(ControlMode::PercentOutput, 0.0);
#endif
	}
}

// Elevator PID loop completion monitoring

bool Elevator::MoveToPositionIsFinished() {
	bool pidFinished = false;
	int curCounts = 0;
	int closedLoopError = 0;
	double motorOutput = 0.0;
	double errorInInches = 0;

	// If a real move was requeted, check for completion
	if (m_elevatorLevel != NOCHANGE_HEIGHT)
	{
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
		curCounts = motorL7->GetSelectedSensorPosition(m_pidIndex);
		closedLoopError = motorL7->GetClosedLoopError(m_pidIndex);
		motorOutput = motorL7->GetMotorOutputPercent();
#endif

		// EncCount = Encoder Counts, CLE = Closed Loop Error, M_Output = Motor Output
		std::printf("2135: Elevator EncCount %d, CLE %d, M_Output %f\n", curCounts, closedLoopError, motorOutput);

		// Check to see if the Safety Timer has timed out.
		if (m_safetyTimer.Get() >= m_safetyTimeout) {
			pidFinished = true;
			m_safetyTimer.Stop();
			std::printf("2135: Elevator Move Safety timer has timed out\n");
		}

		// Check to see if the error is in an acceptable number of inches.
		errorInInches = CountsToInches(m_targetCounts - (double)curCounts);
		if (fabs(errorInInches) < 2.0) {
			pidFinished = true;
			m_safetyTimer.Stop();
			std::printf("2135: Elevator Move Finished - Time %f\n", m_safetyTimer.Get());
		}
		else {
			pidFinished = false;
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
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
	motorL7->Set(ControlMode::PercentOutput, 0.0);
#endif
}

// Elevator PID calibration execution loop

void Elevator::CalibrationExecute() {

	// Calibration state machine

#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
	static int lastCalibState = -1;

	switch (m_calibrationState) {
	case CALIB_START:
		// Hall sensor is false when near magnet
		if (HallSensorIsTriggered()) {
			// Near magnet, reset encoder and move up a little using encoder
			std::printf("2135: Calibration - move UP first\n");
			motorL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
			motorL7->Set(ControlMode::PercentOutput, m_calibrationSpeed);
			m_calibrationState = CALIB_MOVE_UP;
		}
		else {
			std::printf("2135: Calibration - move DOWN first\n");
			// Not near magnet, start moving down
			m_calibrationState = CALIB_START_DOWN;
		}
		break;
	case CALIB_MOVE_UP:
		// Check to see if moved up 3 rotations
		printf("2135: Encoder Counts %d\n", motorL7->GetSelectedSensorPosition(m_pidIndex));
		if (abs(motorL7->GetSelectedSensorPosition(m_pidIndex)) > (COUNTS_PER_ROTATION)) {
			std::printf("2135: Calibration - done moving up\n");
			motorL7->Set(ControlMode::PercentOutput, 0.0);
			m_calibrationState = CALIB_START_DOWN;
		}
		break;
	case CALIB_START_DOWN:
		std::printf("2135: Calibration - start moving down\n");
		motorL7->Set(ControlMode::PercentOutput, -m_calibrationSpeed);
		m_calibrationState = CALIB_MOVE_DOWN;
		break;
	case CALIB_MOVE_DOWN:
		// Hall sensor is false when near magnet
		if (HallSensorIsTriggered()) {
			// Near magnet, end of calibration
			std::printf("2135: Calibration - done moving down - Hall sensor found\n");
			motorL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
			motorL7->Set(ControlMode::PercentOutput, 0.0);
			m_calibrationState = CALIB_DONE;
		}
		break;
	case CALIB_DONE:
		motorL7->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
		motorL7->Set(ControlMode::Position, 0.0);
		m_calibrated = true;
		break;
	}

	// If calibration state changes, print new value
	if (m_calibrationState != lastCalibState) {
		std::printf("2135: Elevator State: %d\n", m_calibrationState);
		lastCalibState = m_calibrationState;
	}
#endif
}

// Elevator PID calibration monitoring

bool Elevator::CalibrationIsFinished() {
	// Hall sensor is false when near magnet
	return m_calibrated;
}

// Elevator PID calibration movement failed

void Elevator::CalibrationStop() {
#if !defined (ROBORIO_STANDALONE) || defined (ROBOTBENCHTOPTEST)
	motorL7->Set(ControlMode::PercentOutput, 0.0);
#endif
}

// Elevator PID calibration force step

void Elevator::CalibrationOverride() {
	m_calibrationState = CALIB_DONE;
	CalibrationExecute();
}
