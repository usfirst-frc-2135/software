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
class LED: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	int m_previousColor = 0;

	static constexpr int kLength = 30;

    // PWM port 9
    // Must be a PWM header, not MXP or DIO
    frc::AddressableLED m_led{9};
    std::array<frc::AddressableLED::LEDData, kLength> m_ledBuffer;  // Reuse the buffer

    // Store what the last hue of the first pixel is
    int firstPixelHue = 0;

public:
LED();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

void LEDInit (void);
	void SetColor (int color);
	void LEDSetRGB(int rgbRed, int rgbGreen, int rgbBlue);
	void DetectPowerCell(bool powerCellOn);

	enum LED_Color{
		LED_SetBlack = -1,
		LED_SetWhite = 0,
		LED_SetRed = 1,
		LED_SetOrange = 2,
		LED_SetYellow = 3,
		LED_SetGreen = 4,
		LED_SetBlue = 5,
		LED_SetPurple = 6,
	};

	frc::SendableChooser<LED_Color> chooser;

};

