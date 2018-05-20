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

#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../frc2135/TalonSRXUtils.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/DriveTeleop.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {
	double peakOutput = 1.0;

	std::printf("2135: DT Drivetrain Constructor\n");
#ifndef ROBORIO_STANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL1 = RobotMap::drivetrainMotorL1;
    motorR3 = RobotMap::drivetrainMotorR3;
    diffDrive = RobotMap::drivetrainDiffDrive;
    motorL2 = RobotMap::drivetrainMotorL2;
    motorR4 = RobotMap::drivetrainMotorR4;
    shifter = RobotMap::drivetrainShifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidL1 = frc2135::TalonSRXUtils::TalonSRXCheck(motorL1, "DT", "L1");
    m_talonValidL2 = frc2135::TalonSRXUtils::TalonSRXCheck(motorL2, "DT", "L2");
    m_talonValidR3 = frc2135::TalonSRXUtils::TalonSRXCheck(motorR3, "DT", "R3");
    m_talonValidR4 = frc2135::TalonSRXUtils::TalonSRXCheck(motorR4, "DT", "R4");

   //Retrieve drivetrain modifiers from RobotConfig
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
	config->GetValueAsDouble("DT_PeakOutput", peakOutput, 1.0);
	config->GetValueAsDouble("DT_DriveXScaling", m_driveXScaling, 1.0);
	config->GetValueAsDouble("DT_DriveYScaling", m_driveYScaling, 1.0);
    config->GetValueAsDouble("DT_TurnScaling", m_turnScaling, 1.0);
	if ((m_turnScaling < 0.0) || (m_turnScaling > 1.0)) {
		std::printf("2135: DT ERROR - m_turnScaling preference invalid - %f [0.0 .. 1.0]\n", m_turnScaling);
	}
    config->GetValueAsDouble("DT_DriveSpin", m_driveSpin, 0.45);
    config->GetValueAsDouble("DT_PidDistKp", m_distKp, 0.20);
    config->GetValueAsDouble("DT_PidDistMaxOut", m_distMaxOut, 0.65);
	config->GetValueAsDouble("DT_PidDistMaxInches", m_distMaxInches, 310.0);
	config->GetValueAsDouble("DT_CLRampRate", m_CL_rampRate, 0.300);
	config->GetValueAsInt("DT_CLAllowedError", m_CLAllowedError, 0);
	config->GetValueAsDouble("DT_PidDistErrInches", m_distErrInches, 1.5);
    config->GetValueAsDouble("DT_PidTurnKp", m_turnKp, 0.030);
    config->GetValueAsDouble("DT_PidTurnMaxOut", m_turnMaxOut, 0.42);
	config->GetValueAsDouble("DT_PidTurnErrDeg", m_turnErrDeg, 1.5);

	// Load autonomous command values at boot from config file
	double	temp;
	config->GetValueAsDouble("AutoDriveDist", temp, 97.5);
	SmartDashboard::PutNumber(AUTO_DT_DD, temp);
	config->GetValueAsDouble("AutoDriveTurn", temp, 90.0);
	SmartDashboard::PutNumber(AUTO_DT_DT, temp);

    // Invert the direction of the motors
    // Set to coast mode (in comparison to brake)
    // Set encoder as a CTRE magnetic in relative mode with sensor in phase with output

    if (m_talonValidL1) {
        motorL1->SetInverted(true);
        motorL1->SetNeutralMode(NeutralMode::Coast);
        motorL1->Set(ControlMode::PercentOutput, 0.0);
        motorL1->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorL1->SetSensorPhase(false);
        motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    }

    if (m_talonValidL2) {
    	motorL2->SetInverted(true);
        motorL2->SetNeutralMode(NeutralMode::Coast);
        motorL2->Set(ControlMode::Follower, 1);
    }

    if (m_talonValidR3) {
        motorR3->SetInverted(true);
        motorR3->SetNeutralMode(NeutralMode::Coast);
        motorR3->Set(ControlMode::PercentOutput, 0.0);
        motorR3->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorR3->SetSensorPhase(false);
        motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    }

    if (m_talonValidR4) {
        motorR4->SetInverted(true);
        motorR4->SetNeutralMode(NeutralMode::Coast);
        motorR4->Set(ControlMode::Follower, 3);
    }

    // Set to low gear (switch to high in teleop)
    m_lowGear = true;
    MoveShiftGears(m_lowGear);

	// Adjust kP for encoder being used -- CPR of ___ is the reference
	// Ramp rate is "seconds to full speed"
	// Peak output is percent of full speed
	// Set motor peak output levels

    if (m_talonValidL1) {
    	motorL1->Config_kP(m_slotIndex, m_distKp, m_timeout);
    	motorL1->ConfigClosedloopRamp(m_CL_rampRate, m_timeout);
    	motorL1->ConfigClosedLoopPeakOutput(m_slotIndex, m_distMaxOut, m_timeout);
    	motorL1->ConfigPeakOutputForward(peakOutput, m_timeout);
    	motorL1->ConfigPeakOutputReverse(-peakOutput, m_timeout);
    }
    if (m_talonValidR3) {
    	motorR3->Config_kP(m_slotIndex, m_distKp, m_timeout);
    	motorR3->ConfigClosedloopRamp(m_CL_rampRate, m_timeout);
    	motorR3->ConfigClosedLoopPeakOutput(m_slotIndex, m_distMaxOut, m_timeout);
    	motorR3->ConfigPeakOutputForward(peakOutput, m_timeout);
    	motorR3->ConfigPeakOutputReverse(-peakOutput, m_timeout);
    }

    // If both drive talons not valid, disable safety timer
   	diffDrive->SetSafetyEnabled(false);

    // Initialize the NavX MXP gyro
 	gyro = new AHRS(SPI::Port::kMXP);
 	gyro->SetName("DriveTrain", "Gyro");
   	std::printf("2135: DT Gyro Sub %s Name %s\n", gyro->GetSubsystem().c_str(), gyro->GetName().c_str());

 	// Wait for gyro to be connected before proceeding to reset
 	while (!gyro->IsConnected()) {
 		static 	double 	time = frc::GetTime();
 		if (frc::GetTime() - time > 0.250)
 			std::printf("2135: Waiting for gyro\n");
 	}

   	std::printf("2135: DT Gyro Firmware Version - %s\n", gyro->GetFirmwareVersion().c_str());
   	gyro->Reset();
   	gyro->ResetDisplacement();

   	// Calibrate the gyro
   	std::printf("2135: DT Gyro Calibration Started\n");
   	gyro->ZeroYaw();
   	std::printf("2135: DT Gyro Calibration Finished\n");

 	// Initialize PID for Turn PID
   	driveTurnPIDOutput = new PIDOutputDriveTurn(diffDrive);
   	driveTurnPIDLoop = new PIDController(m_turnKp, 0.0, 0.0, gyro, driveTurnPIDOutput, 0.010);

   	// Settings for Turn PID
   	driveTurnPIDLoop->SetPID(m_turnKp, 0.0, 0.0);
   	driveTurnPIDLoop->SetOutputRange(-m_turnMaxOut, m_turnMaxOut);
   	driveTurnPIDLoop->SetAbsoluteTolerance(m_turnErrDeg);
#endif
}

void Drivetrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
#ifndef ROBORIO_STANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

#endif
}

void Drivetrain::Periodic() {
    // Put code here to be run every loop
	double	encoderLeft = 0.0;
	double	encoderRight = 0.0;
	double	gyroYaw = 0.0;

#ifndef ROBORIO_STANDALONE
	if (m_talonValidL1)
		encoderLeft = motorL1->GetSelectedSensorPosition(0);
	if (m_talonValidR3)
		encoderRight = motorR3->GetSelectedSensorPosition(0);
	gyroYaw = gyro->GetYaw();
#endif
	SmartDashboard::PutNumber("DT_Encoder_L", encoderLeft);
	SmartDashboard::PutNumber("DT_Encoder_R", encoderRight);
	SmartDashboard::PutNumber("DT_GyroAngle", gyroYaw);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivetrain::Initialize(void) {
	std::printf("2135: DT Initialize\n");

	// When disabled, low gear and coast mode to allow easier pushing
	if (frc::RobotState::IsDisabled()) {
		m_lowGear = true;
		m_brakeMode = false;
	}
	else {
		// Enabled and teleop - high gear and coast mode
		if (frc::RobotState::IsOperatorControl()) {
			m_lowGear = false;
			m_brakeMode = false;
		}
		else {	// Auton always low gear and brake mode
			m_lowGear = true;
			m_brakeMode = true;
		}
	}

	MoveShiftGears(m_lowGear);
    MoveSetBrakeMode(m_brakeMode);
}

//	Joystick movement during Teleop

void Drivetrain::MoveWithJoystick(std::shared_ptr<Joystick> joystick)
{
#ifndef ROBORIO_STANDALONE
	double xValue;
	double yValue;

	xValue = joystick->GetX() * m_driveXScaling;
	yValue = joystick->GetY() * m_driveYScaling;

	if (m_talonValidL1 && m_talonValidR3)
		diffDrive->ArcadeDrive(-yValue, xValue, true);
#endif
}

//	Automatic Drive Spin movement

void Drivetrain::MoveSpin(bool spinRight)
{
	double spinSpeed = m_driveSpin;

	if (!spinRight)
		spinSpeed *= -1.0;

#ifndef ROBORIO_STANDALONE
	if (m_talonValidL1 && m_talonValidR3)
		diffDrive->TankDrive(spinSpeed, -spinSpeed, false);
#endif
}

//	Automatic Drive Spin movement

void Drivetrain::MoveStop()
{
#ifndef ROBORIO_STANDALONE
	if (m_talonValidL1 && m_talonValidR3)
		diffDrive->TankDrive(0.0, 0.0, false);
#endif
}

//	Shift transmission gears

void Drivetrain::MoveShiftGears(bool lowGear)
{
	m_lowGear = lowGear;

	std::printf("2135: DT %s gear\n", (lowGear) ? "LOW" : "HIGH");
	SmartDashboard::PutBoolean("DT Low Gear", lowGear);

#ifndef ROBORIO_STANDALONE
    shifter->Set( (lowGear) ? shifter->kForward : shifter->kReverse);
#endif
}

//	Set Talon brake mode

void Drivetrain::MoveSetBrakeMode(bool brakeMode)
{
	m_brakeMode = brakeMode;

	std::printf("2135: DT %s mode\n", (brakeMode) ? "BRAKE" : "COAST");
	SmartDashboard::PutBoolean("DT Brake Mode", brakeMode);

#ifndef ROBORIO_STANDALONE
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
#endif
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

///////////////////////////////////////////////////////////////////////////////

// Autonomous driving PID initialization and setup

void Drivetrain::MoveDriveDistancePIDInit(double inches)
{
	// Range check the requested distance
	if (inches > m_distMaxInches) {
		inches = m_distMaxInches;
		std::printf("2135: DT m_distTargetInches limited by m_distMaxInches %f\n", m_distMaxInches);
	}
	m_distTargetInches = inches;
	m_distTargetCounts = inches * CountsPerInch;
	std::printf("2135: DTDD Init %5.2f counts, %5.2f inches, %5.2f CountsPerInch\n",
			m_distTargetCounts, m_distTargetInches, CountsPerInch);

#ifndef ROBORIO_STANDALONE
	// Initialize the encoders to start movement at reference of zero counts
	if (m_talonValidL1)
		motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
	if (m_talonValidR3)
		motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

	// Set the target distance in terms of wheel rotations
	if (m_talonValidL1)
		motorL1->Set(ControlMode::Position, m_distTargetCounts);
	if (m_talonValidR3)
		motorR3->Set(ControlMode::Position, -m_distTargetCounts);

	// Disable motor safety helper during PID
   	diffDrive->SetSafetyEnabled(false);
#endif

	// Start safety timer to be distance divided by 80 inches plus 2.0 sec extra
	// 97.5 -> 3.2 seconds, 320 -> 6.0 seconds
	m_safetyTimeout = (fabs(m_distTargetInches) / 80.0) + 2.0;
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
}

// Autonomous driving PID periodic execution

void Drivetrain::MoveDriveDistancePIDExecute()
{
	// No work needed since Talon does it internally
}

// Autonomous driving PID setpoint monitor

bool Drivetrain::MoveDriveDistanceIsPIDAtSetpoint()
{
	bool pidFinished = false;
	int curCounts_L = 0;
	int curCounts_R = 0;
	int closedLoopError_L = 0;
	int closedLoopError_R = 0;
	double motorOutput_L = 0.0;
	double motorOutput_R = 0.0;
	double errorInInches_L = 0.0;
	double errorInInches_R = 0.0;

#ifndef ROBORIO_STANDALONE
	if (m_talonValidL1) {
		curCounts_L = motorL1->GetSelectedSensorPosition(m_pidIndex);
		motorOutput_L = motorL1->GetMotorOutputPercent();
		closedLoopError_L = motorL1->GetClosedLoopError(m_pidIndex);
	}
	if (m_talonValidR3) {
		curCounts_R = motorR3->GetSelectedSensorPosition(m_pidIndex);
		motorOutput_R = motorR3->GetMotorOutputPercent();
		closedLoopError_R = motorR3->GetClosedLoopError(m_pidIndex);
	}
#endif

	// Check to see if the error is in an acceptable number of inches. (R is negated)
	errorInInches_L = CountsToInches(m_distTargetCounts - (double)curCounts_L);
	errorInInches_R = CountsToInches(-m_distTargetCounts - (double)curCounts_R);

	// cts = Encoder Counts, CLE = Closed Loop Error, Out = Motor Output
	double secs = (double)RobotController::GetFPGATime() / 1000000.0;
	std::printf("2135: DTDD %5.3f (L R) cts %5d %5d in %5.2f %5.2f CLE %5d %5d, Out %5.3f %5.3f errIn %5.2f %5.2f\n",
			secs, curCounts_L, curCounts_R, CountsToInches(curCounts_L), CountsToInches(curCounts_R),
			closedLoopError_L, closedLoopError_R, motorOutput_L, motorOutput_R, errorInInches_L, errorInInches_R);

	if ((fabs(errorInInches_L) < m_distErrInches) && (fabs(errorInInches_R) < m_distErrInches)) {
		pidFinished = true;
	}

	// Check to see if the Safety Timer has timed out.
	if (m_safetyTimer.Get() >= m_safetyTimeout) {
		std::printf("2135: DTDD Safety timer has timed out\n");
		pidFinished = true;
	}

	// If on target or safety time has expired
	return pidFinished;
}

// Autonomous driving PID to clean up after reaching the target position

void Drivetrain::MoveDriveDistancePIDStop(void)
{
	int curCounts_L = 0;
	int curCounts_R = 0;
	int closedLoopError_L = 0;
	int closedLoopError_R = 0;
	double motorOutput_L = 0.0;
	double motorOutput_R = 0.0;
	double errorInInches_L = 0.0;
	double errorInInches_R = 0.0;

	// Stop the safety timer
	std::printf("2135: DTDD TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

#ifndef ROBORIO_STANDALONE
	// Change from PID position-loop back to PercentVbus for driver control
	motorL1->Set(ControlMode::PercentOutput, 0.0);
	motorR3->Set(ControlMode::PercentOutput, 0.0);

	if (m_talonValidL1) {
		curCounts_L = motorL1->GetSelectedSensorPosition(m_pidIndex);
		motorOutput_L = motorL1->GetMotorOutputPercent();
		closedLoopError_L = motorL1->GetClosedLoopError(m_pidIndex);
	}
	if (m_talonValidR3) {
		curCounts_R = motorR3->GetSelectedSensorPosition(m_pidIndex);
		motorOutput_R = motorR3->GetMotorOutputPercent();
		closedLoopError_R = motorR3->GetClosedLoopError(m_pidIndex);
	}

	// Re-enable the motor safety helper
    if (m_talonValidL1 && m_talonValidR3)
    	diffDrive->SetSafetyEnabled(true);
#endif

	// Snapshot of results to SmartDashboard
//	SmartDashboard::PutNumber("DD PID L", curCounts_L);
//	SmartDashboard::PutNumber("DD PID R", curCounts_R);
//	SmartDashboard::PutNumber("DD TIME", m_safetyTimer.Get());

	// Check to see if the error is in an acceptable number of inches. (R is negated)
	errorInInches_L = CountsToInches(m_distTargetCounts - (double)curCounts_L);
	errorInInches_R = CountsToInches(-m_distTargetCounts - (double)curCounts_R);

	// Print final results to console
	double secs = (double)RobotController::GetFPGATime() / 1000000.0;
	std::printf("2135: DTDD %5.3f (L R) cts %5d %5d in %5.2f %5.2f CLE %5d %5d, Out %5.3f %5.3f errIn %5.2f %5.2f\n",
			secs, curCounts_L, curCounts_R, CountsToInches(curCounts_L), CountsToInches(curCounts_R),
			closedLoopError_L, closedLoopError_R, motorOutput_L, motorOutput_R, errorInInches_L, errorInInches_R);
}

///////////////////////////////////////////////////////////////////////////////

// Autonomous turn PID initialization and setup

void Drivetrain::MoveDriveTurnPIDInit(double angle)
{
	m_turnAngle = angle;
	std::printf("2135: DTDT Init %f degrees\n", m_turnAngle);

#ifndef ROBORIO_STANDALONE
	// Initialize the encoders to start movement at reference of zero counts
	if (m_talonValidL1)
		motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
	if (m_talonValidR3)
		motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

	gyro->ZeroYaw();
	driveTurnPIDLoop->SetSetpoint(angle);
	driveTurnPIDLoop->Enable();

	// Disable motor safety helper during PID
   	diffDrive->SetSafetyEnabled(false);
#endif

	// Start safety timer with 1.0 sec padding (45 deg -> 0.75 sec, 90 deg -> 1.30 sec)
	m_safetyTimeout = (fabs(m_turnAngle) * 0.020) + 1.0;
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
}

// Autonomous turn PID periodic execution

void Drivetrain::MoveDriveTurnPIDExecute(void)
{
	// No work needed since done by PID controller
}

// Autonomous turn PID setpoint monitoring

bool Drivetrain::MoveDriveTurnIsPIDAtSetPoint(void)
{
	bool pidFinished = false;
	int curCounts_L = 0;
	int curCounts_R = 0;
	double motorOutput_L = 0.0;
	double motorOutput_R = 0.0;
	double curAngle = 0.0;
	double errorInDegrees = 0.0;

#ifndef ROBORIO_STANDALONE
	if (m_talonValidL1) {
		curCounts_L = motorL1->GetSelectedSensorPosition(m_pidIndex);
		motorOutput_L = motorL1->GetMotorOutputPercent();
	}
	if (m_talonValidR3) {
		curCounts_R = motorR3->GetSelectedSensorPosition(m_pidIndex);
		motorOutput_R = motorR3->GetMotorOutputPercent();
	}
	curAngle = gyro->GetYaw();
#endif

	errorInDegrees = m_turnAngle - curAngle;

	double secs = (double)RobotController::GetFPGATime() / 1000000.0;
	std::printf("2135: DTDT %5.3f deg %4.2f -> %4.2f (err %4.2f) cts %5d %5d Out %4.2f %4.2f\n",
			secs, curAngle, m_turnAngle, errorInDegrees,
			curCounts_L, curCounts_R, motorOutput_L, motorOutput_R);

#ifndef ROBORIO_STANDALONE
	if (driveTurnPIDLoop->OnTarget())
		pidFinished = true;
#endif

	// Check to see if the Safety Timer has timed out.
	if (m_safetyTimer.Get() >= m_safetyTimeout) {
		std::printf("2135: DTDT Safety timer has timed out\n");
		pidFinished = true;
	}

	// If on target or safety time has expired
	return pidFinished;
}

// Autonomous turn PID to clean up after reaching the target position

void Drivetrain::MoveDriveTurnPIDStop(void)
{
	int curCounts_L = 0;
	int curCounts_R = 0;
	double motorOutput_L = 0.0;
	double motorOutput_R = 0.0;
	double curAngle = 0.0;
	double errorInDegrees = 0.0;

	// Stop the safety timer
	std::printf("2135: DTDT TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

#ifndef ROBORIO_STANDALONE
	driveTurnPIDLoop->Disable();
	curAngle = gyro->GetYaw();

	// Re-enable the motor safety helper
    if (m_talonValidL1 && m_talonValidR3)
    	diffDrive->SetSafetyEnabled(true);
#endif

	// Snapshot of results to SmartDashboard
//	SmartDashboard::PutNumber("DT DEG", curAngle);
//	SmartDashboard::PutNumber("DT TIME", m_safetyTimer.Get());

	errorInDegrees = m_turnAngle - curAngle;

	// Print final results to console
	double secs = (double)RobotController::GetFPGATime() / 1000000.0;
	std::printf("2135: DTDT %5.3f deg %4.2f -> %4.2f (err %4.2f) cts %5d %5d Out %4.2f %4.2f\n",
			secs, curAngle, m_turnAngle, errorInDegrees,
			curCounts_L, curCounts_R, motorOutput_L, motorOutput_R);
}

///////////////////////////////////////////////////////////////////////////////

void Drivetrain::ResetSensors(void) {
#ifndef ROBORIO_STANDALONE
	if (m_talonValidL1)
		motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
	if (m_talonValidR3)
		motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
	gyro->ZeroYaw();
#endif
}
