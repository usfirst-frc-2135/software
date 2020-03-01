// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <Subsystems/Shooter.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <frc2135/TalonUtils.h>
#include <frc2135/RobotConfig.h>


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/ShooterRun.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Shooter::Shooter() : frc::Subsystem("Shooter") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
motorSH10.reset(new WPI_TalonSRX(10));


motorSH11.reset(new WPI_TalonSRX(11));


shooterIndexer.reset(new frc::Solenoid(0, 6));
AddChild("Shooter Indexer", shooterIndexer);


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS


    // Validate Talon SRX controllers, initialize and display firmware versions
     m_talonValidSH10 = frc2135::TalonUtils::TalonCheck(motorSH10, "SH", "SH10");
     m_talonValidSH11 = frc2135::TalonUtils::TalonCheck(motorSH11, "SH", "SH11");

    // Check if solenoid is functional or blacklisted
     if (shooterIndexer->IsBlackListed())
        std::printf("2135: ERROR: SH Shooter Indexer FWD Solenoid is BLACKLISTED\n");
     else
        std::printf("2135: SH Shooter Indexer FWD Solenoid is FUNCTIONAL\n");

    // Initialize Variables
     frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
     config->GetValueAsDouble("SH_OnSpeed", m_onSpeed, 60.0);
     config->GetValueAsDouble("SH_ReverseSpeed", m_reverseSpeed, -20.0);
     config->GetValueAsDouble("SH_FwdOutput", m_fwdOutput, 0.75);
     config->GetValueAsDouble("SH_RevOutput", m_revOutput, -0.25);
     config->GetValueAsDouble("SH_PidKf", m_pidKf, 0.427);
     config->GetValueAsDouble("SH_PidKp", m_pidKp, 0.250);
     config->GetValueAsDouble("SH_PidKi", m_pidKi, 0.000);
     config->GetValueAsDouble("SH_PidKd", m_pidKd, 0.000);
     config->GetValueAsDouble("SH_NeutralDeadband", m_neutralDeadband, 0.004);

     frc::SmartDashboard::PutNumber("SH_SmartDashSpeed", 0);
     m_smartDashSpeed = frc::SmartDashboard::GetNumber("SH_SmartDashSpeed", 0);

     frc::SmartDashboard::PutNumber("SH_SmartDashOutput", 0);
     m_smartDashOutput = frc::SmartDashboard::GetNumber("SH_SmartDashOutput", 0);

    // Initialize modes and set power to off
    // Set motor peak outputs
    if (m_talonValidSH10) {
        // Set motor directions
        // Turn on Coast mode
        motorSH10->SetInverted(false);
        motorSH10->SetNeutralMode(NeutralMode::Coast);
        motorSH10->SetSafetyEnabled(false);

        // Enable voltage compensation
        motorSH10->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorSH10->EnableVoltageCompensation(true);
        motorSH10->ConfigNeutralDeadband(m_neutralDeadband, m_timeout);

        // Configure sensor settings
        motorSH10->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorSH10->SetSensorPhase(false);
        motorSH10->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

		// Configure Velocity PIDF settings
		motorSH10->SelectProfileSlot(0, 0);
        motorSH10->Config_kF(0, m_pidKf, m_timeout);
        motorSH10->Config_kP(0, m_pidKp, m_timeout);
        motorSH10->Config_kI(0, m_pidKi, m_timeout);
        motorSH10->Config_kD(0, m_pidKd, m_timeout);

        motorSH10->Set(ControlMode::PercentOutput, 0.0);
    }

    if (m_talonValidSH11) {
        motorSH11->Set(ControlMode::Follower, 10);                  // Set to follow Shooter Motor 10
        motorSH11->SetInverted(InvertType::OpposeMaster);           // Sets the Talon inversion to true
        motorSH11->SetNeutralMode(NeutralMode::Coast);              // Set to coast mode
        motorSH11->SetSafetyEnabled(false);

        // Enable voltage compensation
        motorSH11->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorSH11->EnableVoltageCompensation(true);
        motorSH11->ConfigNeutralDeadband(m_neutralDeadband, m_timeout);
    }

    Initialize ();
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ShooterRun(0));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Shooter::Periodic() {
    // Put code here to be run every loop

    // Show the status of the shooter and talons in SmartDashboard.
    if (m_shooterDebug > 0) {
        double outputSH10 = 0.0, currentSH10 = 0.0;
        double outputSH11 = 0.0, currentSH11 = 0.0;

        if (m_talonValidSH10) {
            outputSH10 = motorSH10->GetMotorOutputPercent();
            currentSH10 = motorSH10->GetOutputCurrent();
        }

        if (m_talonValidSH11) {
            outputSH11 = motorSH11->GetMotorOutputPercent();
            currentSH11 = motorSH11->GetOutputCurrent();
        }

        frc::SmartDashboard::PutNumber("SH_Output_SH10", outputSH10);
        frc::SmartDashboard::PutNumber("SH_Current_SH10", currentSH10);
        frc::SmartDashboard::PutNumber("SH_Output_SH11", outputSH11);
        frc::SmartDashboard::PutNumber("SH_Current_SH11", currentSH11);

        double curVelocityRPM = NativeToRpm(motorSH10->GetSelectedSensorVelocity(m_pidIndex));
        frc::SmartDashboard::PutNumber("SH_Velocity_RPM", curVelocityRPM);

        frc::SmartDashboard::PutNumber("SH_Indexer", shooterIndexer->Get());
    }
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Initialize(void) {
	std::printf("2135: SH Init\n");
	// Motor off
	 if (m_talonValidSH10)
		motorSH10->Set(ControlMode::PercentOutput, 0.0);
    m_targetVelocityRPM = 0.0;
}

void Shooter::FaultDump(void) {
	//	Dump all Talon faults
	 frc2135::TalonUtils::TalonFaultDump("SH 10", motorSH10);
     frc2135::TalonUtils::TalonFaultDump("SH 11", motorSH11);
}

double Shooter::RpmToNative(double rpm) {
	double 	native;
	native = (rpm*COUNTS_PER_ROTATION)/(60*10);
	return native;
}

double Shooter::NativeToRpm(double native) {
	double 	rpm;
	rpm = native*(60*10)/(COUNTS_PER_ROTATION);
	return 	rpm;
}

// Set mode of shooter
void Shooter::SetShooterMotorOutput(int direction) {
	// const char *strName;
	// double outputSH = 0.0; 		// Default: off

    // switch (direction)
	// {
	// default:
	// case SHOOTER_STOP:
	// 	strName = "STOP";
	// 	outputSH = 0.0;
    //     shooterIndexer->Set(false);
	// 	break;
	// case SHOOTER_FORWARD:
	// 	strName = "FORWARD";
	// 	outputSH = 0.75;
    //     shooterIndexer->Set(true);
	// 	break;
	// case SHOOTER_REVERSE:
	// 	strName = "REVERSE";
	// 	outputSH = -0.25;
    //     shooterIndexer->Set(true);
	// 	break;
	// }

    // std::printf("2135: Shooter Set Speed - %s\n", strName);

	// if (m_talonValidSH10)
	// 	motorSH10->Set(ControlMode::PercentOutput, outputSH);
}

void Shooter::SetShooterSpeedInit(int level) {
    double 	curVelocityNative = 0.0;
    double  shooterOutput = 0.0;

	m_shooterLevel = level;

	// Validate and set the requested position to move
	switch (level) {
	case STOP_SPEED:
		m_targetVelocityRPM = 0.0;
        shooterOutput = 0.0;
		break;
	case ON_SPEED:
		m_targetVelocityRPM = m_onSpeed;
        shooterOutput = m_fwdOutput;
		break;
	case REVERSE_SPEED:
		m_targetVelocityRPM = m_reverseSpeed;
        shooterOutput = m_revOutput;
		break;
    case SMARTDASH_SPEED:
         m_targetVelocityRPM = m_smartDashSpeed;
         shooterOutput = m_smartDashOutput;
         break;
	default:
		std::printf("2135: SH invalid velocity requested - %d\n", level);
		return;
	}

    m_targetVelocityNative = RpmToNative(m_targetVelocityRPM);

	// Get current position in inches and set position mode and target counts
	 if (m_talonValidSH10)
		curVelocityNative = motorSH10->GetSelectedSensorVelocity(m_pidIndex);
	 m_curVelocityRPM = NativeToRpm(curVelocityNative);

	// Start the safety timer.
	 m_safetyTimeout = 2.4;
	 m_safetyTimer.Reset();
	 m_safetyTimer.Start();

    motorSH10->Set(ControlMode::Velocity, m_targetVelocityNative);
	std::printf("2135: SH Velocity RPM %5.2f -> %5.2f Native Unit %5.2f-> %5.2f\n",
		m_curVelocityRPM, m_targetVelocityRPM, curVelocityNative, m_targetVelocityNative);

    // motorSH10->Set(ControlMode::PercentOutput, shooterOutput);
    // double curOutput = motorSH10->GetMotorOutputPercent();
    // std::printf("2135: SH Output %5.2f -> %5.2f\n", curOutput, shooterOutput);
    // TODO: Remove warning while stuff is commented out above
    shooterOutput = shooterOutput;
}

