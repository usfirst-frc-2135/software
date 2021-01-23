// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <frc/util/Color.h>
#include <frc2135/TalonUtils.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/Spinner.h"
#include <frc/smartdashboard/SmartDashboard.h>

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Spinner::Spinner()
{
SetName("Spinner");

#if 0   // TODO: Until we get a spinner mechanism installed

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Spinner");

 
 

 AddChild("Position", &m_position);
 

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

     // Initialize Variables
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("SP_TurnSpeed", m_spinSpeed, 0.6);

    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);

    if (m_talonValidSP12)
    {
        m_motorSP12.SetInverted(false);
        m_motorSP12.SetNeutralMode(NeutralMode::Brake);
        m_motorSP12.ConfigVoltageCompSaturation(12.0, 0);
        m_motorSP12.EnableVoltageCompensation(true);
    }

    frc::SmartDashboard::PutString("Color Setpoint", "");
#endif
}

void Spinner::Periodic()
{
    // Put code here to be run every 20 msec loop
    // TODO: Reading the color sensor MUST be in separate thread
    //  The i2c transactions can block for 100msec in the main loop--that's a problem
#if 0   // TODO: Until we get a spinner mechanism installed

   /**
     * The method GetColor() returns a normalized color value from the sensor and can be
     * useful if outputting the color to an RGB LED or similar. To
     * read the raw color, use GetRawColor().
     *
     * The color sensor works best when within a few inches from an object in
     * well lit conditions (the built in LED is a big help here!). The farther
     * an object is the more light from the surroundings will bleed into the
     * measurements and make it difficult to accurately determine its color.
     */
    frc::Color detectedColor = m_colorSensor.GetColor();

    // COLOR MATCH
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    if (matchedColor == kBlueTarget)
        colorString = "Blue";
    else if (matchedColor == kRedTarget)
        colorString = "Red";
    else if (matchedColor == kGreenTarget)
        colorString = "Green";
    else if (matchedColor == kYellowTarget)
        colorString = "Yellow";
    else
        colorString = "Unknown";

    //  Open Smart Dashboard or Shuffleboard to see the color detected by the sensor
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);
    frc::SmartDashboard::PutString("Detected Color", colorString);

#endif
}

void Spinner::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Spinner::Initialize(void)
{
    std::printf("2135: SP12 Init\n");
    // Motor off
    if (m_talonValidSP12)
    {
        m_motorSP12.Set(ControlMode::PercentOutput, 0.0);

        m_motorSP12.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kCANTimeout);
        m_motorSP12.SetSensorPhase(false);
        m_motorSP12.SetSelectedSensorPosition(0, kCANTimeout);
    }
}

//    Dump all Talon faults
void Spinner::FaultDump(void)
{
    frc2135::TalonUtils::TalonFaultDump("SP 12", m_motorSP12);
}

///// Rotate the control panel to a given color. /////

void Spinner::ControlPositionInit(std::string givenColor)
{
#if 0   // TODO: Until we get a spinner mechanism installed

    m_targColor = givenColor;
    std::printf("2135: Position Control: Target Color %s\n", m_targColor.c_str());

    if (m_talonValidSP12)
        m_motorSP12.Set(ControlMode::PercentOutput, m_spinSpeed); // Run motor to turn control panel
#endif
}

void Spinner::ControlPositionExecute()
{
#if 0   // TODO: Until we get a spinner mechanism installed

    m_curColor = ReadColorValue();
#endif
}

bool Spinner::ControlPositionIsFinished()
{
#if 0   // TODO: Until we get a spinner mechanism installed
    if (m_curColor == m_targColor) return true;
        return false;
#else
    return true;
#endif
}

void Spinner::ControlPositionEnd()
{
#if 0   // TODO: Until we get a spinner mechanism installed

    if (m_talonValidSP12)
        m_motorSP12.Set(ControlMode::PercentOutput, 0.0); // Stop motor
#endif
}

///// Rotate the control panel four times. /////

void Spinner::ControlRotationInit()
{
#if 0   // TODO: Until we get a spinner mechanism installed

    m_colorCount = 0;
    if (m_talonValidSP12)
        m_motorSP12.Set(ControlMode::PercentOutput, m_spinSpeed);
#endif
}

void Spinner::ControlRotationExecute()
{
#if 0   // TODO: Until we get a spinner mechanism installed

    m_curColor = ReadColorValue();
    if (m_colorCount == 0)
    {
        rotColors[m_colorCount++] = m_curColor;
        m_lastColor = m_curColor;
    }

    if (m_curColor != m_lastColor)
    {
        if (isColorOrderValid(m_curColor, m_lastColor))
        {
            rotColors[m_colorCount++] =  m_curColor;
            m_lastColor = m_curColor;
        }
    }
#endif
}

bool Spinner::ControlRotationIsFinished()
{
#if 0   // TODO: Until we get a spinner mechanism installed

    if (m_colorCount >= 31)
        return true;
    else
        return false;
#else
    return true;
#endif
}

void Spinner::ControlRotationEnd()
{
#if 0   // TODO: Until we get a spinner mechanism installed

    if (m_talonValidSP12)
        m_motorSP12.Set(ControlMode::PercentOutput, 0.0); // Stop motor
#endif
}

std::string Spinner::ReadColorValue()
{
#if 0   // TODO: Until we get a spinner mechanism installed

    frc::Color detectedColor = m_colorSensor.GetColor();

    // COLOR MATCH
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    if (matchedColor == kBlueTarget)
        colorString = "Blue";
    else if (matchedColor == kRedTarget)
        colorString = "Red";
    else if (matchedColor == kGreenTarget)
        colorString = "Green";
    else if (matchedColor == kYellowTarget)
        colorString = "Yellow";
    else
        colorString = "Unknown";

    return colorString;
#else
    return "Unknow";
#endif
}

bool Spinner::isColorOrderValid(std::string curColor, std::string lastColor)
{
#if 0   // TODO: Until we get a spinner mechanism installed

    // Color Order Check: Blue Green Red Yellow (clockwise)
    // if curColor = Red then lastColor = Green
    // if curColor = Yellow then lastColor = Red
    // if curColor = Blue then lastColor = Yellow
    // if curColor = Green then lastColor = Blue

    if ((curColor == "Red") && (lastColor != "Green")) return false;
    if ((curColor == "Yellow") && (lastColor != "Red")) return false;
    if ((curColor == "Blue") && (lastColor != "Yellow")) return false;
    if ((curColor == "Green") && (lastColor != "Blue")) return false;
    if (curColor == "Unknown") {
        frc::SmartDashboard::PutString("Color Order Check", "Unknown");
        return false;
  }
#endif

  return true;
}
