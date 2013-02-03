// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef MAGAZINE_H
#define MAGAZINE_H
#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class Magazine: public PIDSubsystem {
 public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	SpeedController* magazineMotor;
	AnalogChannel* magazinePotentiometer;
	AnalogChannel* slotLimit1;
	AnalogChannel* slotLimit2;
	AnalogChannel* slotLimit3;
	AnalogChannel* slotLimit4;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Magazine();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
	bool Magazine::GetSlotLimit(int slotNum);
};
#endif
