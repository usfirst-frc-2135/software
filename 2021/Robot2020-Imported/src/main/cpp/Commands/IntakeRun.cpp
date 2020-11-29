// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/IntakeRun.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

IntakeRun::IntakeRun(int intakeDirection): frc::Command() {
m_intakeDirection = intakeDirection;
    // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::intake.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void IntakeRun::Initialize()
{
    std::printf("2135: IntakeRun - Init (%d)\n", m_intakeDirection);
    Robot::intake->SetIntakeMotorDirection(m_intakeDirection);
}

// Called repeatedly when this Command is scheduled to run
void IntakeRun::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeRun::IsFinished()
{
    return false;
}

// Called once after isFinished returns true
void IntakeRun::End()
{
    std::printf("2135: IntakeRun - End \n");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void IntakeRun::Interrupted()
{
    std::printf("2135: IntakeRun - Interrupted \n");

}
