#include "DriveWithJoystick.h"

DriveWithJoystick::DriveWithJoystick() {
	Requires( chassis );
}

void DriveWithJoystick::Initialize() {
}

void DriveWithJoystick::Execute() {
	chassis->driveWithJoystick( oi->getDriverJoystick() );
}

bool DriveWithJoystick::IsFinished() {
	return false;
}

void DriveWithJoystick::End() {
}

void DriveWithJoystick::Interrupted() {
}
