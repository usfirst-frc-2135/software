// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ShooterFireAuto.h"
#include "../CheesyVisionServer.h"
ShooterFireAuto::ShooterFireAuto() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	m_shooterTimer = new Timer;
}
// Called just before this Command runs the first time
void ShooterFireAuto::Initialize() {
	m_shooterTimer->Reset();
	m_shooterTimer->Start();
}
// Called repeatedly when this Command is scheduled to run
void ShooterFireAuto::Execute() {
	
}
// Make this return true when this Command no longer needs to run execute()
bool ShooterFireAuto::IsFinished() {
	if (CheesyVisionServer::GetInstance()->GetLeftStatus() &&
		CheesyVisionServer::GetInstance()->GetRightStatus()) {
		if ( m_shooterTimer->HasPeriodPassed(m_shooterSecondHotTime) ) {
			printf( "2135: Shooter Timed Out-Second\n" );
			Robot::shooter->ShooterDisengage();
			return true;
		}
	}
	else {
		if ( m_shooterTimer->HasPeriodPassed(m_shooterFirstHotTime) ) {
			printf( "2135: Shooter Timed Out-First\n" );
			Robot::shooter->ShooterDisengage();
			return true;
		}
	}
	return false;
}
// Called once after isFinished returns true
void ShooterFireAuto::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterFireAuto::Interrupted() {
}
