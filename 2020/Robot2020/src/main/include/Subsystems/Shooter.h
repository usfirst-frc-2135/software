// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#pragma once

#include <frc/commands/Subsystem.h>

// TODO: Do we need to add this into autogenerated code?
#include "frc/controller/SimpleMotorFeedforward.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "ctre/Phoenix.h"
#include "frc/DoubleSolenoid.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author ExampleAuthor
 */
class Shooter: public frc::Subsystem
{

private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorSH10;
	std::shared_ptr<WPI_TalonSRX> motorSH11;
	std::shared_ptr<frc::DoubleSolenoid> indexer;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Declare constants
    const int       m_shooterDebug = 1;                // DEBUG flag to disable/enable extra logging calls
    const int       kPidIndex = 0;                    // PID slot index for sensors
    const int       kCANTimeout = 30;                // CAN timeout in msec to wait for response
    const double    kFlywheelCPR = (1024*4);        // CPR is 1024 and multipled by 4 because it is a quadrature encoder
    const double    kFlywheelMaxRPM = 5200;        // Measured max RPM with two mini-CIMs
    const int       kFlywheelMaxVelNative = ((int) ((kFlywheelMaxRPM * kFlywheelCPR) / (60 * 10)));

    // Declare module variables
    bool            m_talonValidSH10;            // Health indicator for shooter talon 10
    bool            m_talonValidSH11;            // Health indicator for shooter talon 11

    int             m_shooterLevel;                // Current shooter speed level
    double          m_targetOutput;                // Target output
    double          m_targetVelocityRPM;        // Target shooter velocity in RPM
    double          m_targetVelocityNative;        // Target shooter velcoity in native units per 100 ms
    double          m_curVelocityRPM;            // Current shooter velocity in RPM

    frc::SimpleMotorFeedforward<units::meter> m_feedforward; // Shooter feedforward calculator

    // Configuration file parameters
    double          m_fwdOutput;
    double          m_revOutput;

    double          m_pidKf;                    // Shooter PID force constant
    double          m_pidKp;                    // Shooter PID proportional constant
    double          m_pidKi;                    // Shooter PID integral constant
    double          m_pidKd;                    // Shooter PID derivative constant
    double          m_neutralDeadband;            // Shooter PID neutral deadband in percent
    double          m_ffKs;                        // Feedforward kS
    double          m_ffKv;                        // Feedforward kV
    double          m_ffKa;                        // Feedforward kA

    // Conversion functions between RPM and Output and CTRE Native Units / 100ms
    double RpmToNative(double rpm);
    double NativeToRpm(double native);
    double OutputToRpm(double output);

public:
    Shooter();
    void InitDefaultCommand() override;
    void Periodic() override;

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // Shooter motor control states
    typedef enum shooterSpeed_e
    {
        SHOOTERSPEED_STOP       = 0,        // Stop shooter
        SHOOTERSPEED_FORWARD    = 1,        // Shooter velocity
        SHOOTERSPEED_REVERSE    = -1,       // Shooter reverse
        SHOOTERSPEED_SMARTDASH  = 2
    } shooterSpeed_e;

    void Initialize(void);
    void FaultDump(void);

    void SetShooterSpeedInit(int speed);
    void IndexerDeploy(bool state);
};
