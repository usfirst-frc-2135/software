#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveWithJoystick.h"

Chassis::Chassis() : Subsystem("Chassis") {
	driveTrain = new RobotDrive ( PWM_LEFT_DRIVE_MOTOR, PWM_RIGHT_DRIVE_MOTOR );
	driveTrain->SetSafetyEnabled ( false );
}
    
void Chassis::InitDefaultCommand () {
	SetDefaultCommand ( new DriveWithJoystick() );
}

void Chassis::goStraight () {
	driveTrain->ArcadeDrive ( 1.0, 0.0 );
}

void Chassis::driveWithJoystick ( Joystick *driverStick ) {
	driveTrain->ArcadeDrive ( driverStick );
}



