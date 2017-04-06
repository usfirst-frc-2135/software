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
    robotDrive = RobotMap::chassisRobotDrive;
    motorL2 = RobotMap::chassisMotorL2;
    motorR4 = RobotMap::chassisMotorR4;
    shifter = RobotMap::chassisShifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    gyro = RobotMap::chassisGyro;

    printf("2135: Chassis Constructor\n");

    // Note that we cannot load smartdashboard values here - driverstation may not be connected yet

    // Drivetrain Talon settings - Teleop mode

    // Enable motor safety code on drive motors (temporarily disabled)
    // TODO: Can we enable motor safety and have auton run
    robotDrive->SetSafetyEnabled(false);

    // Make second Talon SRX controller on each side of drivetrain follow the main Talon SRX
    motorL2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    motorL2->Set(1);
    motorR4->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    motorR4->Set(3);
    motorL1->SetInverted(true);

    // TODO: Can we remove this code and have autonomous run
    motorL1->SetSafetyEnabled(false);
    motorL2->SetSafetyEnabled(false);
    motorR3->SetSafetyEnabled(false);
    motorR4->SetSafetyEnabled(false);

    // Drivetrain Talon settings - Autonomous modes

    // Feedback device is US Digital S4 CPR 120 encoder
	motorL1->SetFeedbackDevice(CANTalon::QuadEncoder);
	motorR3->SetFeedbackDevice(CANTalon::QuadEncoder);
	motorL1->ConfigEncoderCodesPerRev(USDigitalS4_CPR_120);
	motorR3->ConfigEncoderCodesPerRev(USDigitalS4_CPR_120);

    // Invert the direction of the right hand side motors and sensors
	motorL1->SetClosedLoopOutputDirection(true);
	motorR3->SetClosedLoopOutputDirection(false);

#ifdef CRUSH_SETTINGS
	motorL1->SetSensorDirection(true);
	motorR3->SetSensorDirection(false);
#else
	motorL1->SetSensorDirection(false);
	motorR3->SetSensorDirection(true);
#endif

	// Set drive Talons to profile 0
	motorL1->SelectProfileSlot(0);
	motorR3->SelectProfileSlot(0);


    // Set all motors to use coast mode and not brake when stopped
    m_brakeMode = false;
    MoveSetBrakeNotCoastMode(m_brakeMode);

	//	Initialize drivetrain modifiers
    m_driveDirection = 1.0;			// Initialize drivetrain direction for driving forward or backward
    m_driveScaling = 1.0;		// Initialize scaling factor and disable it
    m_driveSpin = 0.45;		// Initialize power setting used for spin turns

    // 	Initialize closed loop parameters for Talon PID - ramp rate, close loop error, target rotations
    m_pidTargetRotations = 0.0;
    m_CL_pidStarted = false;

    // Initialize to low gear
    m_lowGear = true;

	// set to low gear
	MoveShiftGears(true);

    // NOTE: Calibrate gyro - this takes a few seconds--must not be in mode switch to Teleop or Auton
    printf("2135: Starting gyro calibration\n");
	gyro->Calibrate();
    printf("2135: Stopping gyro calibration\n");

	// Autonomous turn PID controller - SHOULD BE AFTER GYRO IS CALIBRATED
    driveTurnPIDOutput = new DriveTurnPID(robotDrive);
    driveTurnPIDLoop = new PIDController(0.02, 0.0, 0.0, gyro.get(), driveTurnPIDOutput);

    driveVisionPIDSource = new DriveVisionPIDSource();
    driveVisionPIDOutput = new DriveVisionPID(robotDrive);
    driveVisionPIDLoop = new PIDController(CAM_TURNKP_D, 0.0, 0.0, driveVisionPIDSource, driveVisionPIDOutput);

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

	printf("2135: Chassis Initialize\n");

	// Robot is in low gear in autonomous and high gear in teleop
	if (frc::RobotState::IsAutonomous())
		MoveShiftGears(true);
	else
		MoveShiftGears(false);

	// Drive invert direction the stick moves the robot
	SmartDashboard::PutBoolean(CHS_DRIVE_DIRECTION, false);

	// Brake/coast mode for talon speed controller
    m_brakeMode = false;
    MoveSetBrakeNotCoastMode(m_brakeMode);

	// Scale maximum driving speed - if in beginner mode
	m_driveScaling = Robot::LoadPreferencesVariable(CHS_DRIVE_SCALING, CHS_DRIVE_SCALING_D);

	// Speed to apply to the motors for spin turns
	m_driveSpin = Robot::LoadPreferencesVariable(CHS_DRIVE_SPIN, CHS_DRIVE_SPIN_D);

	// Closed Loop VoltageRampRate - in volts per second
	// NOTE: Tune this after main PID loop is working ONLY to eliminate initial lurching
	//	0.0 disables the ramp. Start tuning at full speed in one half second (12.0V/0.5s)
	double rampRate;
	rampRate = Robot::LoadPreferencesVariable(CHS_CL_RAMPRATE, CHS_CL_RAMPRATE_D);
	motorL1->SetCloseLoopRampRate(rampRate);
	motorR3->SetCloseLoopRampRate(rampRate);

	// Allowable Closed Loop Error - in Talon native units (480 units per one rotation)
	m_CL_allowError = (int) Robot::LoadPreferencesVariable(CHS_CL_ALLOWERROR, CHS_CL_ALLOWERROR_D);
	motorL1->SetAllowableClosedLoopErr(m_CL_allowError);
	motorR3->SetAllowableClosedLoopErr(m_CL_allowError);

	// Set closed loop peak output voltage to cap maximum speed
	// Note this is persistent in Talon, so set it even if not used
	double peakOutputVoltage;
	peakOutputVoltage = Robot::LoadPreferencesVariable(CHS_CL_PEAKOUTVOLTS, CHS_CL_PEAKOUTVOLTS_D);
	motorL1->ConfigPeakOutputVoltage(peakOutputVoltage, -peakOutputVoltage);
	motorR3->ConfigPeakOutputVoltage(peakOutputVoltage, -peakOutputVoltage);

	// Set closed loop nominal output voltage if doesn't quite reach target (NOT NEEDED)
	// Note this is persistent in Talon, so set it even if not used
	double nominalOutputVoltage;
	nominalOutputVoltage = Robot::LoadPreferencesVariable(CHS_CL_NOMOUTVOLTS, CHS_CL_NOMOUTVOLTS_D);
	motorL1->ConfigNominalOutputVoltage(nominalOutputVoltage, -nominalOutputVoltage);
	motorR3->ConfigNominalOutputVoltage(nominalOutputVoltage, -nominalOutputVoltage);

	// Reset left/right encoder values
	motorL1->SetEncPosition(0);
	motorR3->SetEncPosition(0);

	// drive distance inches
	// Read from SmartDashboard
	SmartDashboard::PutNumber(CHS_CL_TARGETINCHES,Robot::LoadPreferencesVariable(CHS_CL_TARGETINCHES, CHS_CL_TARGETINCHES_D));

	// reset gyro to zero
	gyro->Reset();

	// drive heading angle
	SmartDashboard::PutNumber(AUTON_DRIVEHEADING, AUTON_DRIVEHEADING_D);
}


// UpdateSmartDashboardValues is used during TelopPeriodic and AutonomousPeriodic to display real time updates
//	of sensor values

void Chassis::UpdateSmartDashboardValues(void)
{
#ifndef ROBORIO_STANDALONE	// If not in RoboRIO standalone mode (no talons connected)
	SmartDashboard::PutNumber(CHS_ENCPOSITION_L, motorL1->GetEncPosition());
	SmartDashboard::PutNumber(CHS_ENCPOSITION_R, motorR3->GetEncPosition());
	SmartDashboard::PutNumber(CHS_ROTATIONS_L, motorL1->GetPosition());
	SmartDashboard::PutNumber(CHS_ROTATIONS_R, motorR3->GetPosition());
	SmartDashboard::PutNumber(CHS_CL_ERROR_L, motorL1->GetClosedLoopError());
	SmartDashboard::PutNumber(CHS_CL_ERROR_R, motorR3->GetClosedLoopError());
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

	// If in high gear, use the scaling factor against the y-axis
	// TODO: Why does scaling affect the X axis? Should it? (Maybe it's correct)
	if (!m_lowGear) {
		xValue = xValue * m_driveScaling;
		yValue = yValue * m_driveScaling;
	}

	// Apply modified joystick input to the drive motorsd
	robotDrive->ArcadeDrive( yValue, xValue, true );
}

// MoveSpin is a custom feature that can be hooked to a button for spin turns

void Chassis::MoveSpin(bool spinLeft)
{
	// Use input flag to perform a left/right turn using equal power, opposite direction on motors
	if (spinLeft)
		robotDrive->SetLeftRightMotorOutputs( m_driveSpin, -m_driveSpin );
	else
		robotDrive->SetLeftRightMotorOutputs( -m_driveSpin, m_driveSpin );
}

// MoveInvertDriveDirection is a custom feature to set robot drive direction to flip from front to back

void Chassis::MoveInvertDriveDirection(void)
{
	// Toggle the drive direction and update the dashboard status
	m_driveDirection = -m_driveDirection;

	if (m_driveDirection > 0.0) {
		SmartDashboard::PutBoolean(CHS_DRIVE_DIRECTION, false);
	}
	else {
		SmartDashboard::PutBoolean(CHS_DRIVE_DIRECTION, true);
	}
}

// MoveSetBrakeNotCoastMode is used to allow other functions and commands to change how the drive works

void Chassis::MoveSetBrakeNotCoastMode(bool brakeMode)
{
	// If brake mode is requested, send to the Talons
	if (brakeMode) {
		motorL1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		motorL2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		motorR3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		motorR4->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	}
	else {
		motorL1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		motorL2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		motorR3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		motorR4->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	}

	// Update the global setting
	m_brakeMode = brakeMode;
	SmartDashboard::PutBoolean(CHS_DRIVE_BRAKEMODE, brakeMode);
}

// MoveUsingMotorOutputs is used to allow other functions to control the drive with direct left/right inputs

void Chassis::MoveUsingMotorOutputs(double motorInputLeft, double motorInputRight)
{
	robotDrive->SetLeftRightMotorOutputs(motorInputLeft, motorInputRight);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Closed loop movement - Drive a distance using PID loop in Talons

// MoveDriveDistancePIDInit is used at the beginning of distance PID command to start the PID loop in the Talon

void Chassis::MoveDriveDistancePIDInit(double inches)
{
	double proportional;

	m_pidTargetRotations = inches / (WheelDiaInches * M_PI);
	printf("2135: Encoder Distance %f rotations, %f inches\n", m_pidTargetRotations, inches);

	// Shift into low gear during movement for better accuracy
	MoveShiftGears(true);

	// Change the drive motors to be position-loop control modes
	motorL1->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);
	motorL1->Set(0.0);
	motorR3->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);
	motorR3->Set(0.0);

	// Change to brake mode
	MoveSetBrakeNotCoastMode(true);

	// This should be set one time in constructor
	proportional = Robot::LoadPreferencesVariable(CHS_CL_PROPORTIONAL, CHS_CL_PROPORTIONAL_D);
	motorL1->SetPID(proportional, 0.0, 0.0);
	motorR3->SetPID(proportional, 0.0, 0.0);

	// Initialize the encoders to start movement at reference of zero counts
	motorL1->SetEncPosition(0);
	motorR3->SetEncPosition(0);

	// Set the target distance in terms of wheel rotations (negative due to drivetrain direction)
	motorL1->Set(-m_pidTargetRotations);
	motorR3->Set(-m_pidTargetRotations);

	// Set flag to indicate that the PID closed loop error is not yet valid
    m_CL_pidStarted = false;

	//Start safety timer
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
	m_safetyTimeout = 3.5;

	// Disable safety feature during movement, since motors will be fed by loop
	robotDrive->SetSafetyEnabled(false);
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

	// Detect if closed loop error has been updated once after start
	// TODO: Do we need to wait for a rotation now that command is working better
	if (!m_CL_pidStarted && (abs(motorL1->GetClosedLoopError()) > USDigitalS4_CPR_120*4) &&
			(abs(motorR3->GetClosedLoopError()) > USDigitalS4_CPR_120*4))
	{
		m_CL_pidStarted = true;
		printf("2135: Closed loop error has changed\n");
	}

	// If closed loop error has been updated, then check to see if within tolerance
	if (m_CL_pidStarted) {
		if ((abs(motorL1->GetClosedLoopError()) <= m_CL_allowError) &&
			(abs(motorR3->GetClosedLoopError()) <= m_CL_allowError)) {
			printf("2135: TargetRotations: %3.2f   L: %3.2f  R: %3.2f\n",
				m_pidTargetRotations, motorL1->GetPosition(), motorR3->GetPosition());
			printf("2135: ClosedLoopError:         L: %d  R: %d\n",
				motorL1->GetClosedLoopError(), motorR3->GetClosedLoopError());
			pidFinished = true;
		}
	}

	// Check if safety timer has expired, set value to about 2x the cycle
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout)) {
		printf("2135: Safety Timer timed out %3.2f\n", m_safetyTimeout);
		pidFinished = true;
	}

	// If on target or safety timer has expired
	return pidFinished;
}

// MoveDriveDistancePIDStop is called to clean up after the PID loop reaches the target position

void Chassis::MoveDriveDistancePIDStop(void)
{
	// Stop the safety timer
	printf("2135: TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	// Change to coast mode
	MoveSetBrakeNotCoastMode(false);

	// Change from PID position-loop back to PercentVbus for driver control
	motorL1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	motorL1->Set(0.0);
	motorR3->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	motorR3->Set(0.0);

	// Do not shift back to high gear in case another auton command is running

	// Re-enable the motor safety helper (temporarily disabled)
    // TODO: Can we enable motor safety and have auton run
	robotDrive->SetSafetyEnabled(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Closed loop movement - Drive to a relative heading using PID loop in RoboRIO

void Chassis::MoveDriveHeadingInit(double angle)
{
	m_pidAngle = angle;

	// Reset the gyro to set a new turn reference heading
	gyro->Reset();

	// Program the PID target setpoint
	driveTurnPIDLoop->SetSetpoint(angle);
	printf("2135: MoveDriveHeadingInit using angle: %f power: %f\n", angle, m_driveSpin);

	// Shift into low gear during movement for better accuracy
	MoveShiftGears(true);

	// Change to Brake mode
	MoveSetBrakeNotCoastMode(true);

	// Enable the PID loop
	driveTurnPIDLoop->SetOutputRange(-m_driveSpin, m_driveSpin);
	driveTurnPIDLoop->SetAbsoluteTolerance(2.0);
	driveTurnPIDLoop->Enable();

	//Start safety timer
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
	m_safetyTimeout = 2.0;

	// Disable safety feature during movement, since motors will be fed by loop
	robotDrive->SetSafetyEnabled(false);
}

bool Chassis::MoveDriveHeadingIsPIDAtSetPoint(void) {
	bool pidFinished = false;

	// Test the PID to see if it is on the programmed target
	if (driveTurnPIDLoop->OnTarget()) {
		pidFinished = true;
		printf("2135: TargetAngle: %3.2f   Actual: %3.2f\n", m_pidAngle, gyro->GetAngle());
	}

	// Check if safety timer has expired, set value to about 2x the cycle
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout)) {
		printf("2135: Safety Timer timed out %3.2f\n", m_safetyTimeout);
		pidFinished = true;
	}

	return pidFinished;
}

void Chassis::MoveDriveHeadingStop(void) {
	// Disable PID loop
	driveTurnPIDLoop->Disable();

	// Stop safety timer
	printf("2135: TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	// Do not shift back to high gear in case another auton command is running

	// Change to Brake mode
	MoveSetBrakeNotCoastMode(false);

	// Re-enable the motor safety helper (temporarily disabled)
    // TODO: Can we enable motor safety and have auton run
	robotDrive->SetSafetyEnabled(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//	Closed loop movement - Drive to a relative heading using PID loop in RoboRIO and vision angles

void Chassis::MoveDriveVisionHeadingDistanceInit(double angle)
{
	gyro->Reset();

	// Program the PID target setpoint
	driveVisionPIDLoop->SetSetpoint(angle);

	// Shift into low gear during movement for better accuracy
	MoveShiftGears(true);

	// Change to Brake mode
	MoveSetBrakeNotCoastMode(true);

	// Enable the PID loop
	driveVisionPIDLoop->SetAbsoluteTolerance(0.0);
	driveVisionPIDLoop->Enable();

	//Start safety timer
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
	m_safetyTimeout = 30.0;

	// Disable safety feature during movement, since motors will be fed by loop
	robotDrive->SetSafetyEnabled(false);
}

bool Chassis::MoveDriveVisionHeadingIsPIDAtSetPoint(void)
{
	bool pidFinished = false;

	// Test the PID to see if it is on the programmed target
	if (driveVisionPIDLoop->OnTarget()) {
		pidFinished = true;
	}

	// Check if safety timer has expired, set value to about 2x the cycle
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout)) {
		printf("2135: Safety Timer timed out %3.2f\n", m_safetyTimeout);
		pidFinished = true;
	}

	return pidFinished;
}

void Chassis::MoveDriveVisionHeadingStop(void)
{
	// Disable PID loop
	driveVisionPIDLoop->Disable();

	// Stop safety timer
	printf("2135: TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	// Do not shift back to high gear in case another auton command is running

	// Change to Brake mode
	MoveSetBrakeNotCoastMode(false);

	// Re-enable the motor safety helper (temporarily disabled)
    // TODO: Can we enable motor safety and have auton run
	robotDrive->SetSafetyEnabled(false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

DriveTurnPID::DriveTurnPID (std::shared_ptr<RobotDrive> robotDrive) {
	m_robotDrive = robotDrive;
}

void DriveTurnPID::PIDWrite(double output) {
	m_robotDrive->ArcadeDrive (0.0, output, false);

	// TODO: Remove this after tuning
	SmartDashboard::PutNumber(CHS_TURNPID_OUT_L, output);
	SmartDashboard::PutNumber(CHS_TURNPID_OUT_R, -output);
}

DriveVisionPID::DriveVisionPID (std::shared_ptr<RobotDrive> robotDrive) {
	m_robotDrive = robotDrive;

	m_visionAngle = SmartDashboard::GetNumber(CAM_TURNANGLE, CAM_TURNANGLE_D);
	printf("2135: CameraVisionAngle: %f degrees\n", m_visionAngle);
}

void DriveVisionPID::PIDWrite(double output) {

	if (Robot::oi->getDriverJoystick()->GetY() < 0.1) {
		output = 0.0;
	}

	m_robotDrive->ArcadeDrive (-(Robot::oi->getDriverJoystick()->GetY()), output, false);

	// TODO: Remove this after tuning
	SmartDashboard::PutNumber(CHS_TURNPID_OUT_L, output);
	SmartDashboard::PutNumber(CHS_TURNPID_OUT_R, -output);
}

double DriveVisionPIDSource::PIDGet(void) {
	double curAngle;

	// Get the current angle from the gyro
	curAngle = RobotMap::chassisGyro->GetAngle();

#if 0	// If averaging is needed leave this in
	int i;

	// Limit the gyro input to a valid range
	curAngle = fmin(curAngle, 25.0);
	curAngle = fmax(curAngle, -25.0);

	// Store in the gyro angle buffer
	m_angleBuffer[m_curSample++] = curAngle;
	if (m_curSample >= numSamples)
		m_curSample = 0;
	if (m_totSamples < m_totSamples)
		m_totSamples++;

	// Reuse curAngle to average the samples over total samples in buffer
	curAngle = 0.0;
	for (i = 0; i < m_totSamples; i++) {
		curAngle += m_angleBuffer[i];
	}
	curAngle = curAngle / m_totSamples;
#endif

	return curAngle;
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
