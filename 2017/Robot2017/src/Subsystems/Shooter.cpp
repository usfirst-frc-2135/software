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

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    printf("2135: Shooter Constructor\n");
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

void Shooter::Initialize(Preferences *prefs)
{
	// TODO: Initialize SmartDashboard values - if any
	printf("2135: Shooter Initialize\n");
    motor14->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	motor14->SetTalonControlMode(CANTalon::TalonControlMode::kThrottleMode);

	ballGate->SetAngle(0);
}

void Shooter::UpdateSmartDashboardValues(void)
{

}

void Shooter::BallGateDeploy(bool open)
{
	if (open) {
		ballGate->SetAngle(90);
		printf("2135: Ball gate opened\n");
	}
	else {
		ballGate->SetAngle(0);
		printf("2135: Ball gate closed\n");
	}
}

void Shooter::SetMotorSpeed(bool enabled)
{
	if (enabled) {
		motor14->Set(shooterSpeed);
	}
	else {
		motor14->Set(0.0);
	}
}
