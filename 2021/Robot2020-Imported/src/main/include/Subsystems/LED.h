// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#pragma once

#include "frc/commands/Subsystem.h"
#include <frc/AddressableLED.h>
#include "frc/smartdashboard/SendableChooser.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author ExampleAuthor
 */
class Led: public frc::Subsystem
{

private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // Declare constants
    // PWM port 9 - Must be a PWM header, not MXP or DIO
    static const int            kLEDStringLength = 30;
    frc::AddressableLED         m_led { 9 };
    std::array<frc::AddressableLED::LEDData, kLEDStringLength> m_ledBuffer;  // Reuse the buffer

    typedef enum LEDColor_e
    {
        LEDCOLOR_OFF    = -1,
        LEDCOLOR_WHITE  = 0,
        LEDCOLOR_RED    = 1,
        LEDCOLOR_ORANGE = 2,
        LEDCOLOR_YELLOW = 3,
        LEDCOLOR_GREEN  = 4,
        LEDCOLOR_BLUE   = 5,
        LEDCOLOR_PURPLE = 6
    } LEDColor_e;

    const int   m_shooterLEDColor     = LEDCOLOR_BLUE;
    const int   m_conveyorLEDColor    = LEDCOLOR_RED;

    // Declare module variables
    int         m_previousColor = 0;

    // Store what the last hue of the first pixel is
    int         firstPixelHue   = 0;
    int         m_sourceEnabled = 0;

    void SendRGBToString(int rgbRed, int rgbGreen, int rgbBlue);
    void SetColor (int color);

public:
    Led();
    void InitDefaultCommand() override;
    void Periodic() override;

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    typedef enum LEDSource_e
    {
        LEDSOURCE_SHOOTER   = 1<<0,
        LEDSOURCE_CONVEYOR  = 1<<1,
        LEDSOURCE_COMMAND   = 1<<2
    } LEDSource_e;

    void Initialize (void);
    void DetectPowerCell(bool powerCellOn);
    void DisplayColor(LEDSource_e source, bool enable);

    frc::SendableChooser<LEDColor_e> m_ledChooser;
};
