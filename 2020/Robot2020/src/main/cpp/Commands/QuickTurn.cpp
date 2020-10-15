#include "Commands/QuickTurn.h"

QuickTurn::QuickTurn(): frc::Command() {
    SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void QuickTurn::Initialize()
{
    std::printf("2135: QuickTurn - Init\n");
    Robot::drivetrain->setQuickTurn(true);
}

// Called repeatedly when this Command is scheduled to run
void QuickTurn::Execute()
{
    Robot::drivetrain->setQuickTurn(true);
}

// Make this return true when this Command no longer needs to run execute()
bool QuickTurn::IsFinished()
{
    return false;
}

// Called once after isFinished returns true
void QuickTurn::End()
{
    std::printf("2135: QuickTurn - End \n");
    Robot::drivetrain->setQuickTurn(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void QuickTurn::Interrupted()
{
    std::printf("2135: QuickTurn - Interrupted \n");
    Robot::drivetrain->setQuickTurn(false);
}