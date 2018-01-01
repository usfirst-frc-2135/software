// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Chassis.h"
#include "../RobotMap.h"
#include "../Commands/DriveTeleop.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Chassis::Chassis() : Subsystem("Chassis") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL1 = RobotMap::chassisMotorL1;
    motorR3 = RobotMap::chassisMotorR3;
    motorL2 = RobotMap::chassisMotorL2;
    motorR4 = RobotMap::chassisMotorR4;
    shifter = RobotMap::chassisShifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    drive = RobotMap::chassisDrive;

    gyro = RobotMap::chassisGyro;

    std::printf("2135: Chassis Constructor\n");

    // Note that we cannot load smartdashboard values here - driverstation may not be connected yet

    // Drivetrain Talon settings - Teleop mode

    // Make second Talon SRX controller on each side of drivetrain follow the main Talon SRX
    motorL1->Set(ControlMode::PercentOutput, 0.0);
    motorL2->Set(ControlMode::Follower, 1);
    motorR3->Set(ControlMode::PercentOutput, 0.0);
    motorR4->Set(ControlMode::Follower, 3);

    // Drivetrain Talon settings - Autonomous modes

    // Feedback device is US Digital S4 CPR 120 encoder
	motorL1->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, pidIndex, timeout);
	motorR3->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, pidIndex, timeout);

    // Invert the direction of the right hand side motors and sensors
	// TODO: See if we need these
	motorL1->SetInverted(true);
	motorR3->SetInverted(false);

	motorL1->SetSensorPhase(true);
	motorR3->SetSensorPhase(false);

	// Set drive Talons to profile 0
	motorL1->SelectProfileSlot(0, pidIndex);
	motorR3->SelectProfileSlot(0, pidIndex);

    // Set all motors to use coast mode and not brake when stopped, start in low gear
    m_brakeMode = true;
    MoveSetBrakeNotCoastMode(m_brakeMode);
    m_lowGear = true;
	MoveShiftGears(m_lowGear);

	//	Initialize drivetrain modifiers
    m_driveDirection = -1.0;	// Initialize drivetrain direction for driving forward or backward
    m_driveScaling = 1.0;		// Initialize scaling factor and disable it
    m_driveSpin = 0.45;			// Initialize power setting used for spin turns

    // 	Initialize closed loop parameters for Talon PID - ramp rate, close loop error, target rotations
    m_pidTargetCounts = 0.0;
    m_CL_pidStarted = false;

    // NOTE: Calibrate gyro - this takes a few seconds--must not be in mode switch to Teleop or Auton
    std::printf("2135: Starting gyro calibration\n");
	gyro->Calibrate();
    std::printf("2135: Stopping gyro calibration\n");

	// Autonomous turn PID controller - SHOULD BE AFTER GYRO IS CALIBRATED
    m_turnKP = CHS_TURNKP_D;
    SmartDashboard::PutNumber(CHS_TURNKP, m_turnKP);
    std::printf("2135: Turn PID Kp: %f\n", m_turnKP);

    driveTurnPIDOutput = new PIDOutputDriveTurn(drive);
    driveTurnPIDLoop = new PIDController(m_turnKP, 0.0, 0.0, gyro.get(), driveTurnPIDOutput);

    // Adjust Kp for encoder being used
    driveVisionPIDSource = new PIDSourceDriveVision();
    driveVisionPIDOutput = new PIDOutputDriveVision(drive);
    driveVisionPIDLoop = new PIDController((CHS_CAMTURNKP_D / Encoder_CPR) * 1.5, 0.0, 0.0, driveVisionPIDSource, driveVisionPIDOutput);

    m_turnScaling = Robot::LoadPreferencesVariable(CHS_TURN_SCALING, CHS_TURN_SCALING_D);
	if ((m_turnScaling < 0.0) || (m_turnScaling > 1.0)) {
		std::printf("2135: ERROR - m_turnScaling preference invalid - %f [0.0 .. 1.0]\n", m_turnScaling);
	}
	SmartDashboard::PutNumber(CHS_TURN_SCALING, m_turnScaling);
}

void Chassis::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.


// Initialize is called whenever we change robot modes Disabled->Teleop, Disabled->Autonomous
//	It is used to reinitialize the chassis settings to a known condition and read smartdashboard changes

void Chassis::Initialize(frc::Preferences *prefs)
{
	// Initialize SmartDashboard values - if any

	std::printf("2135: Chassis Initialize\n");

	// Robot is in low gear in autonomous and high gear in teleop
	if (frc::RobotState::IsAutonomous()) {
		m_lowGear = true;
	    m_brakeMode = true;
	}
	else {
		m_lowGear = false;
	    m_brakeMode = false;
	}

	// Brake/coast mode for talon speed controller
	MoveShiftGears(m_lowGear);
	MoveSetBrakeNotCoastMode(m_brakeMode);

	// Drive invert direction the stick moves the robot
	SmartDashboard::PutBoolean(CHS_DRIVE_DIRECTION, false);

	// Scale maximum driving speed - if in beginner mode
	m_driveScaling = Robot::LoadPreferencesVariable(CHS_DRIVE_SCALING, CHS_DRIVE_SCALING_D);

	// Speed to apply to the motors for spin turns
	m_driveSpin = Robot::LoadPreferencesVariable(CHS_DRIVE_SPIN, CHS_DRIVE_SPIN_D);

	// Closed Loop VoltageRampRate - in volts per second
	// NOTE: Tune this after main PID loop is working ONLY to eliminate initial lurching
	//	0.0 disables the ramp. Start tuning at full speed in one half second (12.0V/0.5s)
	double rampRate;
	rampRate = Robot::LoadPreferencesVariable(CHS_CL_RAMPRATESECS, CHS_CL_RAMPRATESECS_D);
	motorL1->ConfigOpenloopRamp(rampRate, timeout);
	motorR3->ConfigOpenloopRamp(rampRate, timeout);
	motorL1->ConfigClosedloopRamp(rampRate, timeout);
	motorR3->ConfigClosedloopRamp(rampRate, timeout);

	// Allowable Closed Loop Error - in Talon native units (480/1440 units per one rotation)
	m_CL_allowError = (int) Robot::LoadPreferencesVariable(CHS_CL_ALLOWERROR, CHS_CL_ALLOWERROR_D);
	m_CL_allowError *= USDigitalS4_CPR / 120.0;
	motorL1->ConfigAllowableClosedloopError(0, m_CL_allowError, timeout);
	motorR3->ConfigAllowableClosedloopError(0, m_CL_allowError, timeout);

	// Set closed loop peak output voltage to cap maximum speed
	// Note this is persistent in Talon, so set it even if not used
	double peakOutputVoltage = 1.0;
	peakOutputVoltage = Robot::LoadPreferencesVariable(CHS_CL_PEAKOUTPCNT, CHS_CL_PEAKOUTPCNT_D);
	motorL1->ConfigPeakOutputForward(peakOutputVoltage, timeout);
	motorL1->ConfigPeakOutputReverse(-peakOutputVoltage, timeout);
	motorR3->ConfigPeakOutputForward(peakOutputVoltage, timeout);
	motorR3->ConfigPeakOutputReverse(-peakOutputVoltage, timeout);

	// Set closed loop nominal output voltage if doesn't quite reach target (NOT NEEDED)
	// Note this is persistent in Talon, so set it even if not used
	double nominalOutputVoltage = 0.0;
	nominalOutputVoltage = Robot::LoadPreferencesVariable(CHS_CL_NOMOUTPCNT, CHS_CL_NOMOUTPCNT_D);
	motorL1->ConfigNominalOutputForward(nominalOutputVoltage, timeout);
	motorL1->ConfigNominalOutputReverse(-nominalOutputVoltage, timeout);
	motorR3->ConfigNominalOutputForward(nominalOutputVoltage, timeout);
	motorR3->ConfigNominalOutputReverse(-nominalOutputVoltage, timeout);

	// Reset left/right encoder values
	motorL1->SetSelectedSensorPosition(0, pidIndex, timeout);
	motorR3->SetSelectedSensorPosition(0, pidIndex, timeout);

	// reset gyro to zero
	gyro->Reset();

	// drive heading angle
	SmartDashboard::PutNumber(AUTON_DRIVEHEADING, AUTON_DRIVEHEADING_D);

	m_turnScaling = Robot::LoadPreferencesVariable(CHS_TURN_SCALING, CHS_TURN_SCALING_D);
	if ((m_turnScaling < 0.0) || (m_turnScaling > 1.0)) {
		std::printf("2135: ERROR - m_turnScaling preference invalid - %f [0.0 .. 1.0]\n", m_turnScaling);
	}
	SmartDashboard::PutNumber(CHS_TURN_SCALING, m_turnScaling);

	m_invertEnable = Robot::LoadPreferencesVariable(CHS_INVERT_ENABLE, CHS_INVERT_ENABLE_D);
}


// UpdateSmartDashboardValues used during TelopPeriodic and AutonomousPeriodic to display sensor real time updates

void Chassis::UpdateSmartDashboardValues(void)
{
#ifndef ROBORIO_STANDALONE	// If not in RoboRIO standalone mode (no talons connected)
	SmartDashboard::PutNumber(CHS_ENCPOSITION_L, GetEncoderPosition(motorL1));
	SmartDashboard::PutNumber(CHS_ENCPOSITION_R, GetEncoderPosition(motorR3));
	SmartDashboard::PutNumber(CHS_CL_ERROR_L, motorL1->GetClosedLoopError(pidIndex));
	SmartDashboard::PutNumber(CHS_CL_ERROR_R, motorR3->GetClosedLoopError(pidIndex));
#endif
	SmartDashboard::PutNumber(CHS_GYROANGLE, gyro->GetAngle());
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Drivetrain and movement methods

// MoveWithJoystick is our main Teleop control of ArcadeDrive

void Chassis::MoveWithJoystick(std::shared_ptr<Joystick> joystick)
{
	double xValue;
	double yValue;

	// Retrieve the joystick values, if inverted drive is selected, flip the Y input
	xValue = joystick->GetX();
	yValue = joystick->GetY() * m_driveDirection;
	static int i = 0;
	if (i++ % 50 == 0)
		printf("x %f y %f\n", xValue, yValue);

	// If in high gear, use the scaling factor against the y-axis
	if (!m_lowGear) {
		xValue = xValue * m_driveScaling;
		yValue = yValue * m_driveScaling;
	}

	if (!m_lowGear && (m_turnScaling < 0.99)) {
		double scaledFactor;
		// Create a scaling factor which increases as Y increases (faster robot speed)
		scaledFactor = -(1.0 - m_turnScaling) * (fabs(yValue)) + 1.0;
		xValue = scaledFactor * xValue;
	}

	// Apply modified joystick input to the drive motors
	drive->ArcadeDrive( xValue, yValue, true );
}

// MoveSpin is a custom feature that can be hooked to a button for spin turns

void Chassis::MoveSpin(bool spinLeft)
{
	// Use input flag to perform a left/right turn using equal power, opposite direction on motors
	if (spinLeft)
		drive->TankDrive( m_driveSpin, -m_driveSpin, false );
	else
		drive->TankDrive( -m_driveSpin, m_driveSpin, false );
}

// MoveInvertDriveDirection is a custom feature to set robot drive direction to flip from front to back

void Chassis::MoveInvertDriveDirection(void)
{
	// m_invertEnable == true enables the invert direction function
	if (m_invertEnable == true) {
		// Toggle the drive direction and update the dashboard status
		m_driveDirection = -m_driveDirection;

		if (m_driveDirection > 0.0) {
			SmartDashboard::PutBoolean(CHS_DRIVE_DIRECTION, false);
		}
		else {
			SmartDashboard::PutBoolean(CHS_DRIVE_DIRECTION, true);
		}
	}
}

// MoveSetBrakeNotCoastMode is used to allow other functions and commands to change how the drive works

void Chassis::MoveSetBrakeNotCoastMode(bool brakeMode)
{
	NeutralMode brakeOutput;

	brakeOutput = (brakeMode) ? NeutralMode::Brake : NeutralMode::Coast;

	// If brake mode is requested, send to the Talons
	motorL1->SetNeutralMode(brakeOutput);
	motorL2->SetNeutralMode(brakeOutput);
	motorR3->SetNeutralMode(brakeOutput);
	motorR4->SetNeutralMode(brakeOutput);

	// Update the global setting
	m_brakeMode = brakeMode;
	SmartDashboard::PutBoolean(CHS_DRIVE_BRAKEMODE, brakeMode);
}

// MoveUsingMotorOutputs is used to allow other functions to control the drive with direct left/right inputs

void Chassis::MoveUsingMotorOutputs(double motorInputLeft, double motorInputRight)
{
	drive->TankDrive(motorInputLeft, motorInputRight, false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//	Drivetrain movement - Allow other functions to shift gears to low/high as requested

void Chassis::MoveShiftGears(bool lowGear)
{
	if (lowGear) {
		shifter->Set(shifter->kForward);
		m_lowGear = true;
	}
	else {
		shifter->Set(shifter->kReverse);
		m_lowGear = false;
	}
}

void Chassis::MoveShiftToggle(void)
{
	MoveShiftGears(!m_lowGear);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Closed loop movement - Drive a distance using PID loop in Talons

// MoveDriveDistancePIDInit is used at the beginning of distance PID command to start the PID loop in the Talon

void Chassis::MoveDriveDistancePIDInit(double inches)
{
	double proportional;

	m_pidTargetCounts = inches / InchesPerCount;
	std::printf("2135: Encoder Distance %f counts, %f inches\n", m_pidTargetCounts, inches);

	// Change the drive motors to be position-loop control modes
	motorL1->Set(ControlMode::Position, 0.0);
	motorR3->Set(ControlMode::Position, 0.0);

	// This should be set one time in constructor
	proportional = Robot::LoadPreferencesVariable(CHS_CL_PROPORTIONAL, CHS_CL_PROPORTIONAL_D);
	// Adjust Kp for encoder being used -- CPR of 120 is the reference
	motorL1->Config_kP(0, proportional, timeout);
	motorR3->Config_kP(0, proportional, timeout);

	// Initialize the encoders to start movement at reference of zero counts
	motorL1->SetSelectedSensorPosition(0, pidIndex, timeout);
	motorR3->SetSelectedSensorPosition(0, pidIndex, timeout);

	// Set the target distance in terms of wheel rotations (negative due to drivetrain direction)
	motorL1->Set(ControlMode::PercentOutput, -m_pidTargetCounts);
	motorR3->Set(ControlMode::PercentOutput, -m_pidTargetCounts);

	// Set flag to indicate that the PID closed loop error is not yet valid
    m_CL_pidStarted = false;

	//Start safety timer
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
	m_safetyTimeout = 3.5;

	// Disable safety feature during movement, since motors will be fed by loop
	drive->SetSafetyEnabled(false);
}

// MoveDriveDistancePIDExecuted is called repeatedly until the PID loop reaches the target

void Chassis::MoveDriveDistancePIDExecute(void)
{
	// No work needed since Talon does it all internally
}

bool Chassis::MoveDriveDistanceIsPIDAtSetpoint(void)
{
	// Verify that both encoders are on target
	bool pidFinished = false;
	int	closedLoopErrorLeft = 0, closedLoopErrorRight = 0;

	// Detect if closed loop error has been updated once after start
	// TODO: Do we need to wait for a rotation now that command is working better
	closedLoopErrorLeft = motorL1->GetClosedLoopError(0);
	closedLoopErrorRight = motorR3->GetClosedLoopError(0);
	if (!m_CL_pidStarted && (abs(closedLoopErrorLeft) > Encoder_CPR) &&
			(abs(closedLoopErrorRight) > Encoder_CPR))
	{
		m_CL_pidStarted = true;
		std::printf("2135: Closed loop error has changed\n");
	}

	// If closed loop error has been updated, then check to see if within tolerance
	if (m_CL_pidStarted) {
		if ((abs(closedLoopErrorLeft) <= m_CL_allowError) &&
			(abs(closedLoopErrorRight) <= m_CL_allowError)) {
			std::printf("2135: TargetCounts: %3.2f   L: %5d  R: %5d\n",
				m_pidTargetCounts, GetEncoderPosition(motorL1), GetEncoderPosition(motorR3));
			std::printf("2135: ClosedLoopError:      L: %d  R: %d\n",
				closedLoopErrorLeft, closedLoopErrorRight);
			pidFinished = true;
		}
	}

	// Check if safety timer has expired, set value to about 2x the cycle
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout)) {
		std::printf("2135: Safety Timer timed out %3.2f\n", m_safetyTimeout);
		pidFinished = true;
	}

	// If on target or safety timer has expired
	return pidFinished;
}

// MoveDriveDistancePIDStop is called to clean up after the PID loop reaches the target position

void Chassis::MoveDriveDistancePIDStop(void)
{
	// Stop the safety timer
	std::printf("2135: TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	SmartDashboard::PutNumber("DD PID L", GetEncoderPosition(motorL1));
	SmartDashboard::PutNumber("DD PID R", GetEncoderPosition(motorR3));
	SmartDashboard::PutNumber("DD TIME", m_safetyTimer.Get());

	// Change from PID position-loop back to PercentVbus for driver control
	motorL1->Set(ControlMode::PercentOutput, 0.0);
	motorR3->Set(ControlMode::PercentOutput, 0.0);

	// Do not shift back to high gear in case another auton command is running

	// Re-enable the motor safety helper (temporarily disabled)
	drive->SetSafetyEnabled(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Closed loop movement - Drive to a relative heading using PID loop in RoboRIO

void Chassis::MoveDriveHeadingInit(double angle)
{
	m_pidAngle = angle;

	// Reset the gyro to set a new turn reference heading
	gyro->Reset();

	// Program the PID target setpoint
	m_turnKP = SmartDashboard::GetNumber(CHS_TURNKP, CHS_TURNKP_D);
	driveTurnPIDLoop->SetPID(m_turnKP, 0.0, 0.0);
	driveTurnPIDLoop->SetSetpoint(angle);
	std::printf("2135: MoveDriveHeadingInit using angle: %f power: %f Kp: %f\n", angle, m_driveSpin, m_turnKP);

	// Enable the PID loop
	driveTurnPIDLoop->SetOutputRange(-m_driveSpin, m_driveSpin);
	driveTurnPIDLoop->SetAbsoluteTolerance(2.0);
	driveTurnPIDLoop->Enable();

	//Start safety timer
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
	m_safetyTimeout = 3.0;

	// Disable safety feature during movement, since motors will be fed by loop
	drive->SetSafetyEnabled(false);
}

bool Chassis::MoveDriveHeadingIsPIDAtSetPoint(void) {
	bool pidFinished = false;

	// Test the PID to see if it is on the programmed target
	if (driveTurnPIDLoop->OnTarget()) {
		pidFinished = true;
		std::printf("2135: TargetAngle: %3.2f   Actual: %3.2f\n", m_pidAngle, gyro->GetAngle());
	}

	// Check if safety timer has expired, set value to about 2x the cycle
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout)) {
		std::printf("2135: Safety Timer timed out %3.2f\n", m_safetyTimeout);
		pidFinished = true;
	}

	return pidFinished;
}

void Chassis::MoveDriveHeadingStop(void) {
	// Disable PID loop
	driveTurnPIDLoop->Disable();

	// Stop safety timer
	std::printf("2135: TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	SmartDashboard::PutNumber("DH GYRO", gyro->GetAngle());
	SmartDashboard::PutNumber("DH TIME", m_safetyTimer.Get());

	// Re-enable the motor safety helper (temporarily disabled)
	drive->SetSafetyEnabled(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Closed loop movement - Drive to a vision loop distance and angle using PID loop in RoboRIO

void Chassis::MoveDriveVisionHeadingDistanceInit(double angle, double distance)
{
	double visionAngle;
	double visionDistance;

	gyro->Reset();

	//Initialize the encoders to start movement at reference of zero counts
	motorL1->SetSelectedSensorPosition(0, pidIndex, timeout);
	motorR3->SetSelectedSensorPosition(0, pidIndex, timeout);

	// Grab vision target angle and distance from SmartDashboard

	// angle input parameter is not used--read directly from dashboard
	visionAngle = SmartDashboard::GetNumber(CAM_TURNANGLE, CAM_TURNANGLE_D);
	SmartDashboard::PutNumber("DV CAMA", visionAngle);
	driveVisionPIDOutput->SetTurnAngle(visionAngle);
	driveVisionPIDSource->SetTurnAngle(visionAngle);

	// Program the PID target setpoint in encoder counts (CPR * 4)
	visionDistance = SmartDashboard::GetNumber(CAM_DISTANCE, CAM_DISTANCE_D);
	SmartDashboard::PutNumber("DV CAMD", visionDistance);
	if (visionDistance > 0.0)					// If a valid vision distance
		visionDistance = visionDistance - 2.0;	// Adjust distance for camera sensor to peg (minus carriage)
	driveVisionPIDLoop->SetSetpoint(visionDistance / InchesPerCount);

	std::printf("2135: Leg 3 Distance: %f; Angle: %f\n", visionDistance, visionAngle);
	driveVisionPIDLoop->SetOutputRange(-0.5, 0.5);

	// Enable the PID loop (tolerance is in encoder count units)
	driveVisionPIDLoop->SetAbsoluteTolerance(1.0 / InchesPerCount);	// This is +/-, so 1" = 2.0 inches
	driveVisionPIDLoop->Enable();

	//Start safety timer
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
	m_safetyTimeout = 3.5;

	// Disable safety feature during movement, since motors will be fed by loop
	drive->SetSafetyEnabled(false);
}

bool Chassis::MoveDriveVisionHeadingIsPIDAtSetPoint(void)
{
	bool pidFinished = false;

	// Test the PID to see if it is on the programmed target
	if (driveVisionPIDLoop->OnTarget()) {
		pidFinished = true;

		std::printf("2135: Encoder Values on Target. L: %d, R: %d\n",
			GetEncoderPosition(motorL1), GetEncoderPosition(motorR3));
	}

	// Check if safety timer has expired, set value to about 2x the cycle
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout)) {
		std::printf("2135: Safety Timer timed out %3.2f\n", m_safetyTimeout);
		pidFinished = true;
	}

	return pidFinished;
}

void Chassis::MoveDriveVisionHeadingStop(void)
{
	double closedLoopError;

	// Disable PID loop
	driveVisionPIDLoop->Disable();

	// Stop safety timer
	std::printf("2135: TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	SmartDashboard::PutNumber("DV GYRO", gyro->GetAngle());
	SmartDashboard::PutNumber("DV DS L", (double)GetEncoderPosition(motorL1) * InchesPerCount);
	SmartDashboard::PutNumber("DV DS R", (double)GetEncoderPosition(motorR3) * InchesPerCount);
	SmartDashboard::PutNumber("DV TIME", m_safetyTimer.Get());

	// Gets closed loop error and prints it
	closedLoopError = driveVisionPIDLoop->GetError();
	std::printf("2135: ClosedLoopError: %f\n", closedLoopError);

	// Re-enable the motor safety helper (temporarily disabled)
	drive->SetSafetyEnabled(false);
}

int Chassis::GetEncoderPosition(std::shared_ptr<TalonSRX> mtr)
{
	return mtr->GetSelectedSensorPosition(pidIndex);
}
