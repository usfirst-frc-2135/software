// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/DriveTeleop.h"
Chassis::Chassis() : Subsystem("Chassis") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	left = RobotMap::chassisLeft;
	right = RobotMap::chassisRight;
	driveTrain = RobotMap::chassisDriveTrain;
	leftEncoder = RobotMap::chassisLeftEncoder;
	rightEncoder = RobotMap::chassisRightEncoder;
	gyro = RobotMap::chassisGyro;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Chassis::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new DriveTeleop());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
// Teleop drive under joystick control
void Chassis::DriveWithJoystick(Joystick *driverStick){
		driveTrain->ArcadeDrive( driverStick, true );
//		RobotMap::driverStationLCD->PrintfLine( DriverStationLCD::kUser_Line1, "Drive %5.2f %5.2f", 
//			driverStick->GetAxis( Joystick::kYAxis ), driverStick->GetAxis( Joystick::kXAxis ) );
}
//Controlled drive used during autonomous or drive commands
void Chassis::DriveUsingLeftRightMotorOutputs(double left, double right){
	// printf ( "2135: SetLeftRightMotorOutputs left - %6.3f, right - %6.3f\n", left, right);
	driveTrain->SetLeftRightMotorOutputs( left, right );
//	RobotMap::driverStationLCD->PrintfLine( DriverStationLCD::kUser_Line1, "Drive %5.2f %5.2f", 
//			left, right );
}
