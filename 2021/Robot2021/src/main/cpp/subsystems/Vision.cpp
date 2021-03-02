// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/Vision.h"

#include <frc/smartdashboard/SmartDashboard.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Vision::Vision()
{
    SetName("Vision");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Vision");

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    table->PutNumber("ledMode", 0);

    Initialize();
}

void Vision::Periodic()
{
    // Put code here to be run every loop
    m_targetOffsetAngle_Horizontal = table->GetNumber("tx", 0.0);
    m_targetOffsetAngle_Vertical = table->GetNumber("ty", 0.0);
    m_targetArea = table->GetNumber("ta", 0.0);
    m_targetSkew = table->GetNumber("ts", 0.0);
    m_targetValid = (bool)table->GetNumber("tv", 0.0);

    frc::SmartDashboard::PutNumber("VI_HORZ_OFFSET_ANGLE", m_targetOffsetAngle_Horizontal);
    frc::SmartDashboard::PutNumber("VI_VERT_OFFSET_ANGLE", m_targetOffsetAngle_Vertical);
    frc::SmartDashboard::PutNumber("VI_TARGET_AREA", m_targetArea);
    frc::SmartDashboard::PutNumber("VI_TARGET_SKEW", m_targetSkew);
}

void Vision::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Vision::Initialize(void)
{
    std::printf("2135: VI Init\n");
}

double Vision::GetHorizOffset()
{
    return m_targetOffsetAngle_Horizontal;
}

double Vision::GetVertOffset()
{
    return m_targetOffsetAngle_Vertical;
}

double Vision::GetTargetArea()
{
    return m_targetArea;
}

double Vision::GetTargetSkew()
{
    return m_targetSkew;
}

bool Vision::GetTargetValid()
{
    return m_targetValid;
}

void Vision::SetLEDMode(bool mode)
{
    table->PutNumber("led", mode);
}
