// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Shooter.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Commands/ShootPresets.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Shooter::Shooter() : Subsystem("Shooter") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    lowerMotor = RobotMap::shooterLowerMotor;
    upperMotor = RobotMap::shooterUpperMotor;
    frameSolenoid = RobotMap::shooterFrameSolenoid;
    fireSolenoid = RobotMap::shooterFireSolenoid;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    lowerMotor->SetSafetyEnabled(false);
    upperMotor->SetSafetyEnabled(false);

    lowerMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);
    upperMotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);

    SetFrameControl(false);
    SetFireSolenoid(true);

    m_isPID = false;

    m_logFile = fopen("/home/lvuser/EncoderLog.csv", "w");
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ShootPresets(0));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Initialize(Preferences *prefs) {
	printf("2135: Shooter Initialize\n");

	SmartDashboard::PutNumber("ShootLow_Upper", Robot::LoadPreferencesVariable ("ShootLow_Upper", 0.75));
	SmartDashboard::PutNumber("ShootLow_Lower", Robot::LoadPreferencesVariable ("ShootLow_Lower", 0.5));
	SmartDashboard::PutNumber("ShootHigh_Upper", Robot::LoadPreferencesVariable ("ShootHigh_Upper", 0.95));
	SmartDashboard::PutNumber("ShootHigh_Lower", Robot::LoadPreferencesVariable ("ShootHigh_Lower", 0.7));

	SmartDashboard::PutNumber("Shoot Upper", 0.0);
	SmartDashboard::PutNumber("Shoot Lower", 0.0);

	SmartDashboard::PutNumber("Upper Encoder Velocity", upperMotor->GetEncVel());
	SmartDashboard::PutNumber("Lower Encoder Velocity", lowerMotor->GetEncVel());
	SmartDashboard::PutNumber("Upper PID Error", upperMotor->GetClosedLoopError());
	SmartDashboard::PutNumber("Lower PID Error", lowerMotor->GetClosedLoopError());

	SmartDashboard::PutBoolean("PIDMode", m_isPID);

	upperP = Robot::LoadPreferencesVariable ("Shooter_Upper_P", 0.007296);
	lowerP = Robot::LoadPreferencesVariable ("Shooter_Lower_P", 0.007296);

	upperI = Robot::LoadPreferencesVariable ("Shooter_Upper_I", 0.0);
	lowerI = Robot::LoadPreferencesVariable ("Shooter_Lower_I", 0.0);

	upperD = Robot::LoadPreferencesVariable ("Shooter_Upper_D", 0.0);
	lowerD = Robot::LoadPreferencesVariable ("Shooter_Lower_D", 0.0);

	upperMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
	upperMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	upperMotor->ConfigEncoderCodesPerRev(4096);
	upperMotor->SetSensorDirection(false);
	upperMotor->SetEncPosition(0);

	lowerMotor->SetControlMode(CANTalon::ControlMode::kPercentVbus);
	lowerMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	lowerMotor->ConfigEncoderCodesPerRev(4096);
	lowerMotor->SetSensorDirection(true);
	lowerMotor->SetEncPosition(0);

    lowerMotor->SetStatusFrameRateMs(CANTalon::StatusFrameRateQuadEncoder,20);
    upperMotor->SetStatusFrameRateMs(CANTalon::StatusFrameRateQuadEncoder,20);

	m_timer.Reset();
	m_timer.Start();

	m_encoder_timer.Reset();
	m_encoder_timer.Start();
}

void Shooter::SetMotorSpeeds(double upperSpeed, double lowerSpeed) {
//	fprintf(m_logFile,
//			"%f,%i,%i,%d,%d\n",
//			m_encoder_timer.Get(),
//			upperMotor->GetEncVel(),
//			lowerMotor->GetEncVel(),
//			upperMotor->GetClosedLoopError(),
//			lowerMotor->GetClosedLoopError());

	lowerMotor->Set(lowerSpeed*M_VELOCITY_PER_VBUS_PRCNT);
	upperMotor->Set(upperSpeed*M_VELOCITY_PER_VBUS_PRCNT);

	UpdateEncoderDisplays();
}

void Shooter::SetMotorDirection(bool isForward) {
	if (isForward) {
		lowerMotor->ConfigPeakOutputVoltage(0.0, -12.0);
		upperMotor->ConfigPeakOutputVoltage(12.0, 0.0);
	}

	else {
		lowerMotor->ConfigPeakOutputVoltage(12.0, 0.0);
		upperMotor->ConfigPeakOutputVoltage(0.0, -12.0);
	}
}

void Shooter::SetControlMode(void) {
	m_isPID = !m_isPID;
	SmartDashboard::PutBoolean("PIDMode", m_isPID);
}

void Shooter::ShootStartMode(void) {
	if (m_isPID == true) {
		printf("2135: Shooter PID Mode\n");
		upperMotor->SetF(.033901);
		upperMotor->SetPID(upperP,upperI,upperD);
		upperMotor->SetControlMode(CANSpeedController::ControlMode::kSpeed);
		upperMotor->ConfigPeakOutputVoltage(12.0,0.0);

		lowerMotor->SetF(.033901);
		lowerMotor->SetPID(lowerP,lowerI,lowerD);
		lowerMotor->SetControlMode(CANSpeedController::ControlMode::kSpeed);
		lowerMotor->ConfigPeakOutputVoltage(0.0,-12.0);
	}
}

void Shooter::ShootFinishMode(void) {
	if (m_isPID == true) {
		printf("2135: Shooter %%Vbus Mode\n");
		upperMotor->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
		lowerMotor->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	}
}

void Shooter::SetFireSolenoid(bool fire) {
	if (m_frameUpState) {
		m_fireState = fire;
		if (fire) {
			fireSolenoid->Set(DoubleSolenoid::kForward);
		}
		else {
			fireSolenoid->Set(DoubleSolenoid::kReverse);
		}
	}
}

void Shooter::SetFireSolenoidUnsafe(bool fire) {
	if (fire) {
		fireSolenoid->Set(DoubleSolenoid::kForward);
	}
	else{
		fireSolenoid->Set(DoubleSolenoid::kReverse);
	}
}

bool Shooter::GetFireSolenoid(void) {
	return m_fireState;
}

void Shooter::SetFrameControl(bool frameUp) {
	m_frameUpState = frameUp;
	if (frameUp) {
		frameSolenoid->Set(frameSolenoid->kForward);
	}
	else {
		frameSolenoid->Set(frameSolenoid->kReverse);
	}
}

void Shooter::UpdateEncoderDisplays( void )
{
	static int updateCounter;			// Counter for updating encoder values

	// Update SmartDashboard values - Each counter tick is 20msec
//	printf("2135: Upper Motor Speed: %i \n", upperMotor->GetEncVel());
//	printf("2135: Lower Motor Speed: %i \n", lowerMotor->GetEncVel());
	if (updateCounter % 5 == 0)
	{
		SmartDashboard::PutNumber("Upper Encoder Velocity", (double) upperMotor->GetEncVel());
		SmartDashboard::PutNumber("Lower Encoder Velocity", (double) lowerMotor->GetEncVel());

		SmartDashboard::PutNumber("Upper Encoder Position", (double) upperMotor->GetEncPosition());
		SmartDashboard::PutNumber("Lower Encoder Position", (double) lowerMotor->GetEncPosition());

		SmartDashboard::PutNumber("Upper PID Error", upperMotor->GetClosedLoopError());
		SmartDashboard::PutNumber("Lower PID Error", lowerMotor->GetClosedLoopError());
	}

	updateCounter++;
}
