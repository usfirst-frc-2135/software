#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystick.h"

Chassis::Chassis() : Subsystem("Chassis") {
	drive = new RobotDrive ( LEFTMOTOR, RIGHTMOTOR );
	drive->SetSafetyEnabled ( false );
}
    
void Chassis::InitDefaultCommand () {
	SetDefaultCommand ( new DriveWithJoystick() );
}

void Chassis::goStraight () {
	drive->ArcadeDrive ( 1.0, 0.0 );
}

void Chassis::turnLeft () {
	drive->ArcadeDrive ( 0.0, 1.0 );
}

void Chassis::tankDrive ( double left, double right ) {
	drive->TankDrive ( left, right );
}
void Chassis::driveWithJoystick ( Joystick *stick ) {
	drive->ArcadeDrive ( stick );
}



