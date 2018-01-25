// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ctre/Phoenix.h"


#include "Elevator.h"
#include "../RobotMap.h"
#include "../Commands/ElevatorRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevator::Elevator() : frc::Subsystem("Elevator") {
#ifdef ROBOTNOTSTANDALONE
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL11 = RobotMap::elevatorMotorL11;
    motorR12 = RobotMap::elevatorMotorR12;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    motorL11->SetInverted(false);			// Sets the Talon invertion to false
    motorR12->SetInverted(false);			// Sets the Talon invertion to false

    // Set the control mode and target;
    motorL11->Set(ControlMode::Position, 0.0);
    motorR12->Set(ControlMode::Follower, 11);

    // Set to brake mode (in comparison to coast)
    motorL11->SetNeutralMode(NeutralMode::Brake);
    motorR12->SetNeutralMode(NeutralMode::Brake);

#endif
}

void Elevator::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
#ifdef ROBOTNOTSTANDALONE
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ElevatorRun(false));

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
#endif
}

void Elevator::Periodic() {
    // Put code here to be run every loop

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::ElevatePIDInit(double inches) {
#ifdef ROBOTNOTSTANDALONE
	double m_target = inches / (4.0 * M_PI / COUNTS_PER_ROTATION);
	// Initialize encoders to start at zero
	motorL11->SetSelectedSensorPosition(0, pidIndex, timeout);

	// Set closed loop error
	motorL11->ConfigAllowableClosedloopError(0, 10, timeout);

	// Set power and timeout
	motorL11->ConfigPeakOutputForward(0.25, timeout);
	motorL11->ConfigPeakOutputReverse(-0.25, timeout);

	// Set proportional
	motorL11->Config_kP(0, 0.25/COUNTS_PER_ROTATION, timeout);

	// Set the mode and target
	motorL11->Set(ControlMode::Position, m_target);

	motorL11->SetSafetyEnabled(false);
#endif
}

void Elevator::ElevatePIDExecute() {
	// Nothing here because this will be done in the talon
}

bool Elevator::ElevatePIDatSetPoint() {
	bool pidFinished = false;
	int closedLoopError = 1;	// initialized for ROBOTNOTSTANDALONE mode

	// Detect if closed loop error has been updated
#ifdef ROBOTNOTSTANDALONE
	closedLoopError = motorL11->GetClosedLoopError(0);
#endif

	// Check if it is within tolerance
	if (abs(closedLoopError) <= 0.0) { // TODO: Change this to get the tolerance
		pidFinished = true;
	}

	return pidFinished;
}

void Elevator::ElevatePIDStop() {
#ifdef ROBOTNOTSTANDALONE
	// Set the driving mode and target
	motorL11->Set(ControlMode::Position, 0.0);

	motorL11->SetSafetyEnabled(false);

#endif

}
