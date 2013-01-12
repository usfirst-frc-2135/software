#include "DriveStraight.h"

DriveStraight::DriveStraight( double timeout ) {
	m_timeout = timeout;
	Requires( chassis );
}

void DriveStraight::Initialize() {
	SetTimeout( m_timeout );
}

void DriveStraight::Execute() {
	chassis->goStraight();
}

bool DriveStraight::IsFinished() {
	return IsTimedOut();
}

void DriveStraight::End() {	
}

void DriveStraight::Interrupted() {
}
