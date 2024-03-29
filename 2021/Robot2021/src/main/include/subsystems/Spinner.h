// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#pragma once

#include <rev/ColorMatch.h>
#include <rev/ColorSensorV3.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "ctre/Phoenix.h"

#include <frc/DoubleSolenoid.h>
#include <frc2/command/SubsystemBase.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author ExampleAuthor
 */
class Spinner : public frc2::SubsystemBase
{
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities
#if 0
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
WPI_TalonSRX m_motorSP12{12};
frc::DoubleSolenoid m_position{1, 0, 7};

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#endif
    // Declare constants
    const int kCANTimeout = 30; // CAN timeout in msec to wait for response

    const frc::I2C::Port kI2cPort = frc::I2C::Port::kOnboard;
#if 0
    rev::ColorSensorV3      m_colorSensor { kI2cPort };
    rev::ColorMatch         m_colorMatcher;
#endif

    frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
    frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
    frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
    frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

    // Declare module variables
    bool m_talonValidSP12;

    double m_spinSpeed;
    int m_colorCount;

    std::string m_targColor;
    std::string m_curColor;
    std::string m_lastColor;

    std::string rotColors[32] = {};
    std::string posColors[4] = {};

    std::string ReadColorValue();
    bool isColorOrderValid(std::string curColor, std::string lastColor);

public:
    Spinner();

    void Periodic() override;
    void SimulationPeriodic() override;
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    void Initialize(void);
    void FaultDump(void);

    void ControlPositionInit(std::string givenColor);
    void ControlPositionExecute();
    bool ControlPositionIsFinished();
    void ControlPositionEnd();

    void ControlRotationInit();
    void ControlRotationExecute();
    bool ControlRotationIsFinished();
    void ControlRotationEnd();
};
