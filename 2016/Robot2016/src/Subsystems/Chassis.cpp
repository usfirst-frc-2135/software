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
    motorL2 = RobotMap::chassisMotorL2;
    leftEncoder = RobotMap::chassisLeftEncoder;
    leftPID = RobotMap::chassisLeftPID;
    motorR4 = RobotMap::chassisMotorR4;
    rightEncoder = RobotMap::chassisRightEncoder;
    rightPID = RobotMap::chassisRightPID;
    motorL3 = RobotMap::chassisMotorL3;
    motorR5 = RobotMap::chassisMotorR5;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL2->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    motorL3->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    motorR4->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    motorR5->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

    printf("2135: Creating New Robot Drive\n");
    robotDrive = new RobotDrive(motorL2, motorR4);
    printf("2135: Finish Creating New Robot Drive\n");

    robotDrive->SetSafetyEnabled(false);

    motorL3->SetControlMode(CANSpeedController::kFollower);
    motorL3->Set(2);
    motorR5->SetControlMode(CANSpeedController::kFollower);
    motorR5->Set(4);
    motorR4->SetClosedLoopOutputDirection(true);

    m_drivePidSpeedMin = -0.5;
    m_drivePidSpeedMax = 0.5;
    m_driveDistance = 0.0;
    m_orientationNormal = -1.0;
    m_driveDistanceTimed = 3.0;
    m_rotations = 0.0;
    m_speedControl = 1.0;
    m_scaled = 1.0;

    motorL2->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    motorL2->SetSensorDirection(true);

    motorR4->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
    motorR4->SetSensorDirection(false);

    motorL2->ConfigEncoderCodesPerRev(M_COUNTS_PER_ROTATION);
    motorR4->ConfigEncoderCodesPerRev(M_COUNTS_PER_ROTATION);

    motorL2->ConfigPeakOutputVoltage( +5, -5);
    motorL2->ConfigNominalOutputVoltage(+0, -0);

    motorR4->ConfigPeakOutputVoltage( +5, -5);
    motorR4->ConfigNominalOutputVoltage(+0, -0);
}

void Chassis::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    SetDefaultCommand(new DriveTeleop());
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Chassis::Initialize(Preferences *prefs)
{
	printf("2135: Chassis Initialize\n");

	//Initialize and read preferences file
	//ChassisMinRange
	m_drivePidSpeedMin = Robot::LoadPreferencesVariable("ChassisMinRange", -0.7);

	//ChassisMaxRange
	m_drivePidSpeedMax = Robot::LoadPreferencesVariable("ChassisMaxRange", 0.7);

	//ChassisDriveDistance
	m_driveDistance = Robot::LoadPreferencesVariable("ChassisDriveDistance", 0.0);

	//ChassisDriveTimed
	m_driveDistanceTimed = Robot::LoadPreferencesVariable("ChassisDriveTimed", 0.0);

	//ChassisDriveTimed
	SmartDashboard::PutNumber("ChassisDriveTimedSpeed", Robot::LoadPreferencesVariable("ChassisDriveTimedSpeed", 0.0));

	//ChassisVoltageRampRate
	SmartDashboard::PutNumber("ChassisVolageRampRate", Robot::LoadPreferencesVariable("ChassisVoltageRampRate", 8.0));

	//ChassisPeakOutputVoltage
	SmartDashboard::PutNumber("ChassisPeakOutputVoltage", Robot::LoadPreferencesVariable("ChassisPeakOutputVoltage", 5.0));

	//ChassisProportional
	SmartDashboard::PutNumber("ChassisProportional", Robot::LoadPreferencesVariable("ChassisProportional", 0.3));

	//ChassisAbsoluteValue
	SmartDashboard::PutNumber("ChassisAbsoluteValue", Robot::LoadPreferencesVariable("ChassisAbsoluteValue", 0.2));

	//SpeedControl
	m_speedControl = Robot::LoadPreferencesVariable("SpeedControl", 1.0);
	SmartDashboard::PutNumber("SpeedControl", m_speedControl);

	SmartDashboard::PutNumber("Left Encoder Position", (motorL2->GetEncPosition() * -1));

	SmartDashboard::PutNumber("Right Encoder Position", motorR4->GetEncPosition());

	SmartDashboard::PutNumber("Drive Distance", 60.0);
}

void Chassis::MoveWithJoystick(std::shared_ptr<Joystick> joystick)
{
	double yValue;
	double xValue;
//	double speedControl;

	xValue = joystick->GetX();
	yValue = joystick->GetY() * m_orientationNormal;

//	speedControl = SmartDashboard::GetNumber("Speed Control", 1.0);
	if (m_scaled) {
		yValue = yValue * m_speedControl;
		xValue = xValue * m_speedControl;
	}

	robotDrive->ArcadeDrive( yValue, xValue * (-1), true );

	SmartDashboard::PutNumber("Left Encoder Position", (motorL2->GetEncPosition() * -1));
	SmartDashboard::PutNumber("Right Encoder Position", motorR4->GetEncPosition());
	//robotDrive->ArcadeDrive( joystick->GetY() , joystick->GetX(), true );
}

void Chassis::MoveUsingLeftRightMotorOutputs(double left, double right)
{
	robotDrive->SetLeftRightMotorOutputs( left, right );
}

void Chassis::MoveStop(void)
{
	robotDrive->SetLeftRightMotorOutputs( 0.0, 0.0 );
}

void Chassis::MoveLowShift(bool scaled)
{
	m_scaled = scaled;
}

void Chassis::ReverseDriveTrain(void)
{
	m_orientationNormal = -m_orientationNormal;
	SmartDashboard::PutNumber("Drive Invert", m_orientationNormal);
}

void Chassis::MoveDistanceWithPIDInit( double distance )
{
	double voltageRampRate = SmartDashboard::GetNumber("ChassisVoltageRampRate", 8.0);
	double peakOutputVoltage = SmartDashboard::GetNumber("ChassisPeakOutputVoltage", 5.0);
	double proportional = SmartDashboard::GetNumber("ChassisProportional", 0.3);
	double abstolerance = SmartDashboard::GetNumber("ChassisAbsoluteValue", 0.2);

	motorL2->ConfigPeakOutputVoltage(peakOutputVoltage, peakOutputVoltage*(-1));
	motorR4->ConfigPeakOutputVoltage(peakOutputVoltage, peakOutputVoltage*(-1));

//	double leftDistance;
//	double rightDistance;

	double rotations;
	rotations = distance / (M_WHEEL_DIA * M_PI);

//	motorR4->SetInverted(false);

//	leftPID->SetPID( 1.0, 0.0, 0.0 );
//	leftPID->SetOutputRange( m_drivePidSpeedMin, m_drivePidSpeedMax );
//	leftPID->SetAbsoluteTolerance( abstolerance );
//	leftEncoder->SetDistancePerPulse( 4 * M_PI / 360 );
//
//	rightPID->SetPID( 1.0, 0.0, 0.0 );
//	rightPID->SetOutputRange( m_drivePidSpeedMin, m_drivePidSpeedMax );
//	rightPID->SetAbsoluteTolerance( abstolerance );
//	rightEncoder->SetDistancePerPulse( 4 * M_PI / 360 );
//
//	// get current encoder values
//	leftDistance = leftEncoder->GetDistance();
//	rightDistance = rightEncoder->GetDistance();
//	printf("2135: Encoder Distance %f %f\n", leftDistance, rightDistance);
//
//	//add distance to current encoder values
//	leftDistance += distance;
//	rightDistance += distance;
//	printf("2135: Encoder Distance %f %f\n", leftDistance, rightDistance);
//
//	//set SetPoint with calculated target distance
//	leftPID->SetSetpoint(leftDistance);
//	rightPID->SetSetpoint(rightDistance);
//	robotDrive->SetSafetyEnabled(false);
//
//	//enable PID loops
//	leftPID->Enable();
//	rightPID->Enable();
//	printf("2135: Left and Right PIDs are enabled\n");

	motorL2->SetAllowableClosedLoopErr(abstolerance);
	motorR4->SetAllowableClosedLoopErr(abstolerance);

	motorL2->SetPID( proportional, 0.0, 0.0 );
	motorR4->SetPID( proportional, 0.0, 0.0 );

	motorL2->SetVoltageRampRate(voltageRampRate);
	motorL2->SetControlMode(CANSpeedController::ControlMode::kPosition);

	motorR4->SetVoltageRampRate(voltageRampRate);
	motorR4->SetControlMode(CANSpeedController::ControlMode::kPosition);

	motorL2->SetEncPosition(0);
	motorR4->SetEncPosition(0);

	motorL2->Set(rotations);
	motorR4->Set(rotations);

	m_rotations = rotations;
}

void Chassis::MoveDistanceWithPIDExecute( void )
{

	if (m_rotations == motorL2->GetEncPosition()) {
//		motorL2->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
		printf("2135: Left PID is Disabled\n");
		motorL2->Set(0.0);
	}

	if (m_rotations == motorR4->GetEncPosition()) {
//		motorR4->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
		printf("2135: Right PID is Disabled\n");
		motorR4->Set(0.0);
	}

	SmartDashboard::PutNumber("Left Encoder Position", (motorL2->GetEncPosition() * -1));
	SmartDashboard::PutNumber("Right Encoder Position", motorR4->GetEncPosition());

//	if (leftPID->OnTarget())
//	{
//		leftPID->Disable();
//		printf("2135: Left PID is Disabled\n");
//	}
//	if (rightPID->OnTarget())
//	{
//		rightPID->Disable();
//		printf("2135: Right PID is Disabled\n");
//	}
//	if (!leftPID->IsEnabled())
//	{
//		motorL2->Set(0, 0);
//	}
//	if (!rightPID->IsEnabled())
//	{
//		motorR4->Set(0, 0);
//	}
//
	static int counter = 0;
	if (counter++ % 50 == 0)
	{
		//printf("2135: LeftPID  %d %d\n", RobotMap::chassisLeftEncoder->Get(), leftPID->IsEnabled());
		//printf("2135: RightPID %d %d\n", RobotMap::chassisRightEncoder->Get(), rightPID->IsEnabled());
		printf("2135: LeftPID  %d\n", motorL2->GetEncPosition());
		printf("2135: RightPID %d\n", motorR4->GetEncPosition());
	}
}

bool Chassis::MoveDistanceWithPIDIsAtSetpoint(void)
{
	bool bothOnTarget;
	// are both PIDs on target
	bothOnTarget = false;
//	if (!leftPID->IsEnabled() && !rightPID->IsEnabled())
//	{
//		MoveDistanceWithPIDStop();
//		bothOnTarget = true;
//	}

	if (m_rotations == motorL2->GetEncPosition() && m_rotations == motorR4->GetEncPosition()) {
		MoveDistanceWithPIDStop();
		bothOnTarget = true;
	}

	return bothOnTarget;
}

void Chassis::MoveDistanceWithPIDStop( void )
{
//	leftPID->Disable();
//	rightPID->Disable();

	motorL2->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	motorR4->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	robotDrive->SetSafetyEnabled(true);

	//motorR4->SetInverted(true);
}
