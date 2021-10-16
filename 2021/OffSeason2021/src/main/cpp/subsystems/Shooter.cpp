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
#include "subsystems/Shooter.h"

#include <frc/smartdashboard/SmartDashboard.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Shooter::Shooter()
{
    SetName("Shooter");
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Shooter");

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    // Validate Talon FX controllers, initialize and display firmware versions
    m_talonValidSH10 = frc2135::TalonUtils::TalonCheck(m_motorSH10, "SH", "SH10");
    m_talonValidSH11 = frc2135::TalonUtils::TalonCheck(m_motorSH11, "SH", "SH11");

    // Initialize Variables
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("SH_flywheelPidKf", m_flywheelPidKf, 0.0475);
    config->GetValueAsDouble("SH_flywheelPidKp", m_flywheelPidKp, 0.0);
    config->GetValueAsDouble("SH_flywheelPidKi", m_flywheelPidKi, 0.0);
    config->GetValueAsDouble("SH_flywheelPidKd", m_flywheelPidKd, 0.0);
    config->GetValueAsDouble("SH_flywheelNeutralDeadband", m_flywheelNeutralDeadband, 0.004);

    config->GetValueAsDouble("SH_feederPidKf", m_feederPidKf, 0.0475);
    config->GetValueAsDouble("SH_feederPidKp", m_feederPidKp, 0.0);
    config->GetValueAsDouble("SH_feeerPidKi", m_feederPidKi, 0.0);
    config->GetValueAsDouble("SH_feederPidKd", m_feederPidKd, 0.0);
    config->GetValueAsDouble("SH_feederNeutralDeadband", m_feederNeutralDeadband, 0.004);

    config->GetValueAsDouble("SH_FlywheelRPM", m_FlywheelTargetRPM);
    config->GetValueAsDouble("SH_FeederRPM", m_FeederTargetRPM);

    if (m_talonValidSH10)
    {
        // Set motor directions
        // Turn on Coast mode
        m_motorSH10.SetInverted(true);
        m_motorSH10.SetNeutralMode(NeutralMode::Coast);
        m_motorSH10.SetSafetyEnabled(false);

        // Enable voltage compensation
        m_motorSH10.ConfigVoltageCompSaturation(12.0, kCANTimeout);
        m_motorSH10.EnableVoltageCompensation(true);
        m_motorSH10.ConfigNeutralDeadband(m_feederNeutralDeadband, kCANTimeout);
        m_motorSH10.ConfigPeakOutputReverse(0.0, kCANTimeout);

        SupplyCurrentLimitConfiguration supplyCurrentLimits;
        supplyCurrentLimits = { true, 45.0, 45.0, 0.001 };

        StatorCurrentLimitConfiguration statorCurrentLimits;
        statorCurrentLimits = { true, 80.0, 80.0, 0.001 };

        m_motorSH10.ConfigSupplyCurrentLimit(supplyCurrentLimits);
#ifdef __FRC_ROBORIO__
        m_motorSH10.ConfigStatorCurrentLimit(statorCurrentLimits);
#endif

        // Configure sensor settings
        m_motorSH10.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, kPidIndex, kCANTimeout);
        m_motorSH10.SetSensorPhase(true);
        m_motorSH10.SetSelectedSensorPosition(0, kPidIndex, kCANTimeout);

        // Configure Velocity PIDF settings
        m_motorSH10.SelectProfileSlot(0, 0);
        m_motorSH10.Config_kF(0, m_feederPidKf, kCANTimeout);
        m_motorSH10.Config_kP(0, m_feederPidKp, kCANTimeout);
        m_motorSH10.Config_kI(0, m_feederPidKi, kCANTimeout);
        m_motorSH10.Config_kD(0, m_feederPidKd, kCANTimeout);

        m_motorSH10.Set(ControlMode::Velocity, 0.0);
    }

    if (m_talonValidSH11)
    {
        // Set motor directions
        // Turn on Coast mode
        m_motorSH11.SetInverted(true);
        m_motorSH11.SetNeutralMode(NeutralMode::Coast);
        m_motorSH11.SetSafetyEnabled(false);

        // Enable voltage compensation
        m_motorSH11.ConfigVoltageCompSaturation(12.0, kCANTimeout);
        m_motorSH11.EnableVoltageCompensation(true);
        m_motorSH11.ConfigNeutralDeadband(m_flywheelNeutralDeadband, kCANTimeout);
        m_motorSH11.ConfigPeakOutputReverse(0.0, kCANTimeout);

        SupplyCurrentLimitConfiguration supplyCurrentLimits;
        supplyCurrentLimits = { true, 45.0, 45.0, 0.001 };

        StatorCurrentLimitConfiguration statorCurrentLimits;
        statorCurrentLimits = { true, 80.0, 80.0, 0.001 };

        m_motorSH11.ConfigSupplyCurrentLimit(supplyCurrentLimits);
#ifdef __FRC_ROBORIO__
        m_motorSH11.ConfigStatorCurrentLimit(statorCurrentLimits);
#endif

        // Configure sensor settings
        m_motorSH11.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, kPidIndex, kCANTimeout);
        m_motorSH11.SetSensorPhase(true);
        m_motorSH11.SetSelectedSensorPosition(0, kPidIndex, kCANTimeout);

        // Configure Velocity PIDF settings
        m_motorSH11.SelectProfileSlot(0, 0);
        m_motorSH11.Config_kF(0, m_flywheelPidKf, kCANTimeout);
        m_motorSH11.Config_kP(0, m_flywheelPidKp, kCANTimeout);
        m_motorSH11.Config_kI(0, m_flywheelPidKi, kCANTimeout);
        m_motorSH11.Config_kD(0, m_flywheelPidKd, kCANTimeout);

        m_motorSH11.Set(ControlMode::Velocity, 0.0);
    }

    frc::SmartDashboard::PutNumber("SH_FeederPidKf", m_feederPidKf);
    frc::SmartDashboard::PutNumber("SH_FeederPidKp", m_feederPidKp);
    frc::SmartDashboard::PutNumber("SH_FeederPidKi", m_feederPidKi);
    frc::SmartDashboard::PutNumber("SH_FeederPidKd", m_feederPidKd);

    frc::SmartDashboard::PutNumber("SH_FlywheelPidKf", m_flywheelPidKf);
    frc::SmartDashboard::PutNumber("SH_FlywheelPidKp", m_flywheelPidKp);
    frc::SmartDashboard::PutNumber("SH_FlywheelPidKi", m_flywheelPidKi);
    frc::SmartDashboard::PutNumber("SH_FlywheelPidKd", m_flywheelPidKd);

    frc::SmartDashboard::PutNumber("SH_FeederSmartDashRPM", m_FeederCurrentRPM);
    frc::SmartDashboard::PutNumber("SH_FlywheelSmartDashRPM", m_FlywheelCurrentRPM);

    Initialize();
}

void Shooter::Periodic()
{
    static int periodicInterval = 0;
    // Put code here to be run every loop

    // Only update indicators every 100 ms to cut down on network traffic
    if (periodicInterval++ % 5 == 0)
    {
        if (m_talonValidSH10)
        {
            m_FeederCurrentRPM =
                m_feederFilter.Calculate(NativeToFeederRPM(m_motorSH10.GetSelectedSensorVelocity(kPidIndex)));
        }

        if (m_talonValidSH11)
        {
            m_FlywheelCurrentRPM = m_flywheelFilter.Calculate(
                NativeToFlywheelRPM(m_motorSH11.GetSelectedSensorVelocity(kPidIndex)));
        }

        frc::SmartDashboard::PutNumber("SH_FeederRPM", m_FeederCurrentRPM);
        frc::SmartDashboard::PutNumber("SH_FlywheelRPM", m_FlywheelCurrentRPM);

        if (m_FlywheelTargetRPM > 50)
        {
            spdlog::info("SH_FeederRPM {} SH_FlywheelRPM {}", m_FeederCurrentRPM, m_FlywheelCurrentRPM);
        }

        // Show current drain and slave output if more debugging is needed
        if (m_shooterDebug > 0)
        {
            double currentSH10 = 0.0;
            double currentSH11 = 0.0;

            if (m_talonValidSH10)
            {
                currentSH10 = m_motorSH10.GetOutputCurrent();
            }

            if (m_talonValidSH11)
            {
                currentSH11 = m_motorSH11.GetOutputCurrent();
            }

            frc::SmartDashboard::PutNumber("SH_Current_SH10", currentSH10);
            frc::SmartDashboard::PutNumber("SH_Current_SH11", currentSH11);
        }
    }
}

void Shooter::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation
    m_feederSim.SetInputVoltage(1_V * m_motorSH10.Get() * frc::RobotController::GetInputVoltage());
    m_flywheelSim.SetInputVoltage(1_V * m_motorSH11.Get() * frc::RobotController::GetInputVoltage());

    m_feederSim.Update(20_ms);
    m_flywheelSim.Update(20_ms);

    m_feederEncoderSim.SetDistance(m_feederSim.GetAngularVelocity().to<double>());
    m_flywheelEncoderSim.SetDistance(m_flywheelSim.GetAngularVelocity().to<double>());
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Initialize(void)
{
    spdlog::info("SH Init");
    SetShooterSpeed(SHOOTERSPEED_STOP);
}

void Shooter::FaultDump(void)
{
    //    Dump all Talon faults
    if (m_talonValidSH10)
        frc2135::TalonUtils::TalonFaultDump("SH 10", m_motorSH10);
    if (m_talonValidSH11)
        frc2135::TalonUtils::TalonFaultDump("SH 11", m_motorSH11);
}

double Shooter::FlywheelRPMToNative(double rpm)
{
    // Phoenix native encoder units are CPR / 100 msec
    return (rpm * kFlywheelCPR) / (60.0 * 10.0);
}

double Shooter::NativeToFlywheelRPM(double native)
{
    // Phoenix native encoder units are CPR / 100 msec
    return (native * 60.0 * 10.0) / kFlywheelCPR;
}

double Shooter::FeederRPMToNative(double rpm)
{
    return (rpm * kFeederCPR) / (60.0 * 10.0);
}

double Shooter::NativeToFeederRPM(double native)
{
    // Phoenix native encoder units are CPR / 100 msec
    return (native * 60 * 10) / kFeederCPR;
}

void Shooter::SetShooterSpeed(int state)
{
    spdlog::info("Shooter State {}", state);

    // // Validate and set the requested position to move
    switch (state)
    {
        case SHOOTERSPEED_STOP:
            m_FeederTargetRPM = 0.0;
            m_FlywheelTargetRPM = 0.0;
            break;
        case SHOOTERSPEED_FORWARD:
            m_FeederTargetRPM = 3000;
            m_FlywheelTargetRPM = 3000;
            break;
        case SHOOTERSPEED_SMARTDASH:
            m_FeederTargetRPM = frc::SmartDashboard::GetNumber("SH_FeederSmartDashRPM", 0.0);
            m_FlywheelTargetRPM = frc::SmartDashboard::GetNumber("SH_FlywheelSmartDashRPM", 0.0);
            break;
        default:
            spdlog::warn("SH invalid velocity requested - {}", state);
            return;
    }

    m_feederPidKf = frc::SmartDashboard::PutNumber("SH_FeederPidKf", m_feederPidKf);
    m_feederPidKp = frc::SmartDashboard::PutNumber("SH_FeederPidKp", m_feederPidKp);
    m_feederPidKi = frc::SmartDashboard::PutNumber("SH_FeederPidKi", m_feederPidKi);
    m_feederPidKd = frc::SmartDashboard::PutNumber("SH_FeederPidKd", m_feederPidKd);

    m_flywheelPidKf = frc::SmartDashboard::PutNumber("SH_FlywheelPidKf", m_flywheelPidKf);
    m_flywheelPidKp = frc::SmartDashboard::PutNumber("SH_FlywheelPidKp", m_flywheelPidKp);
    m_flywheelPidKp = frc::SmartDashboard::PutNumber("SH_FlywheelPidKi", m_flywheelPidKi);
    m_flywheelPidKd = frc::SmartDashboard::PutNumber("SH_FlywheelPidKd", m_flywheelPidKd);

    if (m_talonValidSH10)
    {
        m_motorSH10.Config_kF(0, m_feederPidKf, 0);
        m_motorSH10.Config_kP(0, m_feederPidKp, 0);
        m_motorSH10.Config_kI(0, m_feederPidKi, 0);
        m_motorSH10.Config_kD(0, m_feederPidKd, 0);
    }

    if (m_talonValidSH11)
    {
        m_motorSH11.Config_kF(0, m_flywheelPidKf, 0);
        m_motorSH11.Config_kP(0, m_flywheelPidKp, 0);
        m_motorSH11.Config_kI(0, m_flywheelPidKi, 0);
        m_motorSH11.Config_kD(0, m_flywheelPidKd, 0);
    }

    // Get current position in inches and set position mode and target counts
    if (m_talonValidSH10)
    {
        m_motorSH10.Set(ControlMode::Velocity, FeederRPMToNative(m_FeederTargetRPM));
    }

    if (m_talonValidSH11)
    {
        m_motorSH11.Set(ControlMode::Velocity, FlywheelRPMToNative(m_FlywheelTargetRPM));
    }

    spdlog::info("SH Set shooter speed - feeder {} flywheel {}", m_FeederTargetRPM, m_FlywheelTargetRPM);
}

void Shooter::FlashlightOn(bool onState)
{
    spdlog::info("Shooter Flashlight {}", (onState) ? "ON" : "OFF");
    frc::SmartDashboard::PutBoolean("Flashlight_State", onState);

    m_flashlight.Set(onState);
}

bool Shooter::AtDesiredRPM()
{
    bool atDesiredSpeed = (fabs(m_FlywheelTargetRPM - m_FlywheelCurrentRPM) < 200.0);

    if (atDesiredSpeed)
    {
        spdlog::info("RPM at Speed {}", atDesiredSpeed);
    }

    return atDesiredSpeed;
}
