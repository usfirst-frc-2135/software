// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <frc2135/RobotConfig.h>
#include <frc2135/TalonUtils.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/Shooter.h"
#include <frc/smartdashboard/SmartDashboard.h>

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Shooter::Shooter()
{
SetName("Shooter");
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Shooter");

 
 

 
 

 AddChild("Indexer", &m_indexer);
 

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidSH10 = frc2135::TalonUtils::TalonCheck(m_motorSH10, "SH", "SH10");
    m_talonValidSH11 = frc2135::TalonUtils::TalonCheck(m_motorSH11, "SH", "SH11");

    // Check if solenoid is functional or blacklisted
    if (m_indexer.IsFwdSolenoidBlackListed())
        std::printf("2135: ERROR: SH Shooter Indexer FWD Solenoid is BLACKLISTED\n");
    else if (m_indexer.IsRevSolenoidBlackListed())
        std::printf("2135: ERROR: SH Shooter Indexer REV Solenoid is BLACKLISTED\n");
    else
        std::printf("2135: SH Shooter Indexer FWD Solenoid is FUNCTIONAL\n");

    // Initialize Variables
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("SH_FwdOutput", m_fwdOutput, 0.80);
    config->GetValueAsDouble("SH_RevOutput", m_revOutput, -0.25);
    config->GetValueAsDouble("SH_PidKf", m_pidKf, 0.02305);
    config->GetValueAsDouble("SH_PidKp", m_pidKp, 0.01461);
    config->GetValueAsDouble("SH_PidKi", m_pidKi, 0.000);
    config->GetValueAsDouble("SH_PidKd", m_pidKd, 0.000);
    config->GetValueAsDouble("SH_NeutralDeadband", m_neutralDeadband, 0.004);
    config->GetValueAsDouble("SH_ffKs", m_ffKs, 1.06);
    config->GetValueAsDouble("SH_ffKv", m_ffKv, 0.12);
    config->GetValueAsDouble("SH_ffKa", m_ffKa, 0.0259);

    // Initialize modes and set power to off
    // Set motor peak outputs
    if (m_talonValidSH10)
    {
        // Set motor directions
        // Turn on Coast mode
        m_motorSH10.SetInverted(false);
        m_motorSH10.SetNeutralMode(NeutralMode::Coast);
        m_motorSH10.SetSafetyEnabled(false);

        // Enable voltage compensation
        m_motorSH10.ConfigVoltageCompSaturation(12.0, kCANTimeout);
        m_motorSH10.EnableVoltageCompensation(true);
        m_motorSH10.ConfigNeutralDeadband(m_neutralDeadband, kCANTimeout);

        // Configure sensor settings
        m_motorSH10.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPidIndex, kCANTimeout);
        m_motorSH10.SetSensorPhase(true);
        m_motorSH10.SetSelectedSensorPosition(0, kPidIndex, kCANTimeout);

        // Configure Velocity PIDF settings
        m_motorSH10.SelectProfileSlot(0, 0);
        m_motorSH10.Config_kF(0, m_pidKf, kCANTimeout);
        m_motorSH10.Config_kP(0, m_pidKp, kCANTimeout);
        m_motorSH10.Config_kI(0, m_pidKi, kCANTimeout);
        m_motorSH10.Config_kD(0, m_pidKd, kCANTimeout);

        m_motorSH10.Set(ControlMode::Velocity, 0.0);
    }

    if (m_talonValidSH11)
    {
        m_motorSH11.Set(ControlMode::Follower, 10);                  // Set to follow Shooter Motor 10
        m_motorSH11.SetInverted(InvertType::OpposeMaster);           // Sets the Talon inversion to true
        m_motorSH11.SetNeutralMode(NeutralMode::Coast);              // Set to coast mode
        m_motorSH11.SetSafetyEnabled(false);

        // Enable voltage compensation
        m_motorSH11.ConfigVoltageCompSaturation(12.0, kCANTimeout);
        m_motorSH11.EnableVoltageCompensation(true);
        m_motorSH11.ConfigNeutralDeadband(m_neutralDeadband, kCANTimeout);
    }

    Initialize ();
}

void Shooter::Periodic()
{
    static int  periodicInterval = 0;

    // Put code here to be run every loop

    // Only update indicators every 100 ms to cut down on network traffic
    if (periodicInterval++ % 5 == 0)
    {
        double outputSH10 = 0.0;
        double curVelocityNative = 0.0;
        double curVelocityRPM = 0.0;

        frc::SmartDashboard::PutNumber("SH_Indexer", m_indexer.Get());

        // Normal output is to show shooter output and speed
        if (m_talonValidSH10)
        {
            outputSH10 = m_motorSH10.GetMotorOutputPercent();
            curVelocityNative = m_motorSH10.GetSelectedSensorVelocity(kPidIndex);
            curVelocityRPM = NativeToRpm(curVelocityNative);

            frc::SmartDashboard::PutNumber("SH_Output_SH10", outputSH10);
            frc::SmartDashboard::PutNumber("SH_Velocity_RPM", curVelocityRPM);
        }

        // Show current drain and slave output if more debugging is needed
        if (m_shooterDebug > 0)
        {
            double currentSH10 = 0.0;
            double outputSH11 = 0.0;
            double currentSH11 = 0.0;

            if (m_talonValidSH10)
            {
                currentSH10 = m_motorSH10.GetOutputCurrent();
            }

            if (m_talonValidSH11)
            {
                outputSH11 = m_motorSH11.GetMotorOutputPercent();
                currentSH11 = m_motorSH11.GetOutputCurrent();
            }

            frc::SmartDashboard::PutNumber("SH_Current_SH10", currentSH10);
            frc::SmartDashboard::PutNumber("SH_Error_SH10", m_targetVelocityNative - curVelocityNative);

            frc::SmartDashboard::PutNumber("SH_Current_SH11", currentSH11);
            frc::SmartDashboard::PutNumber("SH_Output_SH11", outputSH11);
        }
    }
}

void Shooter::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Initialize(void)
{
    std::printf("2135: SH Init\n");
    if (m_talonValidSH10)
        m_motorSH10.Set(ControlMode::Velocity, 0.0);

    m_targetVelocityRPM = 0.0;

    /*
     * TODO: Make sure that the values of kV and kA are correct according to frc documentation
     * It expects angular or linear distances.
     */

    // Convert feedforward values to units SimpleMotorFeedforward requires
    auto kS = m_ffKs * 1_V;
    auto kV = m_ffKv * 1_V * 1_s / 1_m;
    auto kA = m_ffKa * 1_V * 1_s * 1_s / 1_m;

    // Create FeedForward calculator
    m_feedforward = frc::SimpleMotorFeedforward<units::meter>(kS, kV, kA);
}

void Shooter::FaultDump(void)
{
    //    Dump all Talon faults
    if (m_talonValidSH10)
        frc2135::TalonUtils::TalonFaultDump("SH 10", m_motorSH10);
    if (m_talonValidSH11)
        frc2135::TalonUtils::TalonFaultDump("SH 11", m_motorSH11);
}

double Shooter::RpmToNative(double rpm)
{
    // Phoenix native encoder units are CPR / 100 msec
    return (rpm * kFlywheelCPR) / (60 * 10);
}

double Shooter::NativeToRpm(double native)
{
    // Phoenix native encoder units are CPR / 100 msec
    return (native * 60 * 10) / kFlywheelCPR;
}

double Shooter::OutputToRpm(double output)
{
    return output * kFlywheelMaxRPM;
}

void Shooter::SetShooterSpeedInit(int level)
{
    double     curVelocityNative = 0.0;

    m_shooterLevel = level;

    // Validate and set the requested position to move
    switch (level)
    {
        case SHOOTERSPEED_STOP:
            m_targetOutput = 0.0;
            break;
        case SHOOTERSPEED_FORWARD:
            m_targetOutput = m_fwdOutput;
            break;
        case SHOOTERSPEED_REVERSE:
            m_targetOutput = m_revOutput;
            break;
        case SHOOTERSPEED_SMARTDASH:
            m_targetOutput = frc::SmartDashboard::GetNumber("SH_SmartDashOutput", 0.0);
            break;
        default:
            std::printf("2135: SH invalid velocity requested - %d\n", level);
            return;
    }

    m_targetVelocityRPM = OutputToRpm(m_targetOutput);
    m_targetVelocityNative = RpmToNative(m_targetVelocityRPM);

    // Get current position in inches and set position mode and target counts
    if (m_talonValidSH10)
    {
        curVelocityNative = m_motorSH10.GetSelectedSensorVelocity(kPidIndex);

        m_curVelocityRPM = NativeToRpm(curVelocityNative);

        // TODO: Units are definitely not right in the Calculate call
        // double ff_val = (double) m_feedforward.Calculate(m_curVelocityRPM * 1_m / 1_s);

        // TODO: Check if the ArbitraryFeedForward argument is being used correctly - (JLM) not really
        // m_motorSH10.Set(ControlMode::Velocity, m_targetVelocityNative, DemandType::DemandType_ArbitraryFeedForward, ff_val);
        // (JLM) If we use the WPILib calculation of FF, then it needs to use ControlMode::PercentOutput API
        // (JLM) Using the Talon SRX internal velocity mode which is preferred

        m_motorSH10.Set(ControlMode::Velocity, m_targetVelocityNative);
    }

    std::printf("2135: SH Velocity Output -> %5.2f RPM %5.2f -> %5.2f Native Unit %5.2f-> %5.2f\n",
        m_targetOutput, m_curVelocityRPM, m_targetVelocityRPM, curVelocityNative, m_targetVelocityNative);
}

void Shooter::IndexerDeploy(bool state)
{
    // If state is true, sets climber deploy forward, else reverse.
    m_indexer.Set( (state) ? m_indexer.kForward : m_indexer.kReverse);
}
