// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#pragma once
#include <frc/Encoder.h>
#include <frc/simulation/EncoderSim.h>
#include <frc/simulation/FlywheelSim.h>
#include <frc/system/plant/LinearSystemId.h>
#include <units/moment_of_inertia.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "ctre/Phoenix.h"

#include <frc2/command/SubsystemBase.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

using namespace units::length;
using namespace units::moment_of_inertia;

/**
 *
 *
 * @author ExampleAuthor
 */
class Shooter : public frc2::SubsystemBase
{
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities

#ifdef __FRC_ROBORIO__
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    WPI_TalonFX m_motorSH11{ 11 };
    WPI_TalonFX m_motorSH10{ 10 };

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#else
    WPI_TalonSRX m_motorSH10{ 10 };
    WPI_TalonSRX m_motorSH11{ 11 };
#endif

    // Sensors

    // Simulated quadrature encoders, since TalonFX is not supported
    frc::Encoder m_feederEncoder{ 5, 6 };
    frc::Encoder m_flywheelEncoder{ 7, 8 };
    frc::sim::EncoderSim m_feederEncoderSim{ m_feederEncoder };
    frc::sim::EncoderSim m_flywheelEncoderSim{ m_flywheelEncoder };
    frc::sim::FlywheelSim m_feederSim{
        frc::LinearSystemId::FlywheelSystem(frc::DCMotor::Falcon500(1), 1.0 * 1.0_kg_sq_m, 1.0),
        frc::DCMotor::Falcon500(1),
        1.5
    };
    frc::sim::FlywheelSim m_flywheelSim{
        frc::LinearSystemId::FlywheelSystem(frc::DCMotor::Falcon500(1), 1.0 * 1.0_kg_sq_m, 1.0),
        frc::DCMotor::Falcon500(1),
        1.5
    };

    const int m_shooterDebug = 1;              // DEBUG flag to disable/enable extra logging calls
    const int kPidIndex = 0;                   // PID slot index for sensors
    const double kFalconEncoderCPR = 2048;     // CPR is 2048 from Falcon 500 Manual
    const double kFeederGearRatio = (1.5 / 1); // Reduction of 1.5/1
    const double kFeederCPR = kFalconEncoderCPR * kFeederGearRatio;
    const double kFlywheelGearRatio = (1.0 / 1.0); // No reduction 1:1
    const double kFlywheelCPR = kFalconEncoderCPR * kFlywheelGearRatio;
    const int kCANTimeout = 30; // CAN timeout in msec to wait for response

    // Declare module variables
    bool m_talonValidSH10; // Health indicator for shooter talon 10
    bool m_talonValidSH11; // Health indicator for shooter talon 11

    //Configuration file parameters

    double m_pidKf;           // Shooter PID force constant
    double m_pidKp;           // Shooter PID proportional constant
    double m_pidKi;           // Shooter PID integral constant
    double m_pidKd;           // Shooter PID derivative constant
    double m_neutralDeadband; // Shooter PID neutral deadband in percent

    double m_FeederTargetRPM;
    double m_FlywheelTargetRPM;

    bool m_atDesiredSpeed;

    int m_shooterState; // Current shooter speed level

    double m_FlywheelCurrentRPM; // Current flywheel RPM
    double m_FeederCurrentRPM;   // Current feeder RPM

    // Conversion functions between RPM and Output and CTRE Native Units / 100ms
    double FlywheelRPMToNative(double rpm);
    double FeederRPMToNative(double rpm);
    double NativeToFlywheelRPM(double native);
    double NativeToFeederRPM(double native);

public:
    Shooter();

    void Periodic() override;
    void SimulationPeriodic() override;
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    typedef enum shooterSpeed_e
    {
        SHOOTERSPEED_STOP = 0,    // Stop shooter
        SHOOTERSPEED_FORWARD = 1, // Shooter velocity
        SHOOTERSPEED_SMARTDASH = 2
    } shooterSpeed_e;

    void Initialize(void);
    void FaultDump(void);

    void SetShooterSpeed(int state);
    void Aiming();
    bool AtDesiredRPM();
};
