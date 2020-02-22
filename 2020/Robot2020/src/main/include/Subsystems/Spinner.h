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

#include <frc/commands/Subsystem.h>

#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>

#include <frc/util/Color.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <frc2135/RobotConfig.h>

#include <frc2135/TalonUtils.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "ctre/Phoenix.h"
#include "frc/DoubleSolenoid.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

/**
 *
 *
 * @author ExampleAuthor
 */
class Spinner: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorSP12;
	std::shared_ptr<frc::DoubleSolenoid> controlPanelDeployer;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	bool			m_talonValidSP12;

	double			m_spinSpeed;
	int				m_colorCount;

	std::string		m_targColor;
	std::string		m_curColor;
	std::string		m_lastColor;

	std::string		rotColors [32] = {};
	std::string		posColors [4] = {};

    static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
    rev::ColorSensorV3 m_colorSensor{i2cPort};
	rev::ColorMatch m_colorMatcher;

	static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
  	static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
  	static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
  	static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

public:
Spinner();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void ControlPositionInit(std::string givenColor);
	void ControlPositionExecute();
	bool ControlPositionIsFinished();
	void ControlPositionEnd();

	void ControlRotationInit();
	void ControlRotationExecute();
	bool ControlRotationIsFinished();
	void ControlRotationEnd();

	std::string ReadColorValue();
	bool isColorOrderValid(std::string curColor, std::string lastColor);

};

