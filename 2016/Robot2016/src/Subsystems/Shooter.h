// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef SHOOTER_H
#define SHOOTER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Shooter: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<CANTalon> lowerMotor;
	std::shared_ptr<CANTalon> upperMotor;
	std::shared_ptr<DoubleSolenoid> frameSolenoid;
	std::shared_ptr<DoubleSolenoid> fireSolenoid;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Timer m_timer;
	bool m_isPID;
	double m_upperP;
	double m_upperI;
	double m_upperD;
	double m_lowerP;
	double m_lowerI;
	double m_lowerD;
	const double M_VELOCITY_PER_VBUS_PRCNT = 4652.95789;  // Max rs775pro RPM 18730/4
	FILE* m_logFile;
	Timer m_encoder_timer;

	void UpdateEncoderDisplays(bool force_update);

public:
	Shooter();
	void InitDefaultCommand();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void Initialize(Preferences *prefs);
	void SetMotorSpeeds(double upperSpeed, double lowerSpeed);
	void SetMotorDirection(bool isForward);
	void ToggleControlMode(void);
	void ShootStartMode(void);
	void ShootFinishMode(void);
	void SetFireSolenoid (bool fire);
	void SetFrameControl(bool frameUp);
};

#endif
