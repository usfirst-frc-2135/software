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

#include <frc/RobotController.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/Climber.h"

#include <frc/smartdashboard/SmartDashboard.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Climber::Climber()
{
    SetName("Climber");
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Climber");

    AddChild("Brake", &m_brake);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidCL14 = frc2135::TalonUtils::TalonCheck(m_motorCL14, "CL", "CL14");

    // Check if solenoids are functional or blacklisted
    if (m_brake.IsBlackListed())
        spdlog::error("CL Climber Solenoid is BLACKLISTED");
    else
        spdlog::info("CL Climber Solenoid is FUNCTIONAL");

    // Initialize Variables
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("CL_InitialUpSpeed", m_upSpeed, 1.0);
    config->GetValueAsDouble("CL_InitialDownSpeed", m_downSpeed, -0.2);

    // Set motor directions
    // Turn on Coast mode (not brake)
    // Set motor peak outputs
    if (m_talonValidCL14)
    {
        m_motorCL14.SetInverted(false);
        m_motorCL14.SetNeutralMode(NeutralMode::Coast);
        m_motorCL14.SetSafetyEnabled(false);

        m_motorCL14.ConfigVoltageCompSaturation(12.0, 0);
        m_motorCL14.EnableVoltageCompensation(true);
    }

    Initialize();
}

void Climber::Periodic()
{
    // Put code here to be run every loop
    static int periodicInterval = 0;

    // Only update indicators every 100 ms to cut down on network traffic
    if (periodicInterval++ % 5 == 0)
    {
        double outputCL14 = 0.0;

        if (m_talonValidCL14)
            outputCL14 = m_motorCL14.GetMotorOutputPercent();
        frc::SmartDashboard::PutNumber("CL_Output_CL14", outputCL14);

        if (m_climberDebug > 0)
        {
            double currentCL14 = 0.0;

            if (m_talonValidCL14)
                currentCL14 = m_motorCL14.GetOutputCurrent();

            frc::SmartDashboard::PutNumber("CL_Current_CL14", currentCL14);
        }
    }
}

void Climber::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Climber::Initialize(void)
{
    spdlog::info("CL Init");

    m_joystickCLZeroed = false;

    SetBrakeSolenoid(true);

    SetClimberStopped();
}

// Dump all Talon faults
void Climber::FaultDump(void)
{
    frc2135::TalonUtils::TalonFaultDump("CL 14", m_motorCL14);
}

// Raise climber with Joysticks method
void Climber::RaiseClimberWithJoysticks(frc::XboxController *joystick)
{
    double yCLValue = 0.0;
    double motorOutput = 0.0;

    yCLValue = joystick->GetY(frc::GenericHID::JoystickHand::kLeftHand);

    if (yCLValue > -0.1 && yCLValue < 0.1)
    {
        spdlog::info("Climber Stopped");
        SetBrakeSolenoid(CL_BRAKE_LOCKED);
    }
    else
    {
        SetBrakeSolenoid(CL_BRAKE_UNLOCKED);
        // If joystick is above a value, climber will move up
        if (yCLValue > 0.1)
            motorOutput = m_upSpeed;

        // If joystick is below a value, climber will move down
        else if (yCLValue < -0.1)
            motorOutput = m_downSpeed;
    }

    if (!m_talonValidCL14)
    {
        spdlog::info("Talon not valid");
    }
    else
    {
        m_motorCL14.Set(ControlMode::PercentOutput, motorOutput);
    }
}

void Climber::SetClimberStopped(void)
{
    spdlog::info("Set Climber Stopped");

    if (m_talonValidCL14)
        m_motorCL14.Set(ControlMode::PercentOutput, 0);
}

void Climber::SetBrakeSolenoid(bool braking)
{
    spdlog::info("CL {}", (braking) ? "STOPPED" : "NOT STOPPED");
    frc::SmartDashboard::PutBoolean("CL_Stopped", braking);

    m_brake.Set(braking);
}
