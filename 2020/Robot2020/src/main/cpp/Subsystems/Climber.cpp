// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <Subsystems/Climber.h>
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Climber::Climber() : frc::Subsystem("Climber") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorCL14.reset(new WPI_TalonSRX(14));

    position.reset(new frc::DoubleSolenoid(0, 3, 4));
    AddChild("Position", position);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate and initialize Talon SRX controller
    m_talonValidCL14 = frc2135::TalonUtils::TalonCheck(motorCL14, "CL", "14");

    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
	config->GetValueAsDouble("CL_ClimbSpeed", m_climbSpeed, 1.0);

    if (m_talonValidCL14) {
        motorCL14->Set(ControlMode::PercentOutput, 0.0);
        motorCL14->SetNeutralMode(NeutralMode::Brake);
        motorCL14->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorCL14->EnableVoltageCompensation(true);
    }

    // Check if solenoids are functional or blacklisted
    if (position->IsFwdSolenoidBlackListed())
        std::printf("2135: ERROR: CL Climber Deployer FWD Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: CL Climber Deployer FWD Solenoid is FUNCTIONAL\n");

    if (position->IsRevSolenoidBlackListed())
        std::printf("2135: ERROR: CL Climber Deployer REV Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: CL Climber Deployer REV Solenoid is FUNCTIONAL\n");

}

void Climber::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Climber::Periodic() {
    // Put code here to be run every loop

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Climber::SetClimberMotorOutput(int direction) {
     double outputSH = 0.0; 		// Default: off

    switch (direction)
	{
	default:
	case CLIMBER_STOP:
		outputSH = 0.0;
		break;
	case CLIMBER_UP:
		outputSH = m_climbSpeed;
		break;
	case CLIMBER_DOWN:
		outputSH = -m_climbSpeed;
		break;
	}

	if (m_talonValidCL14)
		motorCL14->Set(ControlMode::PercentOutput, outputSH);
}

void Climber::DeployClimber(bool state) {
    // If state is true, sets climber deploy forward.
    // If state is false, sets climber deploy reverse.
    position->Set( (state) ? position->kForward : position->kReverse);
}