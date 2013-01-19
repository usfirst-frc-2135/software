///////////////////////////////////////////////////////////////////////////////
//
//	DriveStraight.cpp
//
//	DriveStraight command definition file.
//
#include "DriveStraight.h"

// WHen created, take control of chassis and setup timer

DriveStraight::DriveStraight( double timeout ) {
	printf ( "2135: DriveStraight - Constructed\n" );
	Requires( chassis );
	m_timeout = timeout;
}

//	Initialization tasks
//	Called just before this Command runs the first time

void DriveStraight::Initialize() {
	printf( "2135: DriveStraight - Initialize\n" );
	SetTimeout( m_timeout );
}

//	Normal tasks
//	Called repeatedly when this Command is scheduled to run

void DriveStraight::Execute() {
	chassis->goStraight();
}

//	Test for when finished
//	Make this return true when this Command no longer needs to run execute()

bool DriveStraight::IsFinished() {
	return IsTimedOut();
}

//	Called once after isFinished returns true

void DriveStraight::End() {	
	printf( "2135: DriveStraight - End\n" );
}

// Called when another command uses require on this subsystem and is scheduled

void DriveStraight::Interrupted() {
	printf( "2135: DriveStraight - Interrupted\n" );
}
