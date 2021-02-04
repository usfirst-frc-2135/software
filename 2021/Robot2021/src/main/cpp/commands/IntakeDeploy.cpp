// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "RobotContainer.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/IntakeDeploy.h"

IntakeDeploy::IntakeDeploy(bool intakeDeploy) :
    m_intakeDeploy(intakeDeploy)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("IntakeDeploy");

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

    RobotContainer *container = RobotContainer::GetInstance ();
    m_intake = &container->m_intake;
}

// Called just before this Command runs the first time
void IntakeDeploy::Initialize()
{
    std::printf("2135: IntakeDeploy - Init\n");
    m_intake->SetDeployerSolenoid(m_intakeDeploy);
}

// Called repeatedly when this Command is scheduled to run
void IntakeDeploy::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool IntakeDeploy::IsFinished()
{
    return true;
}

// Called once after isFinished returns true
void IntakeDeploy::End(bool interrupted)
{
    std::printf("2135: IntakeDeploy - End\n");
}

bool IntakeDeploy::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
