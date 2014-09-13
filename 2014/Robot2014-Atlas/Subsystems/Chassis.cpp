// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveTeleop.h"
Chassis::Chassis() : Subsystem("Chassis") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	ultrasonicDrive = RobotMap::chassisUltrasonicDrive;
	leftDriveMotor = RobotMap::chassisLeftDriveMotor;
	leftDriveEncoder = RobotMap::chassisLeftDriveEncoder;
	leftDrivePID = RobotMap::chassisLeftDrivePID;
	rightDriveMotor = RobotMap::chassisRightDriveMotor;
	rightDriveEncoder = RobotMap::chassisRightDriveEncoder;
	rightDrivePID = RobotMap::chassisRightDrivePID;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	printf( "2135: Chassis Constructor\n" );
	drvTrain = RobotMap::driveTrain;
	m_orientationNormal = 1.0;
	drvTrain->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
	drvTrain->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
	drvTrain->SetExpiration( 2.0 );
	m_speedTimer = new Timer;
	m_speedTimer->Start();
	ultrasonicDrive->SetAutomaticMode(true);
	ultrasonicDrive->SetEnabled(true);
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
//	Normal Teleop Drive using Joysticks in Arcade mode
//
void Chassis::DriveWithJoystick( Joystick *driverJoystick )
{
#if 0
	drvTrain->ArcadeDrive( driverJoystick, true );
#else
	drvTrain->ArcadeDrive( driverJoystick->GetY() * m_orientationNormal, driverJoystick->GetX(), true );
#endif
}
//
//	Controlled drive used during spin turns
//
void Chassis::DriveUsingLeftRightMotorOutputs( double left, double right )
{
	// printf ( "2135: SetLeftRightMotorOutputs left - %6.3f, right - %6.3f\n", left, right );
	drvTrain->SetLeftRightMotorOutputs( left, right );
}
//
//	Reverse drive train for driving backwards
//
void Chassis::ReverseDriveTrain( void ) 
{
	m_orientationNormal = -m_orientationNormal;
	SmartDashboard::PutNumber( "Drive Invert", m_orientationNormal );
}
//
//	Autonomous Drive to a specific distance - PID initialization
//
void Chassis::DriveDistanceWithPIDInit( double distance ) 
{
	double leftDistance;
	double rightDistance;
	leftDrivePID->SetPID(SmartDashboard::GetNumber("L: P"),SmartDashboard::GetNumber("L: I"),
					SmartDashboard::GetNumber("L: D"));
	leftDrivePID->SetOutputRange(-0.6,0.6);
	leftDrivePID->SetAbsoluteTolerance(0.2);
	leftDriveEncoder->SetDistancePerPulse(4 * M_PI / 360);
	rightDrivePID->SetPID(SmartDashboard::GetNumber("R: P"),SmartDashboard::GetNumber("R: I"),
					SmartDashboard::GetNumber("R: D"));
	rightDrivePID->SetOutputRange(-0.6,0.6);
	rightDrivePID->SetAbsoluteTolerance(0.2);
	rightDriveEncoder->SetDistancePerPulse(4 * M_PI / 360);
	// get current encoder values
	leftDistance = leftDriveEncoder->GetDistance();
	rightDistance = rightDriveEncoder->GetDistance();
	// add distance to current encoder values
	leftDistance += distance;
	rightDistance -= distance;
	SmartDashboard::PutNumber( "Left Setpoint", leftDistance );
	SmartDashboard::PutNumber( "Right Setpoint", -rightDistance );
	// set SetPoint with calculated target distance
	leftDrivePID->SetSetpoint( leftDistance );
	rightDrivePID->SetSetpoint( rightDistance );
	drvTrain->SetSafetyEnabled(false);
	// enable PID loops
	leftDrivePID->Enable();
	rightDrivePID->Enable();
	SmartDashboard::PutBoolean("Left PID State", false );
	SmartDashboard::PutBoolean("Right PID State", false );
}
//
//	Autonomous Drive to a specific distance - called from command execute
//
void Chassis::DriveDistanceWithPIDExecute( void ) 
{
	if (leftDrivePID->OnTarget()) {
		SmartDashboard::PutBoolean("Left PID State", true );
		leftDrivePID->Disable();
	}
	if (rightDrivePID->OnTarget()) {
		SmartDashboard::PutBoolean("Right PID State", true);
		rightDrivePID->Disable();
	}
	
	if (!leftDrivePID->IsEnabled()) 
		leftDriveMotor->Set(0, 0);
	if (!rightDrivePID->IsEnabled()) 
		rightDriveMotor->Set(0, 0);
}
//
//	Autonomous Drive to a specific distance - detect when at setpoint
//
bool Chassis::DriveDistanceWithPIDIsAtSetpoint( void )
{
	bool bothOnTarget;
	// are both PIDs on target
	bothOnTarget = false;
	if (!leftDrivePID->IsEnabled() && !rightDrivePID->IsEnabled()) {
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
	leftDrivePID->Disable();
	rightDrivePID->Disable();	
	drvTrain->SetSafetyEnabled(true);
}
double Chassis::GetLeftSpeed( void ) 
{
	double static leftDistanceOld;
	double leftDistanceNew;
	double static timeOld;
	double timeNew;
	double leftSpeed;
	
	leftDistanceNew = leftDriveEncoder->GetDistance();
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
	
	rightDistanceNew = rightDriveEncoder->GetDistance();
	//double distanceArray[] {d0, d1, d2, d3, d4};
	//double timeArray[] {t0, t1, t2, t3, t4};
	//distanceArray[4] = distanceArray[0];
	timeNew = m_speedTimer->Get();
	rightSpeed = ((rightDistanceNew - rightDistanceOld) / (timeNew - timeOld)) * -1; 
	rightDistanceOld = rightDistanceNew;
	timeOld = timeNew;
	return ((rightSpeed) / 12);
}
double Chassis::GetDistanceUltrasonic( void )
{
	double distanceRange;
	distanceRange = ultrasonicDrive->GetRangeInches();
	return distanceRange;	
}

void Chassis::UpdateDistance( void )
{
	double oldValues[4];
	oldValues[0] = SmartDashboard::GetNumber("Distance0");
	oldValues[1] = SmartDashboard::GetNumber("Distance1");
	oldValues[2] = SmartDashboard::GetNumber("Distance2");
	SmartDashboard::PutNumber("Distance0", SmartDashboard::GetNumber("Distance Range"));
	SmartDashboard::PutNumber("Distance1", oldValues[0]);
	SmartDashboard::PutNumber("Distance2", oldValues[1]);
	SmartDashboard::PutNumber("Distance3", oldValues[2]);
	
}
