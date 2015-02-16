// RobotBuilder Version: 1.5
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
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/DriveTeleop.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
Chassis::Chassis() : Subsystem("Chassis") {
	printf("2135: Chassis init\n");
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	encoderL = RobotMap::chassisEncoderL;
	motorL2 = RobotMap::chassisMotorL2;
	leftPID = RobotMap::chassisLeftPID;
	motorL3 = RobotMap::chassisMotorL3;
	encoderR = RobotMap::chassisEncoderR;
	motorR4 = RobotMap::chassisMotorR4;
	rightPID = RobotMap::chassisRightPID;
	motorR5 = RobotMap::chassisMotorR5;
	ultrasonicDrive = RobotMap::chassisUltrasonicDrive;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	robotDrive = new RobotDrive(motorL2,motorR4);
	m_orientationNormal = true;
	SmartDashboard::PutNumber("Drive Invert", m_orientationNormal);
	motorL3->SetControlMode(CANSpeedController::kFollower);
	motorL3->Set(2);
	motorR5->SetControlMode(CANSpeedController::kFollower);
	motorR5->Set(4);
}
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new DriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
//	Autonomous Drive to a specific distance - PID initialization
//
void Chassis::DriveDistanceWithPIDInit( double distance )
{
	double leftDistance;
	double rightDistance;
	double minlimit=Preferences::GetInstance()->GetDouble("Min Limit", -0.6);
	double maxlimit=Preferences::GetInstance()->GetDouble("Max Limit", 0.6);
	double abstolerance=Preferences::GetInstance()->GetDouble("Abs Tolerance", 0.2);

	leftPID->SetPID(SmartDashboard::GetNumber("L: P"),SmartDashboard::GetNumber("L: I"),
			SmartDashboard::GetNumber("L: D"));
	leftPID->SetOutputRange(minlimit, maxlimit);
	leftPID->SetAbsoluteTolerance(abstolerance);
	encoderL->SetDistancePerPulse(4 * M_PI / 360);
	rightPID->SetPID(SmartDashboard::GetNumber("R: P"),SmartDashboard::GetNumber("R: I"),
			SmartDashboard::GetNumber("R: D"));
	rightPID->SetOutputRange(minlimit, maxlimit);
	rightPID->SetAbsoluteTolerance(abstolerance);
	encoderR->SetDistancePerPulse(4 * M_PI / 360);
	// get current encoder values
	leftDistance = encoderL->GetDistance();
	rightDistance = encoderR->GetDistance();
	// add distance to current encoder values
	leftDistance += distance;
	rightDistance -= distance;
	SmartDashboard::PutNumber("Left Setpoint", leftDistance);
	SmartDashboard::PutNumber("Right Setpoint", -rightDistance);
	// set SetPoint with calculated target distance
	leftPID->SetSetpoint(leftDistance);
	rightPID->SetSetpoint(rightDistance);
	robotDrive->SetSafetyEnabled(false);
	// enable PID loops
	leftPID->Enable();
	rightPID->Enable();
	SmartDashboard::PutBoolean("Left PID State", false);
	SmartDashboard::PutBoolean("Right PID State", false);
}
//
//	Autonomous Drive to a specific distance - called from command execute
//
void Chassis::DriveDistanceWithPIDExecute( void )
{
	if (leftPID->OnTarget()) {
		SmartDashboard::PutBoolean("Left PID State", true);
		leftPID->Disable();
	}
	if (rightPID->OnTarget()) {
		SmartDashboard::PutBoolean("Right PID State", true);
		rightPID->Disable();
	}
	if (!leftPID->IsEnabled())
		motorL2->Set(0, 0);
	if (!rightPID->IsEnabled())
		motorR4->Set(0, 0);
}
//
//	Autonomous Drive to a specific distance - detect when at setpoint
//
bool Chassis::DriveDistanceWithPIDIsAtSetpoint( void )
{
	bool bothOnTarget;
	// are both PIDs on target
	bothOnTarget = false;
	if (!leftPID->IsEnabled() && !rightPID->IsEnabled()) {
		DriveDistanceWithPIDStop();
		bothOnTarget = true;
	}
	return bothOnTarget;
}
//
//	Autonomous Drive to a specific distance - stop the PID loop
//
void Chassis::DriveDistanceWithPIDStop( void )
{
	SmartDashboard::PutBoolean("Left PID State", true);
	SmartDashboard::PutBoolean("Right PID State", true);
	leftPID->Disable();
	rightPID->Disable();
	robotDrive->SetSafetyEnabled(true);
}

void Chassis::DriveWithJoystick( Joystick *joystick1 )
{
	robotDrive->ArcadeDrive( joystick1->GetY() * m_orientationNormal, joystick1->GetX(), true );
}

void Chassis::DriveUsingLeftRightMotorOutputs( double left, double right )
{
	robotDrive->SetLeftRightMotorOutputs(left, right);
}

void Chassis::ReverseDriveTrain( void )
{
	m_orientationNormal = -m_orientationNormal;
	SmartDashboard::PutNumber("Drive Invert", m_orientationNormal);
}

double Chassis::GetLeftSpeed( void )
{
	double static leftDistanceOld;
	double leftDistanceNew;
	double static timeOld;
	double timeNew;
	double leftSpeed;
	leftDistanceNew = encoderL->GetDistance();
	timeNew = m_speedTimer->Get();
	leftSpeed = (leftDistanceNew - leftDistanceOld) / (timeNew - timeOld);
	leftDistanceOld = leftDistanceNew;
	timeOld = timeNew;
	return ((leftSpeed) / 12);
}

double Chassis::GetRightSpeed( void )
{
	double static rightDistanceOld;
	double rightDistanceNew;
	double static timeOld;
	double timeNew;
	double rightSpeed;
	rightDistanceNew = encoderR->GetDistance();
	timeNew = m_speedTimer->Get();
	rightSpeed = ((rightDistanceNew - rightDistanceOld) / (timeNew - timeOld)) * -1;
	rightDistanceOld = rightDistanceNew;
	timeOld = timeNew;
	return ((rightSpeed) / 12);
}

double Chassis::GetLeftSpeedAverage( void )
{
	static double oldValues[4];
	oldValues[3] = oldValues[2];
	oldValues[2] = oldValues[1];
	oldValues[1] = oldValues[0];
	oldValues[0] = Robot::chassis->GetLeftSpeed();
	return (oldValues[3] + oldValues[2] + oldValues[1] + oldValues[0]) / 4;
}

double Chassis::GetRightSpeedAverage( void )
{
	static double oldValues[4];
	oldValues[3] = oldValues[2];
	oldValues[2] = oldValues[1];
	oldValues[1] = oldValues[0];
	oldValues[0] = Robot::chassis->GetRightSpeed();
	return (oldValues[3] + oldValues[2] + oldValues[1] + oldValues[0]) / 4;
}