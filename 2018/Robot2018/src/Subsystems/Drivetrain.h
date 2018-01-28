// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../RobotDefaults.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
#ifdef ROBOTNOTSTANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorL1;
	std::shared_ptr<WPI_TalonSRX> motorR3;
	std::shared_ptr<frc::DifferentialDrive> diffDrive;
	std::shared_ptr<WPI_TalonSRX> motorL2;
	std::shared_ptr<WPI_TalonSRX> motorR4;
	std::shared_ptr<frc::DoubleSolenoid> shifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#endif
	double m_driveSpin;				// Spin turn power setting
	double m_driveScaling;			//Scaling applied to Joystick, on high gear only
	bool m_lowGear;					// Low Gear or High Gear
	bool m_brakeMode;				//Brake or Coast Mode for Talons
	const double					WheelDiaInches = 4.0;
	const unsigned short int		Encoder_CPR = (360 * 4); //Talons report CPR * 4
	const double					InchesPerCount = WheelDiaInches * M_PI / (double)Encoder_CPR;
	const int 						pidIndex = 0; 			// PID slot index for sensors
	const int 						timeout = 10; 			// CAN timeout in msec to wait for response

	double 	m_pidTargetCounts;
	double 	m_proportional;
	bool 	m_CL_pidStarted; 								// Flag to indicate PID has started and CL error is invalid
	Timer 	m_safetyTimer;									// Safety timer for use during autonomous modes

public:
	Drivetrain();
	void InitDefaultCommand() override;
	void Periodic() override;

	void Initialize(frc::Preferences *RobotConfig);
	void MoveWithJoystick(std::shared_ptr<Joystick>);
	void MoveSpin(bool spinRight);

	// Shifting Gears
    void MoveShiftGears(bool lowGear);
    void MoveShiftToggle(void);

    //Brake or Coast Mode
    void MoveSetBrakeMode(bool m_brakeMode);

    //Autonomous Programs
    void MoveDriveDistancePIDInit(double distance);
    void MoveDriveDistancePIDExecute();
    bool MoveDriveDistanceIsPIDAtSetpoint();
	void MoveDriveDistancePIDStop();


    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
