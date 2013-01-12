#include "Robotmap.h"
#include "OI.h"
#include "Commands/DriveInASquare.h"

OI::OI() {
	stick = new Joystick( JOYSTICK_PORT );
	trigger = new JoystickButton( stick, Joystick::kTopButton );
	trigger->WhenPressed(new DriveInASquare());
}

Joystick * OI::getJoystick() {
	return stick;
}
