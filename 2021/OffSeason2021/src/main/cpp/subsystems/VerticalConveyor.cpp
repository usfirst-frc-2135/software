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

#include <spdlog/spdlog.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/VerticalConveyor.h"

#include <frc/smartdashboard/SmartDashboard.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

VerticalConveyor::VerticalConveyor()
{
    SetName("Vertical Conveyor");
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Vertical Conveyor");

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidVC9 = frc2135::TalonUtils::TalonCheck(m_motorVC9, "VC", "VC9");

    // Initialize Variables
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("VC_AcquireSpeed", m_acquireSpeed, 1.0);
    config->GetValueAsDouble("VC_ExpelSpeed", m_expelSpeed, -0.2);
    config->GetValueAsDouble("VC_ExpelSpeedFast", m_expelSpeedFast, -1.0);

    // Set motor directions
    // Turn on Coast mode (not brake)
    // Initialize modes and set power to off
    if (m_talonValidVC9)
    {
        m_motorVC9.SetInverted(true);
        m_motorVC9.SetNeutralMode(NeutralMode::Coast);
        m_motorVC9.Set(ControlMode::PercentOutput, 0.0);

        SupplyCurrentLimitConfiguration supplyCurrentLimits;
        supplyCurrentLimits = { true, 45.0, 0.0, 0.0 };
        m_motorVC9.ConfigSupplyCurrentLimit(supplyCurrentLimits);
    }

    Initialize();
}

void VerticalConveyor::Periodic()
{
    static int periodicInterval = 0;
    // Put code here to be run every 20 ms loop
    // Only update indicators every 100 ms to cut down on network traffic
    if (periodicInterval++ % 5 == 0)
    {
        double outputVC9;

        outputVC9 = (m_talonValidVC9) ? m_motorVC9.GetMotorOutputPercent() : 0.0;
        frc::SmartDashboard::PutNumber("VC_Output_VC9", outputVC9);

        if (m_conveyorDebug > 0)
        {
            double currentVC9;

            currentVC9 = (m_talonValidVC9) ? m_motorVC9.GetOutputCurrent() : 0.0;
            frc::SmartDashboard::PutNumber("VC_Current_VC9", currentVC9);
        }
    }
}

void VerticalConveyor::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// Put methods for controlling this subsystem
// here. Call these from Commands.

void VerticalConveyor::Initialize(void)
{
    spdlog::info("VC Init");
    SetVerticalConveyorSpeed(VCONVEYOR_STOP);
}

//    Dump all Talon faults
void VerticalConveyor::FaultDump(void)
{
    frc2135::TalonUtils::TalonFaultDump("VC 9", m_motorVC9);
}

// Set mode of conveyor
void VerticalConveyor::SetVerticalConveyorSpeed(int mode)
{
    const char *strName;
    double outputVC = 0.0; // Default: off

    switch (mode)
    {
        default:
        case VCONVEYOR_STOP:
            strName = "STOP";
            outputVC = 0.0;
            break;
        case VCONVEYOR_ACQUIRE:
            strName = "ACQUIRE";
            outputVC = m_acquireSpeed;
            break;
        case VCONVEYOR_EXPEL:
            strName = "EXPEL";
            outputVC = m_expelSpeed;
            break;
        case VCONVEYOR_EXPEL_FAST:
            strName = "EXPEL_FAST";
            outputVC = m_expelSpeedFast;
            break;
    }

    spdlog::info("Vertical Conveyor Set Speed - {}", strName);

    if (m_talonValidVC9)
        m_motorVC9.Set(ControlMode::PercentOutput, outputVC);
}
