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
	leftDriveMotor = RobotMap::chassisLeftDriveMotor;
	leftDriveEncoder = RobotMap::chassisLeftDriveEncoder;
	leftDrivePID = RobotMap::chassisLeftDrivePID;
	rightDriveMotor = RobotMap::chassisRightDriveMotor;
	rightDriveEncoder = RobotMap::chassisRightDriveEncoder;
	rightDrivePID = RobotMap::chassisRightDrivePID;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	printf("2135: Chassis Constructor\n" );
	driveTrain = RobotMap::driveTrain;
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
void Chassis::DriveWithJoystick(Joystick *driverJoystick){
	driveTrain->ArcadeDrive( driverJoystick, true );
}
//
//	Autonomous Drive to a specific distance - PID initialization
//
void Chassis::DriveDistanceWithPIDInit(double distance){
	double leftDistance;
	double rightDistance;
	RobotMap::chassisLeftDrivePID->SetPID(SmartDashboard::GetNumber("L: P"),SmartDashboard::GetNumber("L: I"),
					SmartDashboard::GetNumber("L: D"));
	RobotMap::chassisLeftDrivePID->SetOutputRange(-0.6,0.6);
	RobotMap::chassisLeftDrivePID->SetAbsoluteTolerance(0.2);
	RobotMap::chassisLeftDriveEncoder->SetDistancePerPulse(4 * M_PI / 360);
	RobotMap::chassisRightDrivePID->SetPID(SmartDashboard::GetNumber("R: P"),SmartDashboard::GetNumber("R: I"),
					SmartDashboard::GetNumber("R: D"));
	RobotMap::chassisLeftDrivePID->SetOutputRange(-0.6,0.6);
	RobotMap::chassisLeftDrivePID->SetAbsoluteTolerance(0.2);
	RobotMap::chassisRightDriveEncoder->SetDistancePerPulse(4 * M_PI / 360);
	// get current encoder values
	leftDistance = leftDriveEncoder->GetDistance();
	rightDistance = rightDriveEncoder->GetDistance();
	// add distance to current encoder values
	leftDistance += distance;
	rightDistance -= distance;
	SmartDashboard::PutNumber( "Left Setpoint", leftDistance );
	SmartDashboard::PutNumber( "Right Setpoint", -rightDistance );
	// set SetPoint with calculated target distance
	RobotMap::chassisLeftDrivePID->SetSetpoint( leftDistance );
	RobotMap::chassisRightDrivePID->SetSetpoint( rightDistance );
	// enable PID loops
	RobotMap::chassisLeftDrivePID->Enable();
	RobotMap::chassisRightDrivePID->Enable();
	SmartDashboard::PutBoolean("Left PID State", false );
	SmartDashboard::PutBoolean("Right PID State", false );
}
//
//	Autonomous Drive to a specific distance - called from command execute
//
void Chassis::DriveDistanceWithPIDExecute(){
	if(RobotMap::chassisLeftDrivePID->OnTarget())
	{
		SmartDashboard::PutBoolean("Left PID State", true );
		RobotMap::chassisLeftDrivePID->Disable();
	}
	if(RobotMap::chassisRightDrivePID->OnTarget())
	{
		SmartDashboard::PutBoolean("Right PID State", true);
		RobotMap::chassisRightDrivePID->Disable();
	}
	
	if(!RobotMap::chassisLeftDrivePID->IsEnabled()) 
		RobotMap::chassisLeftDriveMotor->Set(0, 0);
	if(!RobotMap::chassisRightDrivePID->IsEnabled()) 
		RobotMap::chassisRightDriveMotor->Set(0, 0);
}
//
//	Autonomous Drive to a specific distance - detect when at setpoint
//
bool Chassis::DriveDistanceWithPIDIsAtSetpoint(){
	bool bothOnTarget;
	// are both PIDs on target
	bothOnTarget = false;
	if (!RobotMap::chassisLeftDrivePID->IsEnabled() && 
			!RobotMap::chassisRightDrivePID->IsEnabled()) {
		Chassis::DriveDistanceWithPIDStop();
		bothOnTarget=true;
	}
	
	return bothOnTarget;
}
//
//	Autonomous Drive to a specific distance - stop the PID loop
//
void Chassis::DriveDistanceWithPIDStop(){
	SmartDashboard::PutBoolean("Left PID State", true);
	SmartDashboard::PutBoolean("Right PID State", true);
	RobotMap::chassisLeftDrivePID->Disable();
	RobotMap::chassisRightDrivePID->Disable();	
}
