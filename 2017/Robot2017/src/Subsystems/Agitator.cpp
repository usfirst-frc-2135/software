// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Agitator.h"
#include "../RobotMap.h"
#include "../Commands/AgitatorMotorControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Agitator::Agitator() : Subsystem("Agitator") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motor12 = RobotMap::agitatorMotor12;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	std::printf("2135: Agitator Constructor\n");
}

void Agitator::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new AgitatorMotorControl(0));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Agitator::Initialize(frc::Preferences *prefs)
{
	// Initialize SmartDashboard values - if any
	std::printf("2135: Agitator Initialize\n");
    motor12->SetNeutralMode(NeutralMode::Coast);
	motor12->Set(ControlMode::PercentOutput, 0.0);
}

void Agitator::UpdateSmartDashboardValues(void)
{

}

void Agitator::SetMotorSpeed(int speed)
{
	// Window motor direction is opposite what is needed
	switch (speed)
	{
	default:
	case AGITATOR_STOP:
		motor12->Set(0.0);
		break;
	case AGITATOR_FORWARD:
		motor12->Set(-agitatorSpeed);
		break;
	case AGITATOR_REVERSE:
		motor12->Set(agitatorSpeed);
		break;
	}
}
