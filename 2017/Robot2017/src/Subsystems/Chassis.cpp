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

    printf("2135: Chassis Constructor\n");

    // TODO: Safety cannot remain disabled
    robotDrive->SetSafetyEnabled(false);
    turnOutput = new TurnOutput(robotDrive);
    turnControl = new PIDController(0.1, 0.0, 0.0, gyro.get(), turnOutput);

    //	Set all drive motors to use coast mode and not brake when stopped
    motorL1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
    motorL2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
    motorR3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
    motorR4->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);

    // Make second Talon SRX controller on each side of drivetrain follow the main Talon SRX
    motorL2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    motorL2->Set(1);
    motorR4->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    motorR4->Set(3);

    // Invert the direction of the right hand side motors
	motorR3->SetClosedLoopOutputDirection(true);
	motorL1->SetClosedLoopOutputDirection(false);

	motorL1->SetFeedbackDevice(CANTalon::QuadEncoder);
	motorL1->SetSensorDirection(true);

	motorR3->SetFeedbackDevice(CANTalon::QuadEncoder);
	motorR3->SetSensorDirection(false);

	motorL1->ConfigEncoderCodesPerRev(USDigitalS4_360);
	motorR3->ConfigEncoderCodesPerRev(USDigitalS4_360);

    //	TODO: Set voltage ramp rate to control how fast motors spin up
    //MoveSetVoltageRamp(0.0);

	//	Initialize drivetrain direction for driving
    m_driveDirection = 1.0;

	//	Initialize drive scaling factor and disable it
    m_scaled = false;
    m_driveScalingFactor = 1.0;

    //	Initialize power setting used for spin turns
    m_driveSpinSetting = 0.45;

    //	Initalize the brake mode to be disabled
    m_brakeMode = false;

    //	TODO: These may not be used
    m_absTolerance = 0.2;
    m_rotations = 0.0;

    // Initialize lowGear to false
    m_lowGear = false;

    //Initialize safetyInches to zero
    m_safetyInches = 0.0;
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

void Chassis::Initialize(frc::Preferences *prefs)
{
	// TODO: Initialize SmartDashboard values - if any

	printf("2135: Chassis Initialize\n");

	// Drive invert direction the stick moves the robot
	SmartDashboard::PutNumber("DriveInvert", m_driveDirection);

	// Scale maximum driving speed - beginner mode
	m_driveScalingFactor = Robot::LoadPreferencesVariable("ChassDriveScaling", 0.85);
	SmartDashboard::PutNumber("DriveScaling", m_driveScalingFactor);

	// Speed to apply to the motors for spin turns
	m_driveSpinSetting = Robot::LoadPreferencesVariable("ChassDriveSpin", 0.4);
	SmartDashboard::PutNumber("DriveSpin", m_driveSpinSetting);

	// Brake/coast mode for talon speed controller
	SmartDashboard::PutNumber("DriveBrakeMode", m_brakeMode);

	// VoltageRampRate
	SmartDashboard::PutNumber("DrivePIDVoltRampRate", Robot::LoadPreferencesVariable("ChassPIDVoltRampRate", 8.0));

	// absTolerance
	m_absTolerance = Robot::LoadPreferencesVariable("ChassPIDAbsTolerance", 0.2);
	SmartDashboard::PutNumber("DrivePIDAbsTolerance", m_absTolerance);

	// peakOutput
	SmartDashboard::PutNumber("DrivePIDPeakOutVolts", Robot::LoadPreferencesVariable("ChassPIDPeakOutVolts", 5.0));

	// proportional
	SmartDashboard::PutNumber("DrivePIDProportional", Robot::LoadPreferencesVariable("ChassPIDProportional", 0.3));

	// left right encoder values
	std::pair<double, double> DriveEncoderPosition = ReadEncoder();
	SmartDashboard::PutNumber("LeftEncoderPosition", DriveEncoderPosition.first);
	SmartDashboard::PutNumber("RightEncoderPosition", DriveEncoderPosition.second);

	// drive distance inches
	SmartDashboard::PutNumber("DriveDistance", 120);

	// reset encoders to zero
	ResetEncoder();
	ResetGyro();
}

void Chassis::UpdateSmartDashboardValues(void)
{
	// TODO: Verify for correct values
	std::pair<double, double> DriveEncoderPosition = ReadEncoder();
	SmartDashboard::PutNumber("LeftEncoderPosition", DriveEncoderPosition.first);
	SmartDashboard::PutNumber("RightEncoderPosition", DriveEncoderPosition.second);
	SmartDashboard::PutNumber("DriveGyroPosition", ReadGyro());
	SmartDashboard::PutNumber("LeftRotations", motorL1->Get());
	SmartDashboard::PutNumber("RightRotations", motorR3->Get());
	SmartDashboard::PutNumber("LeftClosedLoopError", motorL1->GetClosedLoopError());
	SmartDashboard::PutNumber("RightClosedLoopError", motorR3->GetClosedLoopError());

	SmartDashboard::PutNumber("Gyro Value", Robot::chassis->ReadGyro());
}

void Chassis::MoveWithJoystick(std::shared_ptr<Joystick> joystick)
{
	double xValue;
	double yValue;

	xValue = joystick->GetX();
	yValue = joystick->GetY() * m_driveDirection;

	//	TODO: DONE - Scaling should only work when in high gear--not low gear
	if (m_scaled && !m_lowGear) {
		xValue = xValue * m_driveScalingFactor;
		yValue = yValue * m_driveScalingFactor;
	}

	robotDrive->ArcadeDrive( xValue, yValue, true );
	UpdateSmartDashboardValues();
}

void Chassis::MoveSpin(bool spinLeft)
{
	if (spinLeft)
		robotDrive->SetLeftRightMotorOutputs( -m_driveSpinSetting, m_driveSpinSetting );
	else
		robotDrive->SetLeftRightMotorOutputs( m_driveSpinSetting, -m_driveSpinSetting );
}

//	Set drive direction to be opposite relative to robot

void Chassis::MoveInvertDriveDirection(void)
{
	m_driveDirection = -m_driveDirection;
	SmartDashboard::PutNumber("DriveInvert", m_driveDirection);
}

//	Set scaling factor on drive speed

void Chassis::MoveScaleMaxSpeed(bool scaled)
{
	m_scaled = scaled;
	SmartDashboard::PutBoolean("DriveScaling", m_scaled);
}

//	Set voltage ramp rate to control motor spin up during auton

void Chassis::MoveSetVoltageRamp(double voltageRampRate)
{
	// TODO: DONE - L2 and R4 should always follow L1 and R3 -- this is wrong'
	//	This function could probably be inline, since it is only two calls
	motorL1->SetVoltageRampRate(voltageRampRate);
	motorR3->SetVoltageRampRate(voltageRampRate);
}

void Chassis::MoveToggleBrakeMode(void)
{
	m_brakeMode = !m_brakeMode;

	if (m_brakeMode == false) {
		motorL1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		motorL2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		motorR3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
		motorR4->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	}
	else {
		motorL1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		motorL2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		motorR3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
		motorR4->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	}

	SmartDashboard::PutBoolean("DriveBrakeMode", m_brakeMode);
}

void Chassis::MoveUsingMotorOutputs(double motorInputLeft, double motorInputRight)
{
	robotDrive->SetLeftRightMotorOutputs(motorInputLeft, motorInputRight);

	ReadEncoder();
}

void Chassis::MoveDriveDistancePIDInit(double inches)
{
	double voltageRampRate;
	double peakOutputVoltage;
	double proportional;

	m_rotations = inches / (M_WHEEL_DIA * M_PI);
	printf("2135: Encoder Distance %f rotations, %f inches\n", m_rotations, inches);

	// TODO: Experiment to get default values
	voltageRampRate = SmartDashboard::GetNumber("DrivePIDVoltRampRate", 8.0);
	peakOutputVoltage = SmartDashboard::GetNumber("DrivePIDPeakOutVolts", 5.0);
	proportional = SmartDashboard::GetNumber("DrivePIDProportional", 0.3);
	m_absTolerance = SmartDashboard::GetNumber("DrivePIDAbsTolerance", 0.2);

	// Disable safety feature during movement, since motors will be fed by loop
	robotDrive->SetSafetyEnabled(false);

	// Shift into low gear during movement for better accuracy
	MoveShiftGears(true);

	// Change the drive motors to be position-loop control modes
	motorL1->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);
	motorR3->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);

	// Change to brake mode
	motorL1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	motorL2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	motorR3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);
	motorR4->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Brake);

	// TODO: Temporarily adjust voltage ramp rate for this year's robot
	MoveSetVoltageRamp(voltageRampRate);

	// TODO: Adjust peak output voltage for this year's robot
	motorL1->ConfigPeakOutputVoltage(peakOutputVoltage, -peakOutputVoltage);
	motorR3->ConfigPeakOutputVoltage(peakOutputVoltage, -peakOutputVoltage);

	// This should be set one time in constructor
	motorL1->SetPID(proportional, 0.0, 0.0);
	motorR3->SetPID(proportional, 0.0, 0.0);

	// TODO: Determine if tolerance is really necessary - can be set in constructor if at all
	motorL1->SetAllowableClosedLoopErr(m_absTolerance);
	motorR3->SetAllowableClosedLoopErr(m_absTolerance);

	// Initialize the encoders to start movement at reference of zero counts
	motorL1->SetEncPosition(0);
	motorR3->SetEncPosition(0);

	// Set the target distance in terms of wheel rotations
	motorL1->Set(m_rotations);
	motorR3->Set(m_rotations);

	// TODO: DONE - Set a safety timer in case encoders do not give feedback correctly

	// Enable the PID loop to start the movement
	motorL1->Enable();
	motorR3->Enable();

	//Start safety timer
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
}

void Chassis::MoveDriveDistancePIDExecute(void)
{
	//Verify that robot has reached target within absolute tolerance margins
	if (abs((motorL1->GetEncPosition()/1440) - m_rotations) <= m_absTolerance) {
		printf("2135: Left PID disabled\n");
	}

	if (abs((motorR3->GetEncPosition()/1440) - m_rotations) <= m_absTolerance) {
		printf("2135: Right PID disabled\n");
	}

	UpdateSmartDashboardValues();

}

bool Chassis::MoveDriveDistancePIDAtSetpoint(void)
{
	// Verify that both encoders are on target
	bool bothOnTarget = false;

	// TODO: DONE - If CPR is set to be 360 instead of 120, then this calculation would probably make
	//	this math be 3*480.2 ~= 1440 which is the native units of the Talon quadrature encoder
	if ((abs((motorL1->GetEncPosition()/1440.0) - m_rotations) <= m_absTolerance) &&
			(abs((motorR3->GetEncPosition()/1440.0) - m_rotations) <= m_absTolerance)) {
//		MoveDriveDistancePIDStop();
		bothOnTarget = true;
	}

	if(m_safetyTimer.HasPeriodPassed((m_safetyInches/78)+1)) {
		bothOnTarget = true;
	}

	return bothOnTarget;


}

void Chassis::MoveDriveDistancePIDStop(void)
{
	// TODO: DONE - Disable the PID loop

	// TODO: DONE - Why are these needed?
	motorL1->Disable();
	motorR3->Disable();

	// TODO: Voltage Ramp and Max Output may need to be put back to Teleop setting

	// Change back to gear setting default
	MoveShiftGears(false);

	// Change from PID position-loop back to PercentVbus
	motorL1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	motorR3->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);

	// Change to coast mode
	motorL1->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	motorL2->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	motorR3->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	motorR4->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);

	robotDrive->SetSafetyEnabled(true);
}


void Chassis::MoveDriveHeadingDistance(double inches, double angle)
{
	// Program the PID target setpoint
	turnControl->SetSetpoint(angle);
	printf("===> MoveDriveHeadingDistance() using angle: %f\n",angle);
	// Enable the PID loop
	turnControl->Enable();
}

bool Chassis::MoveDriveHeadingAtSetPoint(void) {
	// Test the PID to see if it is on the programmed target
	return turnControl->OnTarget();
}

void Chassis::MoveDriveHeadingStop(void) {
	// TODO: DONE - This should be turnControl->Disable() to stop the PID -- not individual motors
	turnControl->Disable();
}

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

void Chassis::ResetEncoder(void)
{
	motorL1->SetEncPosition(0);
	motorR3->SetEncPosition(0);
}

std::pair<double, double> Chassis::ReadEncoder(void)
{
	double leftEncoderValue;
	double rightEncoderValue;

	leftEncoderValue = (double)(motorL1->GetEncPosition());
	rightEncoderValue = (double)(motorR3->GetEncPosition());

	return std::make_pair(leftEncoderValue, rightEncoderValue);
}

void Chassis::ResetGyro(void)
{
	gyro->Reset();
}

double Chassis::ReadGyro(void)
{
	return gyro->GetAngle();
}
