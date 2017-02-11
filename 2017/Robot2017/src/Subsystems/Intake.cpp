// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CANTalon.h"


#include "Intake.h"
#include "../RobotMap.h"
#include "../Commands/IntakeMotorControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Intake::Intake() : Subsystem("Intake") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motor8 = RobotMap::intakeMotor8;
    motor9 = RobotMap::intakeMotor9;
    armDeploy = RobotMap::intakeArmDeploy;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    printf("2135: Intake constructor\n");
}

void Intake::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new IntakeMotorControl(0));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Intake::Initialize(Preferences *prefs)
{
	// TODO: Initialize SmartDashboard values
	printf("2135: Intake Initialize\n");
    motor8->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	motor8->SetTalonControlMode(CANTalon::TalonControlMode::kVoltageMode);

    motor9->ConfigNeutralMode(CANTalon::NeutralMode::kNeutralMode_Coast);
	motor9->SetTalonControlMode(CANTalon::TalonControlMode::kFollowerMode);
	motor9->SetClosedLoopOutputDirection(true);
	motor9->Set(8);
}

void Intake::UpdateSmartDashboardValues(void)
{

}

void Intake::ArmExtend(bool extend)
{
	if (extend) {
		armDeploy->Set(armDeploy->kForward);
	}
	else {
		armDeploy->Set(armDeploy->kReverse);
	}
}

void Intake::SetMotorSpeed(int speed)
{
	switch (speed)
	{
	default:
	case INTAKE_STOP:
		motor8->Set(0.0);
		break;
	case INTAKE_FORWARD:
		motor8->Set(intakeSpeed);
		break;
	case INTAKE_REVERSE:
		motor8->Set(-intakeSpeed);
		break;
	}
}
