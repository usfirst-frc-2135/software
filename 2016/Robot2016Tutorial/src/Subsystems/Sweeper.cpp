// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Sweeper.h"
#include "../RobotMap.h"
#include "../Robot.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Sweeper::Sweeper() : Subsystem("Sweeper") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorAcquire = RobotMap::sweeperMotorAcquire;
    indexerAcquire = RobotMap::sweeperIndexerAcquire;
    extension = RobotMap::sweeperExtension;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    //Initialize extend/retract
    Extend(false);						// Retracted
    m_sweeperSpeed = 0.9;
}

void Sweeper::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Sweeper::Initialize(Preferences *prefs) {
	printf("2135: Sweeper Initialize\n");

	//Initialize and read file

	// Ensure Talons are in proper coast/brake mode
    motorAcquire->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
    indexerAcquire->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Brake);

    // Initialize motor speeds
    m_sweeperSpeed = Robot::LoadPreferencesVariable("SweepSpeed", 0.8);
    SmartDashboard::PutNumber("SweepSpeed", m_sweeperSpeed );

    SetMotorSpeed(0);					// Sweeper motor off
    SetIndexerSpeed(0);					// Indexer motor off
}

void Sweeper::Extend(bool extend) {
	if (extend) {
		extension->Set(extension->kForward);
	}
	else {
		extension->Set(extension->kReverse);
	}
}


void Sweeper::SetMotorSpeed(int setting) {
	double speed;

	switch ( setting )
	{
	case SWEEPER_FORWARD:
		speed = m_sweeperSpeed;
		break;
	case SWEEPER_REVERSE:
		speed = -m_sweeperSpeed;
		break;
	case SWEEPER_STOP:
	default:
		speed = 0.0;
		break;
	}
	motorAcquire->Set(speed);
}

void Sweeper::SetIndexerSpeed(int setting) {
	double speed;

	switch ( setting )
	{
	case INDEXER_FORWARD:
		speed = m_sweeperSpeed;
		break;
	case INDEXER_REVERSE:
		speed = -m_sweeperSpeed;
		break;
	case INDEXER_STOP:
	default:
		speed = 0.0;
		break;
	}
	indexerAcquire->Set(speed);
}
