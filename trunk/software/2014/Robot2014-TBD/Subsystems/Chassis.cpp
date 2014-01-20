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
	leftEncoder = RobotMap::chassisLeftEncoder;
	rightEncoder = RobotMap::chassisRightEncoder;
	leftMotor = RobotMap::chassisLeftMotor;
	rightMotor = RobotMap::chassisRightMotor;
	robotDrive = RobotMap::chassisRobotDrive;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	driveControlLeft = RobotMap::driveControlLeft;
	driveControlRight = RobotMap::driveControlRight;
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
//	Normal drive during Teleop using joysticks
void Chassis::DriveUsingJoysticks(Joystick *driverStick){
	robotDrive->ArcadeDrive(driverStick, true);
}
//	Autonomous PID driving initialization
void Chassis::DriveUsingPIDInit(double distance) {
	double	outputRange;
	double	absTolerance;
	
	outputRange = SmartDashboard::GetNumber("Output Range");
	driveControlLeft->SetOutputRange(-outputRange, outputRange);
	driveControlRight->SetOutputRange(-outputRange, outputRange);
	
	absTolerance = SmartDashboard::GetNumber("Abs Tolerance");
	driveControlLeft->SetAbsoluteTolerance(absTolerance);
	driveControlRight->SetAbsoluteTolerance(absTolerance);
	
	m_leftEncoder = leftEncoder->GetDistance();
	m_rightEncoder = rightEncoder->GetDistance();
	SmartDashboard::PutNumber("Left Encoder", m_leftEncoder);
	SmartDashboard::PutNumber("Right Encoder", m_rightEncoder);

	driveControlLeft->Enable();
	driveControlRight->Enable();
	driveControlLeft->SetSetpoint(m_leftEncoder + distance);
	driveControlRight->SetSetpoint(m_rightEncoder + distance);
}
//	Autonomous PID driving normal execution processing
void Chassis::DriveUsingPID(void) {
	m_leftEncoder = leftEncoder->GetDistance();
	m_rightEncoder = rightEncoder->GetDistance();
	SmartDashboard::PutNumber("Left Encoder", m_leftEncoder);
	SmartDashboard::PutNumber("Right Encoder", m_rightEncoder);
}
//	Autonomous PID driving to stop PID processing
void Chassis::DriveUsingPIDStop(void) {
	driveControlLeft->Disable();
	driveControlRight->Disable();
}
//	Autonomous PID driving on target check
bool Chassis::DriveUsingPIDOnTarget() {
	if (driveControlLeft->OnTarget() && driveControlRight->OnTarget())
		return true;
	else
		return false;
}
