// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class Elevator: public PIDSubsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	double          m_elevatorSpeed;
	double			m_elevatorPidMin;
	double			m_elevatorPidMax;

 public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	CANTalon* motor6;
	CANTalon* motor7;
	AnalogPotentiometer* heightPot;
	DigitalInput* upperLimit;
	DigitalInput* lowerLimit;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	enum ElevatorDirection {
		kElevatorUp = 0,
		kElevatorDown = 1
	};

	Elevator();
	void SetNeutralMode( void );
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
	void ElevatorRun( bool direction );
	void ElevatorStop( void );
	void SetElevatorSpeed( double value );
	double GetElevatorSpeed( void );
	void SetElevatorPidMin( double value );
	double GetElevatorPidMin( void );
	void SetElevatorPidMax( double value );
	double GetElevatorPidMax( void );

};

#endif