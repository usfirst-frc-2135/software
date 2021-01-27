// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "frc2135/RobotConfig.h"
#include "frc2135/TalonUtils.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/Conveyor.h"
#include <frc/smartdashboard/SmartDashboard.h>

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Conveyor::Conveyor()
{
    SetName("Conveyor");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Conveyor");

 
 

 AddChild("CV Photosensor", &m_cVPhotosensor);
 

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidCV8 = frc2135::TalonUtils::TalonCheck(m_motorCV8, "CV", "CV8");

    // Initialize Variables
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("CV_AcquireSpeed", m_acquireSpeed, 0.75);
    config->GetValueAsDouble("CV_ExpelSpeed", m_expelSpeed, -0.75);

    // Set motor directions
    // Turn on Coast mode (not brake)
    // Initialize modes and set power to off
    if (m_talonValidCV8)
    {
        m_motorCV8.SetInverted(false);
        m_motorCV8.SetNeutralMode(NeutralMode::Coast);
        m_motorCV8.Set(ControlMode::PercentOutput, 0.0);
    }
}

void Conveyor::Periodic()
{

    static int  periodicInterval = 0;

    // Put code here to be run every 20 ms loop

    // Only update indicators every 100 ms to cut down on network traffic
    if (periodicInterval++ % 5 == 0)
    {
        double outputCV8;

        outputCV8 = (m_talonValidCV8) ? m_motorCV8.GetMotorOutputPercent() : 0.0;
        frc::SmartDashboard::PutNumber("CV_Output_CV8", outputCV8);
#if 0
        frc::SmartDashboard::PutNumber("CV_Photosensor", m_cVPhotosensor.Get());
#endif
        if (m_conveyorDebug > 0)
        {
            double currentCV8;

            currentCV8 = (m_talonValidCV8) ? m_motorCV8.GetOutputCurrent() : 0.0;
            frc::SmartDashboard::PutNumber("CV_Current_CV8", currentCV8);
        }
    }

#if 0   // Until we install a photosensor and an LED string
    // Turn on LED when photosensor detects power cell
    if (!m_cVPhotosensor.Get())
        Robot::led->DisplayColor(Led::LEDSOURCE_CONVEYOR, true);
    else
        Robot::led->DisplayColor(Led::LEDSOURCE_CONVEYOR, false);
#endif
}

void Conveyor::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Conveyor::Initialize(void)
{
    std::printf("2135: CV Init\n");
    // Motor off
    if (m_talonValidCV8)
    {
        m_motorCV8.Set(ControlMode::PercentOutput, 0.0);

        m_motorCV8.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kCANTimeout);
        m_motorCV8.SetSensorPhase(false);
        m_motorCV8.SetSelectedSensorPosition(0, kCANTimeout);
    }
}

//    Dump all Talon faults
void Conveyor::FaultDump(void)
{
    frc2135::TalonUtils::TalonFaultDump("CV 8", m_motorCV8);
}

// Set mode of conveyor
void Conveyor::SetConveyorMotorSpeed(int direction)
{
    const char *strName;
    double outputCV = 0.0;         // Default: off

    switch (direction)
    {
        default:
        case CONVEYOR_STOP:
            strName = "STOP";
            outputCV = 0.0;
            break;
        case CONVEYOR_UP:
            strName = "UP";
            outputCV = m_acquireSpeed;
            break;
        case CONVEYOR_DOWN:
            strName = "DOWN";
            outputCV = m_expelSpeed;
            break;
    }

    std::printf("2135: Conveyor Set Speed - %s\n", strName);

    if (m_talonValidCV8)
        m_motorCV8.Set(ControlMode::PercentOutput, outputCV);
}
