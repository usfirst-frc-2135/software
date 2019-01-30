// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Subsystems/Lifter.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Lifter::Lifter() : frc::Subsystem("Lifter") {

    std::printf("2135: LF Lifter Constructor");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    front.reset(new frc::Solenoid(0, 1));
    back.reset(new frc::Solenoid(0, 3));
    motorLF16.reset(new WPI_TalonSRX(16));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controller, initialize, and display firmware version
    m_talonValidLF16 = frc2135::TalonSRXUtils::TalonSRXCheck(motorLF16, "LF", "16");

    // Check if solenoids are functional or blacklisted
    if (front->IsBlackListed())
        std::printf("2135: ERROR: LF Front Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: LF Front Solenoid is FUNCTIONAL\n");
    if (back->IsBlackListed())
        std::printf("2135: ERROR: LF Back Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: LF Back Solenoid is FUNCTIONAL\n");

    // Retrieve lifter modified parameters from RobotConfig
     frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
     config->GetValueAsDouble("LF_DriveSpeed", m_driveSpeed, 0.5);

    // Set motor direction
    // Turn on Brake mode
    // Set motor peak output
    if (m_talonValidLF16) {
        motorLF16->SetInverted(true);
        motorLF16->SetNeutralMode(NeutralMode::Brake);
        motorLF16->ConfigPeakOutputForward(m_driveSpeed, m_timeout);
        motorLF16->ConfigPeakOutputReverse(-m_driveSpeed, m_timeout);    
    }

    Lifter::Initialize();
}

void Lifter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Lifter::Periodic() {
    // Put code here to be run every loop
    double outputLF16 = 0.0, currentLF16 = 0.0;

    if (m_talonValidLF16) {
        outputLF16 = motorLF16->GetMotorOutputVoltage();
        currentLF16 = motorLF16->GetOutputCurrent();
    }

    if (m_lifterDebug) {
        frc::SmartDashboard::PutNumber("LF_Output_LF16", outputLF16);
        frc::SmartDashboard::PutNumber("LF_Current_LF16", currentLF16);
    }
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

//////////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Lifter::Initialize(void) {
    std::printf("2135: LF Init\n");

    // Motor off
    if (m_talonValidLF16)
        SetLifterMotorSpeed(LIFTER_STOP);

    // Keep lifters retracted
    SetFrontSolenoid(false);
    SetBackSolenoid(false);
}

void Lifter::SetLifterMotorSpeed(int direction) {
    const char *strName;
    double outputLF16 = 0.0;        // Default: off

    switch (direction)
    {
    default:
    case LIFTER_STOP:
        strName = "STOP";
        outputLF16 = 0.0;
        break;
    case LIFTER_FORWARD:
        strName = "FORWARD";
        outputLF16 = m_driveSpeed;
        break;
    case LIFTER_REVERSE:
        strName = "REVERSE";
        outputLF16 = -m_driveSpeed;
    }

    std::printf("2135: Lifter Motor Set Speed - %s\n", strName);

    if (m_talonValidLF16)
        motorLF16->Set(ControlMode::PercentOutput, outputLF16);
}

void Lifter::SetFrontSolenoid(bool extended) {
    const char *strName;
    
    if (extended)
        strName = "EXTEND";
    else {
        strName = "RETRACT";
    }

    std::printf("2135: Lifter Front - %s\n", strName);

    front->Set(extended);
}

void Lifter::SetBackSolenoid(bool extended) {
    const char *strName;
    
    if (extended)
        strName = "EXTEND";
    else {
        strName = "RETRACT";
    }

    std::printf("2135: Lifter Back - %s\n", strName);

    back->Set(extended);
}
