// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "Elevator.h"
#include "../RobotMap.h"
#include "../Commands/ElevatorIdle.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PID
Elevator::Elevator() : PIDSubsystem("Elevator", 1.0, 0.0, 0.0) {
	SetAbsoluteTolerance(0.2);
	GetPIDController()->SetContinuous(false);
	LiveWindow::GetInstance()->AddActuator("Elevator", "PIDSubsystem Controller", GetPIDController());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PID

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	motor6 = RobotMap::elevatorMotor6;
	motor7 = RobotMap::elevatorMotor7;
	heightPot = RobotMap::elevatorHeightPot;
	upperLimit = RobotMap::elevatorUpperLimit;
	lowerLimit = RobotMap::elevatorLowerLimit;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	motor7->SetControlMode(CANSpeedController::kFollower);
	motor7->Set(6);
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
}

void Elevator::SetNeutralMode( void )
{
	motor6->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	motor7->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
}

double Elevator::ReturnPIDInput() {
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;	
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=SOURCE
        return heightPot->Get();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=SOURCE
}

void Elevator::UsePIDOutput(double output) {
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=OUTPUT
	motor6->PIDWrite(output);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=OUTPUT
}

void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new ElevatorIdle());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Elevator::ElevatorRun(double speed) {
#if 0
	if (heightPot->Get() < 0.9 && heightPot->Get() > 0.1)
	{
		motor6->Set(speed);
	}
	else {
		motor6->Set(0.0);
	}
#endif
	motor6->Set(speed);
}


void Elevator::SetElevatorSpeed(double value )
{
	m_elevatorSpeed = value;
	printf("ElevatorSpeed:     %f\n", m_elevatorSpeed);
}

void Elevator::SetElevatorPidMin(double value )
{
	m_elevatorPidMin = value;
	printf("ElevatorPidMin:    %f\n", m_elevatorPidMin);
}

void Elevator::SetElevatorPidMax(double value )
{
	m_elevatorPidMax = value;
	printf("ElevatorPidMax:    %f\n", m_elevatorPidMax);

}

double Elevator::GetElevatorSpeed(void )
{
	return m_elevatorSpeed;
}

double Elevator::GetElevatorPidMin(void )
{
	return m_elevatorPidMin;
}

double Elevator::GetElevatorPidMax(void )
{
	return m_elevatorPidMax;
}

