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

void Shooter::LoadPreferences(Preferences *prefs) {
	printf("2135: Shooter Preferences\n");
	m_upperSpeed = LoadPreferencesVariable (prefs, "ShooterUpperSpeed", 0.5);
	m_lowerSpeed = LoadPreferencesVariable (prefs, "ShooterLowerSpeed", 0.5);

	SmartDashboard::PutNumber("LowShotUpperMotor", LoadPreferencesVariable (prefs, "LowShotUpperMotor", 0.75));
	SmartDashboard::PutNumber("LowShotLowerMotor", LoadPreferencesVariable (prefs, "LowShotLowerMotor", 0.5));
	SmartDashboard::PutNumber("MidShotUpperMotor", LoadPreferencesVariable (prefs, "MidShotUpperMotor", 0.85));
	SmartDashboard::PutNumber("MidShotLowerMotor", LoadPreferencesVariable (prefs, "MidShotLowerMotor", 0.6));
	SmartDashboard::PutNumber("HighShotUpperMotor", LoadPreferencesVariable (prefs, "HighShotUpperMotor", 0.95));
	SmartDashboard::PutNumber("HighShotLowerMotor", LoadPreferencesVariable (prefs, "HighShotLowerMotor", 0.7));
}

double Shooter::LoadPreferencesVariable (Preferences *prefs, std::string name, double defaultValue) {
	double shooterTemp = defaultValue;
	if (prefs->ContainsKey(name)) {
		shooterTemp = prefs->GetDouble(name, defaultValue);
	}
	else {
		printf("2135: %s not found - ERROR\n", name.c_str());
	}
	printf("2135: %s : %f\n", name.c_str(), shooterTemp);
	return shooterTemp;
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
