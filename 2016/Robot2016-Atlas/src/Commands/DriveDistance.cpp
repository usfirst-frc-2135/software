// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "DriveDistance.h"
DriveDistance::DriveDistance() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::chassis);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::transmission);
	m_pidTimer = new Timer;
}
// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	double distance;
	printf( "2135: Drive Distance\n" );
	Robot::transmission->ShiftLow();
	printf( "2135: Shift Low Gear\n" );
#if SMARTDASHBOARD_ENABLE // SmartDashboard::
	distance = SmartDashboard::GetNumber("Target Setpoint");
#else // SmartDashboard::
	distance = 65.0;
#endif // SmartDashboard::
	Robot::chassis->DriveDistanceWithPIDInit(distance);
	// Reset the PID safety timer to zero and start it
	m_pidTimer->Reset();
	m_pidTimer->Start();
}
// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	Robot::chassis->DriveDistanceWithPIDExecute();
}
// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	double temp;
	temp = m_pidTimer->Get();
	
	if ( ( m_pidTimer->HasPeriodPassed(m_pidMaxTime) ) || 
		( Robot::chassis->DriveDistanceWithPIDIsAtSetpoint() ) ) {
		Robot::chassis->DriveDistanceWithPIDStop();
		if ( m_pidTimer->HasPeriodPassed(m_pidMaxTime) ) 
			printf( "2135: PID Timed Out\n" );
		else 
			printf( "2135: PID completed in %f seconds\n", temp );
		return true;
	}
	else
		return false;
}
// Called once after isFinished returns true
void DriveDistance::End() {
	Robot::chassis->DriveDistanceWithPIDStop();
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() {
	Robot::chassis->DriveDistanceWithPIDStop();
}