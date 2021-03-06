// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Commands/DriveShift.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveShift::DriveShift(bool gearSetting): frc::Command() {
m_gearSetting = gearSetting;
    // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveShift::Initialize()
{
    std::printf("2135: DriveShift - Init (%d)\n", m_gearSetting);
    Robot::drivetrain->MoveShiftGears(m_gearSetting);
}

// Called repeatedly when this Command is scheduled to run
void DriveShift::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool DriveShift::IsFinished()
{
    return false;
}

// Called once after isFinished returns true
void DriveShift::End()
{
    std::printf("2135: DriveShift - End (%d)\n", !m_gearSetting);
    Robot::drivetrain->MoveShiftGears(!m_gearSetting);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveShift::Interrupted() {
    std::printf("2135: DriveShift - Interrupted (%d)\n", !m_gearSetting);
    Robot::drivetrain->MoveShiftGears(!m_gearSetting);
}
