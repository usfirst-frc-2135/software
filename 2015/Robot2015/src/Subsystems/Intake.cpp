// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Intake.h"
#include "../RobotMap.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/IntakeIdleBoth.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Intake::Intake() : Subsystem("Intake") {

	printf("2135: Intake init\n");
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	conveyorL = RobotMap::intakeConveyorL;
	conveyorR = RobotMap::intakeConveyorR;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	m_intakeSpeed = 0.0;
}
    
void Intake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new IntakeIdleBoth());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Intake::SetIntakeSpeed( double value )
{
	m_intakeSpeed = value;
	printf("IntakeSpeed:     %f\n", m_intakeSpeed);
}

double Intake::GetIntakeSpeed( void )
{
	return m_intakeSpeed;
}

void Intake::IntakeRun(double speed) {
	conveyorL->Set( m_intakeSpeed );
	conveyorR->Set( m_intakeSpeed );
}

void Intake::IntakeStop( void ) {
	conveyorL->Set(0.0);
	conveyorR->Set(0.0);
}