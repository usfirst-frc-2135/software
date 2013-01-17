#include "DriveStraight.h"

DriveStraight::DriveStraight( double timeout ) {
	m_timeout = timeout;
	Requires( chassis );
	printf ( "2135 - DriveStraight\n" );
}

void DriveStraight::Initialize() {
	printf( "2135: DriveStraight - Init\n" );
	SetTimeout( m_timeout );
}

void DriveStraight::Execute() {
	printf( "2135: DriveStraight - Exec\n" );
	chassis->goStraight();
}

bool DriveStraight::IsFinished() {
	printf( "2135: DriveStraight - IsFinished\n" );
	return IsTimedOut();
}

void DriveStraight::End() {	
	printf( "2135: DriveStraight - End\n" );
}

void DriveStraight::Interrupted() {
	printf( "2135: DriveStraight - Interrupted\n" );
}
