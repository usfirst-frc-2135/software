// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CANTalon.h"


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
    gyro = RobotMap::chassisGyro;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    robotDrive->SetSafetyEnabled(false);
    turnOutput = new TurnOutput(robotDrive);
    turnControl = new PIDController(0.1, 0.0, 0.0, gyro.get(), turnOutput);
    printf("2135: Chassis Constructor\n");

    //	Set all drive motors to use coast mode and not brake when stopped
    motorL1->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    motorL2->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    motorR3->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    motorR4->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

    // Make second Talon SRX controller on each side of drivetrain follow the main Talon SRX
    motorL2->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    motorL2->Set(1);
    motorR4->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
    motorR4->Set(3);

	motorR3->SetClosedLoopOutputDirection(true);

	motorL1->SetFeedbackDevice(CANTalon::QuadEncoder);
	motorL1->SetSensorDirection(true);

	motorR3->SetFeedbackDevice(CANTalon::QuadEncoder);
	motorR3->SetSensorDirection(false);

	motorL1->ConfigEncoderCodesPerRev(M_COUNTS_PER_ROTATION);
	motorR3->ConfigEncoderCodesPerRev(M_COUNTS_PER_ROTATION);

    //	TODO: Set voltage ramp rate to control how fast motors spin up
    //MoveSetVoltageRamp(0.0);

    //	Calibrate the gyro for later use
    gyro->Calibrate();

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
}

void Chassis::UpdateSmartDashboardValues(void)
{
	// TODO: Verify for correct values
	std::pair<double, double> DriveEncoderPosition = ReadEncoder();
	SmartDashboard::PutNumber("LeftEncoderPosition", DriveEncoderPosition.first);
	SmartDashboard::PutNumber("RightEncoderPosition", DriveEncoderPosition.second);
	SmartDashboard::PutNumber("DriveGyroPosition", ReadGyro());
}

void Chassis::MoveToggleBrakeMode(void)
{
	m_brakeMode = !m_brakeMode;

	if (m_brakeMode == false) {
		motorL1->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
		motorL2->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
		motorR3->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
		motorR4->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
	}
	else {
		motorL1->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
		motorL2->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
		motorR3->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
		motorR4->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
	}

	SmartDashboard::PutBoolean("DriveBrakeMode", m_brakeMode);
}

void Chassis::MoveUsingMotorOutputs(double motorInputLeft, double motorInputRight)
{
	robotDrive->SetLeftRightMotorOutputs(motorInputLeft, motorInputRight);

	// TODO: Update the encoders
}

void Chassis::MoveDriveDistancePIDInit(double inches)
{
	double voltageRampRate;
	double peakOutputVoltage;
	double proportional;

	m_rotations = inches / (M_WHEEL_DIA * M_PI);
	printf("2135: Encoder Distance %f rotations\n", m_rotations);

	// TODO: Experiment to get default values
	voltageRampRate = SmartDashboard::GetNumber("DrivePIDVoltRampRate", 8.0);
	peakOutputVoltage = SmartDashboard::GetNumber("DrivePIDPeakOutVolts", 5.0);
	proportional = SmartDashboard::GetNumber("DrivePIDProportional", 0.3);
	m_absTolerance = SmartDashboard::GetNumber("DrivePIDAbsTolerance", 0.2);

	robotDrive->SetSafetyEnabled(false);

	MoveShiftGears(true);

	motorL1->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);
	motorR3->SetTalonControlMode(CANTalon::TalonControlMode::kPositionMode);

	MoveSetVoltageRamp(voltageRampRate);

	motorL1->ConfigPeakOutputVoltage(peakOutputVoltage, peakOutputVoltage*(-1));
	motorR3->ConfigPeakOutputVoltage(peakOutputVoltage, peakOutputVoltage*(-1));

	motorL1->SetPID(proportional, 0.0, 0.0);
	motorR3->SetPID(proportional, 0.0, 0.0);

	motorL1->SetAllowableClosedLoopErr(m_absTolerance);
	motorR3->SetAllowableClosedLoopErr(m_absTolerance);

	motorL1->SetEncPosition(0);
	motorR3->SetEncPosition(0);

	motorL1->Set(m_rotations);
	motorR3->Set(m_rotations);

	motorL1->Enable();
	motorR3->Enable();
}

void Chassis::MoveDriveDistancePIDExecute(void)
{
	//Verify that robot has reached target within absolute tolerance margins
	if (abs(motorL1->GetEncPosition() - m_rotations) <= m_absTolerance) {
		printf("2135: Left PID disabled\n");
		motorL1->Set(0.0); // Stop motor
	}
	motorR3->IsEnabled();
	if (abs(motorR3->GetEncPosition() - m_rotations) <= m_absTolerance) {
		printf("2135: Right PID disabled\n");
		motorR3->Set(0.0); // Stop motor
	}

	UpdateSmartDashboardValues();
}

bool Chassis::MoveDriveDistancePIDAtSetpoint(void)
{
	// Verify that both encoders are on target
	bool bothOnTarget = false;

	if((abs(motorL1->GetEncPosition() - m_rotations) <= m_absTolerance) &&
			(abs(motorR3->GetEncPosition() - m_rotations) <= m_absTolerance)) {
		MoveDriveDistancePIDStop();
		bothOnTarget = true;
	}

	return bothOnTarget;

}
void Chassis::MoveDriveDistancePIDStop(void)
{
	// Change from PID to PercentVbus
	motorL1->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);
	motorR3->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);

	MoveShiftGears(false);

	robotDrive->SetSafetyEnabled(true);
}


void Chassis::MoveDriveHeadingDistance(double inches, double angle)
{
	turnControl->SetSetpoint(angle);
	turnControl->Enable();
}

bool Chassis::MoveDriveHeadingAtSetPoint() {
	return turnControl->OnTarget();
}

void Chassis::MoveShiftGears(bool lowGear)
{
	if (lowGear) {
		shifter->Set(shifter->kForward);
	}
	else {
		shifter->Set(shifter->kReverse);
	}
}

void Chassis::MoveWithJoystick(std::shared_ptr<Joystick> joystick)
{
	double xValue;
	double yValue;

	xValue = joystick->GetX() * -1;
	yValue = joystick->GetY() * m_driveDirection;

	//	TODO: Scaling should only work when in high gear--not low gear
	if (m_scaled) {
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
	motorL1->SetVoltageRampRate(voltageRampRate);
	motorL2->SetVoltageRampRate(voltageRampRate);
	motorR3->SetVoltageRampRate(voltageRampRate);
	motorR4->SetVoltageRampRate(voltageRampRate);
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
