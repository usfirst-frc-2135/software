#include "Shoot.h"

Shoot::Shoot() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires( shooter );
	printf( "2135: Shoot - Shoot\n" );
}

// Called just before this Command runs the first time
void Shoot::Initialize() {
	printf( "2135: Shoot - Init\n" );
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
//	printf( "2135: Shoot - Exec\n" );
	shooter->SetPower( oi->getDriverThrottle(), oi->getOperatorThrottle() );
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Shoot::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
}
