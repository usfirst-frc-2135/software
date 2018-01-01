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
#include "../Commands/ShooterMotorControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Shooter::Shooter() : Subsystem("Shooter") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motor14 = RobotMap::shooterMotor14;
    ballGate = RobotMap::shooterBallGate;
    powerEnable = RobotMap::shooterPowerEnable;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    std::printf("2135: Shooter Constructor\n");
   	m_powerState = false;
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ShooterMotorControl(false));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Initialize(frc::Preferences *prefs)
{
	// Initialize SmartDashboard values - if any
	std::printf("2135: Shooter Initialize\n");
    motor14->SetNeutralMode(NeutralMode::Coast);
	motor14->Set(ControlMode::PercentOutput, 0.0);

	ballGate->SetAngle(0);

	LightPowerEnable(SHTR_LIGHT_D);
}

void Shooter::UpdateSmartDashboardValues(void)
{

}

void Shooter::BallGateDeploy(bool open)
{
	if (open) {
		ballGate->SetAngle(90);
		std::printf("2135: Ball gate opened\n");
	}
	else {
		ballGate->SetAngle(0);
		std::printf("2135: Ball gate closed\n");
	}
}

void Shooter::SetMotorSpeed(bool enabled)
{
	double output = 0.0;		// Default to off

	if (enabled) {
		output = m_shooterSpeed;
	}

	motor14->Set(ControlMode::PercentOutput, output);
}

void Shooter::LightToggleEnable(void) {
	// Toggle light state
	LightPowerEnable(!m_powerState);
}

void Shooter::LightPowerEnable(bool enable) {

	//Alternate between 1 and 0 for each call
	m_powerState = enable;
	powerEnable->Set(m_powerState ? 1 : 0);
	SmartDashboard::PutBoolean(SHTR_LIGHT, m_powerState);
}
