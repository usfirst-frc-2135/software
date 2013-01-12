#include "Turn.h"

Turn::Turn( double timeout ) {
	m_timeout = timeout;
	Requires( chassis );
}

void Turn::Initialize() {
	SetTimeout( m_timeout );
}

void Turn::Execute() {
	chassis->turnLeft();
}

bool Turn::IsFinished() {
	return IsTimedOut();
}

void Turn::End() {
}

void Turn::Interrupted() {
}
