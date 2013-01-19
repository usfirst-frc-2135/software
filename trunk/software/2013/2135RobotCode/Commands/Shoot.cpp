///////////////////////////////////////////////////////////////////////////////
//
//	Shoot.cpp
//
//	Shoot command definition file.
//
#include "Shoot.h"

//	When created, take control of shooter subsystem

Shoot::Shoot( double power ) {
	// Use requires() here to declare subsystem dependencies
	printf( "2135: Shoot - Constructed\n" );
	Requires( shooter );
	m_power = power;
}

//	Initialization tasks
//	Called just before this Command runs the first time

void Shoot::Initialize() {
	printf( "2135: Shoot - Initialize\n" );
}

//	Normal tasks
//	Called repeatedly when this Command is scheduled to run

void Shoot::Execute() {
	shooter->SetPower( oi->getDriverThrottle(), oi->getOperatorThrottle() );
}

//	Test for when finished
//	Make this return true when this Command no longer needs to run execute()

bool Shoot::IsFinished() {
	return false;
}

//	Called once after isFinished returns true

void Shoot::End() {
	printf( "2135: Shoot - End\n" );
}

// Called when another command uses require on this subsystem and is scheduled

void Shoot::Interrupted() {
	printf( "2135: Shoot - Interrupted\n" );
}
