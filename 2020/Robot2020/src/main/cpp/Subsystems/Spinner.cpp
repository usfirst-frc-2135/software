// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <Subsystems/Spinner.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Spinner::Spinner() : frc::Subsystem("Spinner") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
motorSP12.reset(new WPI_TalonSRX(12));


controlPanelDeployer.reset(new frc::DoubleSolenoid(0, 4, 5));
AddChild("Control Panel Deployer", controlPanelDeployer);


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Initialize Variables 
    // TODO: determine speeds (default is random)
    frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("SP_TurnSpeed", m_spinSpeed, 0.6); 

    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);

    if (m_talonValidSP12) { 
        motorSP12->SetInverted(false);
        motorSP12->SetNeutralMode(NeutralMode::Brake);
        motorSP12->ConfigVoltageCompSaturation(12.0, 0);
        motorSP12->EnableVoltageCompensation(true);
    }

    frc::SmartDashboard::PutString("Color Setpoint", "");
}

void Spinner::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Spinner::Periodic() {
    // Put code here to be run every loop
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

    if (matchedColor == kBlueTarget) {
      colorString = "Blue";
    } else if (matchedColor == kRedTarget) {
      colorString = "Red";
    } else if (matchedColor == kGreenTarget) {
      colorString = "Green";
    } else if (matchedColor == kYellowTarget) {
      colorString = "Yellow";
    } else {
      colorString = "Unknown";
    }
        /**
     * Open Smart Dashboard or Shuffleboard to see the color detected by the 
     * sensor.
     */
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);
    frc::SmartDashboard::PutString("Detected Color", colorString);

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

///// Rotate the control panel to a given color. /////

void Spinner::ControlPositionInit(std::string givenColor) {

  m_targColor = givenColor;
  std::printf("Position Control: Target Color %s", m_targColor.c_str());

  motorSP12->Set(ControlMode::PercentOutput, m_spinSpeed); // Run motor to turn control panel
}

void Spinner::ControlPositionExecute() {
    m_curColor = ReadColorValue();
}

bool Spinner::ControlPositionIsFinished() {
  if (m_curColor == m_targColor) return true;
  return false;
}

void Spinner::ControlPositionEnd() {
  motorSP12->Set(ControlMode::PercentOutput, 0.0); // Stop motor
}

///// Rotate the control panel four times. /////

void Spinner::ControlRotationInit() {
  m_colorCount = 0;
  motorSP12->Set(ControlMode::PercentOutput, m_spinSpeed);
}

void Spinner::ControlRotationExecute() {
  m_curColor = ReadColorValue();
  if (m_colorCount == 0) {
    rotColors[m_colorCount++] = m_curColor;
    m_lastColor = m_curColor;
  }

  if (m_curColor != m_lastColor) {
    if (isColorOrderValid(m_curColor, m_lastColor)) {
      rotColors[m_colorCount++] =  m_curColor;
      m_lastColor = m_curColor;
    }
  }
}

bool Spinner::ControlRotationIsFinished() {
  if (m_colorCount >= 31) {
    return true;
  }
  else return false;
}

void Spinner::ControlRotationEnd() {
  motorSP12->Set(ControlMode::PercentOutput, 0.0); // Stop motor
}

std::string Spinner::ReadColorValue() {
  frc::Color detectedColor = m_colorSensor.GetColor();

    // COLOR MATCH
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

    if (matchedColor == kBlueTarget) {
      colorString = "Blue";
    } else if (matchedColor == kRedTarget) {
      colorString = "Red";
    } else if (matchedColor == kGreenTarget) {
      colorString = "Green";
    } else if (matchedColor == kYellowTarget) {
      colorString = "Yellow";
    } else {
      colorString = "Unknown";
    }

  return colorString;
}

bool Spinner::isColorOrderValid(std::string curColor, std::string lastColor) {
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

  return true;
}