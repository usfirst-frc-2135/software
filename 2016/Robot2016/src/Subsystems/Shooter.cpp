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
#include "../Commands/Shoot.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Shooter::Shooter() : Subsystem("Shooter") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    lowerMotor = RobotMap::shooterLowerMotor;
    upperMotor = RobotMap::shooterUpperMotor;
    frameSolenoid = RobotMap::shooterFrameSolenoid;
    fireSolenoid = RobotMap::shooterFireSolenoid;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    lowerMotor->SetSafetyEnabled(false);
    upperMotor->SetSafetyEnabled(false);

    m_upperSpeed = 0.85;
    m_lowerSpeed = 0.6;

    lowerMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    upperMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);

    SetFrameControl(false);
    SetFireSolenoid(true);
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new Shoot(0, 0));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Initialize(Preferences *prefs) {
	printf("2135: Shooter Initialize\n");
	m_upperSpeed = Robot::LoadPreferencesVariable("ShooterUpperSpeed", 0.95);
	m_lowerSpeed = Robot::LoadPreferencesVariable("ShooterLowerSpeed", 0.7);

	SmartDashboard::PutNumber("LowShotUpperMotor", Robot::LoadPreferencesVariable ("LowShotUpperMotor", 0.75));
	SmartDashboard::PutNumber("LowShotLowerMotor", Robot::LoadPreferencesVariable ("LowShotLowerMotor", 0.5));
	SmartDashboard::PutNumber("MidShotUpperMotor", Robot::LoadPreferencesVariable ("MidShotUpperMotor", 0.85));
	SmartDashboard::PutNumber("MidShotLowerMotor", Robot::LoadPreferencesVariable ("MidShotLowerMotor", 0.6));
	SmartDashboard::PutNumber("HighShotUpperMotor", Robot::LoadPreferencesVariable ("HighShotUpperMotor", 0.95));
	SmartDashboard::PutNumber("HighShotLowerMotor", Robot::LoadPreferencesVariable ("HighShotLowerMotor", 0.7));

	SmartDashboard::PutNumber("Upper Shooter Speed", 0.0);
	SmartDashboard::PutNumber("Lower Shooter Speed", 0.0);
}

void Shooter::SetMotorSpeeds(double upperSpeed, double lowerSpeed) {
	lowerMotor->Set(lowerSpeed);
	upperMotor->Set(upperSpeed);

}

void Shooter::SetFireSolenoid(bool fire) {
	if (fire) {
		fireSolenoid->Set(DoubleSolenoid::kReverse);
	}
	else {
		fireSolenoid->Set(DoubleSolenoid::kForward);
	}
}

void Shooter::SetFrameControl(bool frameUp) {
	if (frameUp) {
		frameSolenoid->Set(frameSolenoid->kForward);
	}
	else {
		frameSolenoid->Set(frameSolenoid->kReverse);
	}
}
