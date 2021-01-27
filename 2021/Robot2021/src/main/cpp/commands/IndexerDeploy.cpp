// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/IndexerDeploy.h"

IndexerDeploy::IndexerDeploy(bool indexer, Shooter* m_shooter) :
    m_indexer(indexer),
m_shooter(m_shooter)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(Robot::chassis.get());
    SetName("IndexerDeploy");
    AddRequirements(m_shooter);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

}

// Called just before this Command runs the first time
void IndexerDeploy::Initialize()
{
    std::printf("2135: IndexerDeploy - Init (%d)\n", m_indexer);
    m_shooter->IndexerDeploy(m_indexer);
}

// Called repeatedly when this Command is scheduled to run
void IndexerDeploy::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool IndexerDeploy::IsFinished()
{
    return true;
}

// Called once after isFinished returns true
void IndexerDeploy::End(bool interrupted)
{
    std::printf("2135: IndexerDeploy - End\n");
}

bool IndexerDeploy::RunsWhenDisabled() const
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
    return false;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DISABLED
}
