// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "frc2135/RobotConfig.h"
#include "frc2135/TalonUtils.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/Intake.h"
#include <frc/smartdashboard/SmartDashboard.h>

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Intake::Intake(){
    SetName("Intake");
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
 

 AddChild("Position", &m_position);
 

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidIN6 = frc2135::TalonUtils::TalonCheck(m_motorIN6, "IN", "IN6");

     // Check if solenoids are functional or blacklisted
    if (m_position.IsFwdSolenoidBlackListed())
        std::printf("2135: ERROR: IN Intake Deployer FWD Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: IN Intake Deployer FWD Solenoid is FUNCTIONAL\n");

    if (m_position.IsRevSolenoidBlackListed())
        std::printf("2135: ERROR: IN Intake Deployer REV Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: IN Intake Deployer REV Solenoid is FUNCTIONAL\n");

    // Initialize Variables
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("IN_AcquireSpeed", m_acquireSpeed, 0.8);
    config->GetValueAsDouble("IN_ExpelSpeed", m_expelSpeed, -0.8);

    // Set motor directions
    // Turn on Coast mode (not brake)
    // Set motor peak outputs
    if (m_talonValidIN6)
    {
        m_motorIN6.SetInverted(false);
        m_motorIN6.SetNeutralMode(NeutralMode::Coast);
        m_motorIN6.SetSafetyEnabled(false);

        m_motorIN6.ConfigVoltageCompSaturation(12.0, 0);
        m_motorIN6.EnableVoltageCompensation(true);
    }

    Initialize();
}

void Intake::Periodic() {

    static int  periodicInterval = 0;

    // Put code here to be run every 20 ms loop

    // Only update indicators every 100 ms to cut down on network traffic
    if (periodicInterval++ % 5 == 0)
    {
        double outputIN6 = 0.0;

        if (m_talonValidIN6)
            outputIN6 = m_motorIN6.GetMotorOutputPercent();
        frc::SmartDashboard::PutNumber("IN_Output_IN6", outputIN6);

        if (m_intakeDebug > 0)
        {
            double currentIN6 = 0.0;

            if (m_talonValidIN6)
                currentIN6 = m_motorIN6.GetOutputCurrent();

            frc::SmartDashboard::PutNumber("IN_Current_IN6", currentIN6);
        }
    }
}

void Intake::SimulationPeriodic() {
    // This method will be called once per scheduler run when in simulation

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Intake::Initialize(void)
{
    std::printf("2135: IN Init\n");

     if (m_talonValidIN6)
        SetIntakeMotorDirection(INTAKE_STOP);
}

// Dump all Talon faults
void Intake::FaultDump(void)
{
    frc2135::TalonUtils::TalonFaultDump("IN 6", m_motorIN6);
}

// Set mode of intake
void Intake::SetIntakeMotorDirection(int direction)
{
    const char *strName;
    double output = 0.0;        // Default: off

    switch(direction)
    {
        default:
        case INTAKE_STOP:
            strName = "STOP";
            output = 0.0;
            break;
        case INTAKE_FORWARD:
            strName = "FORWARD";
            output = m_acquireSpeed;
            break;
        case INTAKE_REVERSE:
            strName = "REVERSE";
            output = m_expelSpeed;
            break;
    }

    // Set speed of intake and the percent output
    std::printf("2135: Intake Set Speed - %s\n", strName);

    if (m_talonValidIN6)
        m_motorIN6.Set(ControlMode::PercentOutput, output);
}
