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

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/DriveTeleop.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {
	double peakOutput = 1.0;

	std::printf("2135: Drivetrain Constructor\n");
#ifndef ROBORIO_STANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL1 = RobotMap::drivetrainMotorL1;
    motorR3 = RobotMap::drivetrainMotorR3;
    diffDrive = RobotMap::drivetrainDiffDrive;
    motorL2 = RobotMap::drivetrainMotorL2;
    motorR4 = RobotMap::drivetrainMotorR4;
    shifter = RobotMap::drivetrainShifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Display Talon SRX firmware versions
    std::printf("2135: Motor L1 ID %d ver %d.%d\n", motorL1->GetDeviceID(),
    		motorL1->GetFirmwareVersion()/256, motorL1->GetFirmwareVersion()%256);
    std::printf("2135: Motor L2 ID %d ver %d.%d\n", motorL2->GetDeviceID(),
    		motorL2->GetFirmwareVersion()/256, motorL2->GetFirmwareVersion()%256);
    std::printf("2135: Motor R3 ID %d ver %d.%d\n", motorR3->GetDeviceID(),
    		motorR3->GetFirmwareVersion()/256, motorR3->GetFirmwareVersion()%256);
    std::printf("2135: Motor R4 ID %d ver %d.%d\n", motorR4->GetDeviceID(),
    		motorR4->GetFirmwareVersion()/256, motorR4->GetFirmwareVersion()%256);

    //Retrieve drivetrain modifiers from RobotConfig
    RobotConfig* config = RobotConfig::GetInstance();
	config->GetValueAsDouble("DT_PeakOutput", peakOutput, 1.0);
	config->GetValueAsDouble("DT_DriveScaling", m_driveScaling, 1.0);
    config->GetValueAsDouble("DT_TurnScaling", m_turnScaling, 1.0);
	if ((m_turnScaling < 0.0) || (m_turnScaling > 1.0)) {
		std::printf("2135: ERROR - m_turnScaling preference invalid - %f [0.0 .. 1.0]\n", m_turnScaling);
	}
    config->GetValueAsDouble("DT_DriveSpin", m_driveSpin, 0.45);
    config->GetValueAsDouble("DT_DriveKp", m_distKp, 0.75);
    config->GetValueAsDouble("DT_AutonTurnKp", m_turnKp, 0.08);
	config->GetValueAsInt("DT_AllowedCLError", m_CL_allowError, CTRE_Mag_CPR / 360);

    //Invert the direction of the motors
    motorL1->SetInverted(true);
    motorL2->SetInverted(true);
    motorR3->SetInverted(true);
    motorR4->SetInverted(true);
    motorL1->Set(ControlMode::PercentOutput, 0.0);
    motorL2->Set(ControlMode::Follower, 1);
    motorR3->Set(ControlMode::PercentOutput, 0.0);
    motorR4->Set(ControlMode::Follower, 3);

    // Set to coast mode (in comparison to brake)
    motorL1->SetNeutralMode(NeutralMode::Coast);
    motorR3->SetNeutralMode(NeutralMode::Coast);

    // Set encoder as a CTRE magnetic in relative mode with sensor in phase with output
    motorL1->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
    motorL1->SetSensorPhase(false);
    motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    motorR3->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
    motorR3->SetSensorPhase(false);
    motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

    // Set to low gear (switch to high in teleop)
    m_lowGear = true;
    MoveShiftGears(m_lowGear);

	// Adjust kP for encoder being used -- CPR of ___ is the reference
	motorL1->Config_kP(m_slotIndex, m_distKp, m_timeout);
	motorR3->Config_kP(m_slotIndex, m_distKp, m_timeout);

	// Set motor peak output levels
	motorL1->ConfigPeakOutputForward(peakOutput, m_timeout);
	motorL1->ConfigPeakOutputReverse(-peakOutput, m_timeout);
	motorR3->ConfigPeakOutputForward(peakOutput, m_timeout);
	motorR3->ConfigPeakOutputReverse(-peakOutput, m_timeout);

	// Allowed Closed Loop Eroor - default in Talon

	diffDrive->SetSafetyEnabled(true);

 	gyro = new AHRS(SPI::Port::kMXP);
// 	LiveWindow::GetInstance()->AddSensor("IMU", "Gyro", gyro); // TODO: Remove deprecated call

 	// Calibrate the gyro
   	std::printf("2135: DriveTrain Gyro Calibration Started\n");
   	gyro->Reset();
   	gyro->ZeroYaw();
   	std::printf("2135: DriveTrain Gyro Calibration Finished\n");

 	// Initialize PID for Turn PID
   	driveTurnPIDOutput = new PIDOutputDriveTurn(diffDrive);
   	driveTurnPIDLoop = new PIDController(0.08, 0.0, 0.0, gyro, driveTurnPIDOutput);

   	// Settings for Turn PID // TODO: Calculate real PID and outputs and get from either defaults or Robot Config
   	driveTurnPIDLoop->SetPID(0.08, 0.0, 0.0);
   	driveTurnPIDLoop->SetOutputRange(-1.0, 1.0);
   	driveTurnPIDLoop->SetAbsoluteTolerance(2.0);
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

#ifndef ROBORIO_STANDALONE
	SmartDashboard::PutNumber("DT_Encoder_L", motorL1->GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("DT_Encoder_R", motorR3->GetSelectedSensorPosition(0));
	SmartDashboard::PutNumber("DT_GyroAngle", gyro->GetAngle());

	double safetyHL;

    RobotConfig* config = RobotConfig::GetInstance();
	config->GetValueAsDouble("E_SafetyHeightLimit", safetyHL, 15.00);

	if (Robot::elevator->GetCurrentInches() > safetyHL)	{
		m_lowGear = true;
	    MoveShiftGears(m_lowGear);
	}
#endif
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivetrain::Initialize(frc::Preferences *RobotConfig) {
	std::printf("2135: Drivetrain Initialize\n");

	//Robot switches from low gear in auton to high gear in teleop
	if (frc::RobotState::IsAutonomous()) {
		m_lowGear = true;
		m_brakeMode = true;
	}
	else {
		m_lowGear = false;
		m_brakeMode = false;
	}

    // Set all motors to use coast mode and low gear when initialized.
	MoveShiftGears(m_lowGear);
    m_brakeMode = false;
    MoveSetBrakeMode(m_brakeMode);
}

//	Joystick movement during Teleop

void Drivetrain::MoveWithJoystick(std::shared_ptr<Joystick> joystick)
{
#ifndef ROBORIO_STANDALONE
	double xValue;
	double yValue;

	xValue = joystick->GetX();
	yValue = joystick->GetY();

	if (!m_lowGear) {
		xValue = xValue * m_driveScaling;
		yValue = yValue * m_driveScaling;
	}

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
	diffDrive->TankDrive(spinSpeed, -spinSpeed, false);
#endif
}

//	Shift transmission gears

void Drivetrain::MoveShiftGears(bool lowGear)
{
	m_lowGear = lowGear;

#ifndef ROBORIO_STANDALONE
    shifter->Set( (lowGear) ? shifter->kForward : shifter->kReverse);
#endif
}

//	Set Talon brake mode

void Drivetrain::MoveSetBrakeMode(bool brakeMode)
{
	m_brakeMode = brakeMode;

#ifndef ROBORIO_STANDALONE
	NeutralMode brakeOutput;
	brakeOutput = (brakeMode) ? NeutralMode::Brake : NeutralMode::Coast;
	motorL1->SetNeutralMode(brakeOutput);
	motorL2->SetNeutralMode(brakeOutput);
	motorR3->SetNeutralMode(brakeOutput);
	motorR4->SetNeutralMode(brakeOutput);
#endif
}

///////////////////////////////////////////////////////////////////////////////

// Autonomous driving PID initialization and setup

void Drivetrain::MoveDriveDistancePIDInit(double inches)
{
	 m_distTargetCounts = inches * CountsPerInch;
	 std::printf("2135: Encoder Distance Init %f counts, %f inches, %f CountsPerInch\n", m_distTargetCounts, inches, CountsPerInch);

#ifndef ROBORIO_STANDALONE
	 // Initialize the encoders to start movement at reference of zero counts
	 motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
	 motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

	 // Set the target distance in terms of wheel rotations
	 motorL1->Set(ControlMode::Position, m_distTargetCounts);
	 motorR3->Set(ControlMode::Position, -m_distTargetCounts);

	 // Set flag to indicate that the PID closed loop error is not yet valid
	 m_CL_pidStarted = false;

	 // Start safety timer
	 m_safetyTimeout = 3.5;
	 m_safetyTimer.Reset();
	 m_safetyTimer.Start();

	 // Disable motor safety helper during PID
	 diffDrive->SetSafetyEnabled(false);
#endif
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
	int closedLoopErrorLeft = 0, closedLoopErrorRight = 0;

#ifndef ROBORIO_STANDALONE
	closedLoopErrorLeft = motorL1->GetClosedLoopError(m_pidIndex);
	closedLoopErrorRight = motorR3->GetClosedLoopError(m_pidIndex);
#endif

	if (!m_CL_pidStarted && (abs(closedLoopErrorLeft) > Encoder_CPR) &&
				(abs(closedLoopErrorRight) > Encoder_CPR))
		{
			m_CL_pidStarted = true;
			std::printf("2135: Closed loop error has changed\n");
		}
	if (m_CL_pidStarted) {
		if ((abs(closedLoopErrorLeft) <= m_CL_allowError) &&
				(abs(closedLoopErrorRight) <= m_CL_allowError))
			{
				std::printf("2135: ClosedLoopError:     L: %d  R: %d\n",
					closedLoopErrorLeft, closedLoopErrorRight);
				pidFinished = true;
			}
	}

	// Check if safety timer has expired
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout)) {
		std::printf("2135: Safety Timer timed out %3.2f\n", m_safetyTimeout);
		pidFinished = true;
	}

	// If on target or safety time has expired
	return pidFinished;
}

// Autonomous driving PID to clean up after reaching the target position

void Drivetrain::MoveDriveDistancePIDStop(void)
{
#ifndef ROBORIO_STANDALONE
	// Stop the safety timer
	std::printf("2135: TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	// Change from PID position-loop back to PercentVbus for driver control
	motorL1->Set(ControlMode::PercentOutput, 0.0);
	motorR3->Set(ControlMode::PercentOutput, 0.0);

	// Snapshot of results to SmartDashboard
	SmartDashboard::PutNumber("DD PID L", motorL1->GetSelectedSensorPosition(m_pidIndex));
	SmartDashboard::PutNumber("DD PID R", motorR3->GetSelectedSensorPosition(m_pidIndex));
	SmartDashboard::PutNumber("DD TIME", m_safetyTimer.Get());

	// Print results to console
	std::printf("2135: TargetCounts: %3.2f   L: %5d  R: %5d\n", m_distTargetCounts,
		motorL1->GetSelectedSensorPosition(m_pidIndex), motorR3->GetSelectedSensorPosition(m_pidIndex));

	// Do not shift back to high gear in case another auton command is running

	// Re-enable the motor safety helper
	diffDrive->SetSafetyEnabled(false);
#endif
}

///////////////////////////////////////////////////////////////////////////////

// Autonomous turn PID initialization and setup

void Drivetrain::MoveDriveTurnPIDInit(double angle) {
#ifndef ROBORIO_STANDALONE
	gyro->ZeroYaw();

	std::printf("2135: Move Drive Turn Init %f degrees\n", angle);
	driveTurnPIDLoop->SetSetpoint(angle);
	driveTurnPIDLoop->Enable();
#endif
}

// Autonomous turn PID periodic execution

void Drivetrain::MoveDriveTurnPIDExecute(void) {
	// No work needed
	std::printf("2135: Move Drive Turn Exec %f degrees\n", gyro->GetAngle());
}

// Autonomous turn PID setpoint monitoring

bool Drivetrain::MoveDriveTurnIsPIDAtSetPoint(void) {
	bool pidFinished = false;

#ifndef ROBORIO_STANDALONE
	if (driveTurnPIDLoop->OnTarget())
		pidFinished = true;
#endif
	return pidFinished;
}

// Autonomous turn PID to clean up after reaching the target position

void Drivetrain::MoveDriveTurnPIDStop(void){
#ifndef ROBORIO_STANDALONE
	std::printf("2135: Move Drive Turn Stop at %f degrees\n", gyro->GetAngle());

	driveTurnPIDLoop->Disable();
#endif
}
