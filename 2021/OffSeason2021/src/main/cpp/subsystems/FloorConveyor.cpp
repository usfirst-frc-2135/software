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
#include "subsystems/FloorConveyor.h"

#include <frc/smartdashboard/SmartDashboard.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

FloorConveyor::FloorConveyor()
{
    SetName("Floor Conveyor");
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Floor Conveyor");

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidFC8 = frc2135::TalonUtils::TalonCheck(m_motorFC8, "FC", "FC8");

    // Initialize Variables
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("FC_AcquireSpeed", m_acquireSpeed, 1.0);
    config->GetValueAsDouble("FC_ExpelSpeed", m_expelSpeed, 0.2);
    config->GetValueAsDouble("FC_ExpelSpeedFast", m_expelSpeedFast, -1.0);

    // Set motor directions
    // Turn on Coast mode (not brake)
    // Initialize modes and set power to off
    if (m_talonValidFC8)
    {
        m_motorFC8.SetInverted(false);
        m_motorFC8.SetNeutralMode(NeutralMode::Coast);
        m_motorFC8.Set(ControlMode::PercentOutput, 0.0);

        SupplyCurrentLimitConfiguration supplyCurrentLimits;
        supplyCurrentLimits = { true, 45.0, 45.0, 0.001 };
        m_motorFC8.ConfigSupplyCurrentLimit(supplyCurrentLimits);
    }

    Initialize();
}

void FloorConveyor::Periodic()
{
    static int periodicInterval = 0;

    // Put code here to be run every 20 ms loop

    // Only update indicators every 100 ms to cut down on network traffic
    if (periodicInterval++ % 5 == 0)
    {
        double outputFC8;

        outputFC8 = (m_talonValidFC8) ? m_motorFC8.GetMotorOutputPercent() : 0.0;
        frc::SmartDashboard::PutNumber("FC_Output_FC8", outputFC8);

        if (m_conveyorDebug > 0)
        {
            double currentFC8;

            currentFC8 = (m_talonValidFC8) ? m_motorFC8.GetOutputCurrent() : 0.0;
            frc::SmartDashboard::PutNumber("FC_Current_FC8", currentFC8);
        }
    }
}

void FloorConveyor::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// Put methods for controlling this subsystem
// here. Call these from Commands.

void FloorConveyor::Initialize(void)
{
    spdlog::info("FC Init");
    SetFloorConveyorSpeed(FCONVEYOR_STOP);
}

//    Dump all Talon faults
void FloorConveyor::FaultDump(void)
{
    frc2135::TalonUtils::TalonFaultDump("FC 8", m_motorFC8);
}

// Set mode of floor conveyor
void FloorConveyor::SetFloorConveyorSpeed(int mode)
{
    const char *strName;
    double outputFC = 0.0; // Default: off

    switch (mode)
    {
        default:
        case FCONVEYOR_STOP:
            strName = "STOP";
            outputFC = 0.0;
            break;
        case FCONVEYOR_ACQUIRE:
            strName = "ACQUIRE";
            outputFC = m_acquireSpeed;
            break;
        case FCONVEYOR_EXPEL:
            strName = "EXPEL";
            outputFC = m_expelSpeed;
            break;
        case FCONVEYOR_EXPEL_FAST:
            strName = "EXPEL_FAST";
            outputFC = m_expelSpeedFast;
            break;
    }

    spdlog::info("FC Set Speed - {}", strName);

    if (m_talonValidFC8)
        m_motorFC8.Set(ControlMode::PercentOutput, outputFC);
}
