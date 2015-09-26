// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ShooterReload.h"
ShooterReload::ShooterReload() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	m_reloadTimer = new Timer;
}
// Called just before this Command runs the first time
void ShooterReload::Initialize() {
	printf( "2135: Shooter Reload\n" );
	m_speed = SmartDashboard::GetNumber("Shooter Speed");
	Robot::shooter->ShooterEngage();
	m_reloadTimer->Reset();
	m_reloadTimer->Start();
}
// Called repeatedly when this Command is scheduled to run
void ShooterReload::Execute() {
	Robot::shooter->ShooterReload(m_speed);
}
// Make this return true when this Command no longer needs to run execute()
bool ShooterReload::IsFinished() {
	if ( ( m_reloadTimer->HasPeriodPassed(m_reloadMaxTime) ) || 
		( Robot::shooter->IsShooterFullBack() ) ) {
		if ( m_reloadTimer->HasPeriodPassed(m_reloadMaxTime) ) 
			printf( "2135: ShooterReload Timed Out\n" );
		else 
			printf( "2135: ShooterReload completed in %f seconds\n", m_reloadTimer->Get() );
		return true;
	}
	else 
		return false;
}
	
// Called once after isFinished returns true
void ShooterReload::End() {
	Robot::shooter->ShooterReload(0.0);
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterReload::Interrupted() {
}
