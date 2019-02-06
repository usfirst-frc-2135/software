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

#include "Commands/ElevatorRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevator::Elevator() : frc::Subsystem("Elevator") {

    std::printf("2135: EL Elevator Constructor\n");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorEL8.reset(new WPI_TalonSRX(8));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    m_talonValidEL8 = frc2135::TalonSRXUtils::TalonSRXCheck(motorEL8, "EL", "R8");

    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("EL_CalibSpeed", m_calibrationSpeed, 0.25);
	config->GetValueAsDouble("EL_PidMaxOut", m_pidMaxOut, 1.0);
    config->GetValueAsDouble("EL_PidKp", m_pidKp, 0.250);
    config->GetValueAsDouble("EL_CLRampRate", m_CLRampRate, 0.250);
    config->GetValueAsInt("EL_CLAllowedError", m_CLAllowedError, 0);
	config->GetValueAsDouble("EL_ToleranceInches", m_toleranceInches, 2.0);
    config->GetValueAsDouble("EL_MaxHeight", m_elevatorMaxHeight, 35.0);
    config->GetValueAsDouble("EL_MinHeight", m_elevatorMinHeight, 0.0);
	config->GetValueAsDouble("EL_LowGearHeight", m_lowGearHeight, 15.00);
	config->GetValueAsDouble("EL_BumpHeight", m_bumpHeight, 1.0);
	config->GetValueAsDouble("EL_FloorHeight", m_floorHeight, 0.5);
	config->GetValueAsDouble("EL_ShipHatchHeight", m_shipHatchHeight, 13.5);
	config->GetValueAsDouble("EL_ShipCargoHeight", m_shipCargoHeight, 18.0);
	config->GetValueAsDouble("EL_RocketL2HatchHeight", m_rocketL2HatchHeight, 32.0);
	config->GetValueAsDouble("EL_RocketL3HatchHeight", m_rocketL3HatchHeight, 33.0);
	config->GetValueAsDouble("EL_RocketCargoBumpHeight", m_rocketCargoBumpHeight, 6.0);

    if (m_talonValidEL8) {
	    motorEL8->SetInverted(false);			// Sets the Talon inversion to false
	    motorEL8->SetNeutralMode(NeutralMode::Brake);
	    motorEL8->Set(ControlMode::PercentOutput, 0.0);
	    motorEL8->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
	    motorEL8->SetSensorPhase(true);
	    motorEL8->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
	}

    // Set maximum power and ramp rate
    // Set proportional
    // Set allowable closed loop error
	// Set maximum current draw allowed
	if (m_talonValidEL8) {
		motorEL8->ConfigPeakOutputForward(m_pidMaxOut, m_timeout);
		motorEL8->ConfigPeakOutputReverse(-m_pidMaxOut, m_timeout);
		motorEL8->ConfigClosedloopRamp(m_CLRampRate, m_timeout);
	    motorEL8->Config_kP(m_slotIndex, m_pidKp, m_timeout);
	    motorEL8->Config_kD(m_slotIndex, 10 * m_pidKp, m_timeout);
	    motorEL8->ConfigAllowableClosedloopError(m_slotIndex, m_CLAllowedError, m_timeout);

	    motorEL8->ConfigForwardSoftLimitThreshold(InchesToCounts(m_elevatorMaxHeight), m_timeout);
	    motorEL8->ConfigReverseSoftLimitThreshold(InchesToCounts(m_elevatorMinHeight), m_timeout);
	    motorEL8->ConfigForwardSoftLimitEnable(true, m_timeout);
	    motorEL8->ConfigReverseSoftLimitEnable(true, m_timeout);

		motorEL8->ConfigVoltageCompSaturation(12.0, 0);
		motorEL8->EnableVoltageCompensation(true);

		motorEL8->ConfigPeakCurrentLimit(10.0, m_timeout);
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

        SetDefaultCommand(new ElevatorRun(-1));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Elevator::Periodic() {
    double	curCounts = 0.0;
	double	outputL7 = 0.0, currentL7 = 0.0;
	double	outputR8 = 0.0, currentR8 = 0.0;

    if (m_talonValidEL8) {
		curCounts = motorEL8->GetSelectedSensorPosition(m_pidIndex);
		outputL7 = motorEL8->GetMotorOutputVoltage();
		currentL7 = motorEL8->GetOutputCurrent();
	}

    // Put code here to be run every loop
    frc::SmartDashboard::PutBoolean("EL Calibrated", m_calibrated);
	frc::SmartDashboard::PutNumber("EL Height", CountsToInches(curCounts));

	if (m_elevatorDebug) {
		//frc::SmartDashboard::PutNumber("Cube Height", 2 * CountsToInches(curCounts));

		frc::SmartDashboard::PutNumber("EL_Output_L7", outputL7);
		frc::SmartDashboard::PutNumber("EL_Current_L7", currentL7);
		frc::SmartDashboard::PutNumber("EL_Output_R8", outputR8);
		frc::SmartDashboard::PutNumber("EL_Current_R8", currentR8);
	}
}

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

///////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator:: Initialize(void) {
    double curCounts = 0.0;

    std::printf("EL Initialize\n");

    // PID Target is set to current encoder counts
    if (m_talonValidEL8)
        curCounts = motorEL8->GetSelectedSensorPosition(m_pidIndex);

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

	if (m_talonValidEL8)
		curCounts = motorEL8->GetSelectedSensorPosition(m_pidIndex);

	m_curInches = CountsToInches(curCounts);
	return m_curInches;
}

bool Elevator::HeightLimitToLowGear() {
    // Check to see if we are above our set low gear height limit.
	return (GetCurrentInches() > m_lowGearHeight);
}

//	Elevator PID loop state management //

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
	case SHIP_HATCH_HEIGHT:
		m_targetInches = m_shipHatchHeight;
		break;
	case SHIP_CARGO_HEIGHT:
		m_targetInches = m_shipCargoHeight;
		break;
	case ROCKET_L2_HATCH_HEIGHT:
		m_targetInches = m_rocketL2HatchHeight;
		break;
	case ROCKET_L3_HATCH_HEIGHT:
		m_targetInches = m_rocketL3HatchHeight;
		break;
	case ROCKET_CARGO_BUMP_HEIGHT:
		m_targetInches = m_rocketCargoBumpHeight;
		break;
	case SMARTDASH_HEIGHT:
		m_targetInches = frc::SmartDashboard::GetNumber("EL Setpoint", 0.0);
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
		if (m_talonValidEL8)
			curCounts = motorEL8->GetSelectedSensorPosition(m_pidIndex);
		m_curInches = CountsToInches(curCounts);

		//Start the safety timer.
		m_safetyTimeout = 4.0;
		m_safetyTimer.Reset();
		m_safetyTimer.Start();

		motorEL8->Set(ControlMode::Position, (double)m_targetCounts);

		std::printf("2135: EL Move inches %f -> %f counts %d -> %d\n",
				m_curInches, m_targetInches, curCounts, m_targetCounts);
	}
	else {
		std::printf("2135: EL is not calibrated\n");

		if (m_talonValidEL8)
			motorEL8->Set(ControlMode::PercentOutput, 0.0);
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
		if (m_talonValidEL8) {
			curCounts = motorEL8->GetSelectedSensorPosition(m_pidIndex);
			motorOutput = motorEL8->GetMotorOutputPercent();
		}

		double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

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

void Elevator::CalibrationOverride() {
    if (m_talonValidEL8) {
			motorEL8->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
			motorEL8->Set(ControlMode::Position, 0.0);
		}
	m_calibrated = true;
}
