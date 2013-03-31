// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "DriveStraightDistance.h"
#include "math.h"
DriveStraightDistance::DriveStraightDistance() {
	m_timeout = 3;
	m_targetInches = 10;
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void DriveStraightDistance::Initialize() {
	printf ("2135: DriveStraightDistance - %5.1f inches\n", m_targetInches);
	SetTimeout(m_timeout);
	m_startLeftInches = RobotMap::chassisLeftEncoder->GetDistance();
	m_startRightInches = RobotMap::chassisRightEncoder->GetDistance();
}
// Called repeatedly when this Command is scheduled to run
void DriveStraightDistance::Execute() {
	double leftEncoder;
	double rightEncoder;
	double leftMotorPower;
	double rightMotorPower;
	
	leftEncoder = RobotMap::chassisLeftEncoder->GetDistance()
			- m_startLeftInches;
	rightEncoder = RobotMap::chassisRightEncoder->GetDistance()
			- m_startRightInches;
	printf ("2135: LeftRightEncoder Start Left - %6.3f Right - %6.3f\n", leftEncoder, rightEncoder);
	if (leftEncoder < 10)
		leftMotorPower = 0.6;
	else
		leftMotorPower = 0.3;
	if (rightEncoder < 10)
		rightMotorPower = 0.6;
	else
		rightMotorPower = 0.3;
	Robot::chassis->DriveUsingLeftRightMotorOutputs(leftMotorPower, rightMotorPower);
}
// Make this return true when this Command no longer needs to run execute()
bool DriveStraightDistance::IsFinished() {
	bool atTarget;
	double leftEncoder;
	double rightEncoder;
	
	leftEncoder = RobotMap::chassisLeftEncoder->GetDistance()
			- m_startLeftInches;
	rightEncoder = RobotMap::chassisRightEncoder->GetDistance()
			- m_startRightInches;
	printf ("2135: LeftRightEncoder Current Left - %6.3f Right - %6.3f\n", leftEncoder, rightEncoder);
	atTarget = (fabs(m_targetInches - leftEncoder) < 2.0)
		&& (fabs(m_targetInches -  rightEncoder) < 2.0);
	printf ("2135: LeftRightEncoder fabs Left - %6.3f Right - %6.3f\n", 
		fabs(m_targetInches - leftEncoder), fabs(m_targetInches - rightEncoder));
	return ( IsTimedOut() || atTarget);
}
// Called once after isFinished returns true
void DriveStraightDistance::End() {
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightDistance::Interrupted() {
}
