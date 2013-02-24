// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Shooter.h"
#include "../Robotmap.h"
#include "../Commands/ShooterStop.h"
Shooter::Shooter() : Subsystem("Shooter") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	firingPin = RobotMap::shooterFiringPin;
	entryShooterMotor = RobotMap::shooterEntryShooterMotor;
	exitShooterMotor = RobotMap::shooterExitShooterMotor;
	exitShooterEncoder = RobotMap::shooterExitShooterEncoder;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new ShooterStop());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
//
// Set shooter entry and exit power levels
void Shooter::SetPower( double entryPower, double exitPower ){
	
	entryShooterMotor->Set ( entryPower, 0 );
	exitShooterMotor->Set ( exitPower, 0 );
	
	SmartDashboard::PutNumber( "Shooter Entry Power", -entryPower );
	SmartDashboard::PutNumber( "Shooter Exit Power", -exitPower );	
}
//
// Enable the firing pin pneumatic
void Shooter::enableFiringPin(){
	firingPin->Set(DoubleSolenoid::kForward);
}
//
// Disable the firing pin pneumatic
void Shooter::disableFiringPin(){
	firingPin->Set(DoubleSolenoid::kReverse);
}
