#include "DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() {
	Requires( chassis );
}

void DriveWithJoystick::Initialize() {
}

void DriveWithJoystick::Execute() {
	chassis->driveWithJoystick( oi->getJoystick() );
}

bool DriveWithJoystick::IsFinished() {
	return false;
}

void DriveWithJoystick::End() {
}

void DriveWithJoystick::Interrupted() {
}
