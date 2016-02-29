// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Shooter.h"
#include "../RobotMap.h"
#include "../Robot.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Shooter::Shooter() : Subsystem("Shooter") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    lowerMotor = RobotMap::shooterLowerMotor;
    upperMotor = RobotMap::shooterUpperMotor;
    fireSolenoid = RobotMap::shooterFireSolenoid;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    lowerMotor->SetSafetyEnabled(false);
    upperMotor->SetSafetyEnabled(false);

    m_upperSpeed = 0.8;
    m_lowerSpeed = 0.5;

    lowerMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    upperMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Initialize(Preferences *prefs) {
	printf("2135: Shooter Initialize\n");
	m_upperSpeed = Robot::LoadPreferencesVariable("ShooterUpperSpeed", 0.5);
	m_lowerSpeed = Robot::LoadPreferencesVariable("ShooterLowerSpeed", 0.5);

	SmartDashboard::PutNumber("LowShotUpperMotor", Robot::LoadPreferencesVariable ("LowShotUpperMotor", 0.75));
	SmartDashboard::PutNumber("LowShotLowerMotor", Robot::LoadPreferencesVariable ("LowShotLowerMotor", 0.5));
	SmartDashboard::PutNumber("MidShotUpperMotor", Robot::LoadPreferencesVariable ("MidShotUpperMotor", 0.85));
	SmartDashboard::PutNumber("MidShotLowerMotor", Robot::LoadPreferencesVariable ("MidShotLowerMotor", 0.6));
	SmartDashboard::PutNumber("HighShotUpperMotor", Robot::LoadPreferencesVariable ("HighShotUpperMotor", 0.95));
	SmartDashboard::PutNumber("HighShotLowerMotor", Robot::LoadPreferencesVariable ("HighShotLowerMotor", 0.7));

	SmartDashboard::PutNumber("Upper Shooter Speed", 0.0);
	SmartDashboard::PutNumber("Lower Shooter Speed", 0.0);
}


void Shooter::ShootSpeeds(double upperSpeed, double lowerSpeed) {
	lowerMotor->Set(lowerSpeed);
	upperMotor->Set(upperSpeed);

}

void Shooter::setFireSolenoid(bool fire) {
	if (fire == true) {
		fireSolenoid->Set(DoubleSolenoid::kForward);
	}
	else {
		fireSolenoid->Set(DoubleSolenoid::kReverse);
	}
}
