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
#include "../FRC2135/RobotConfig.h"
#include "AHRS.h"
#include "../FRC2135/PIDOutputDriveTurn.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
#ifndef ROBORIO_STANDALONE
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorL1;
	std::shared_ptr<WPI_TalonSRX> motorR3;
	std::shared_ptr<frc::DifferentialDrive> diffDrive;
	std::shared_ptr<WPI_TalonSRX> motorL2;
	std::shared_ptr<WPI_TalonSRX> motorR4;
	std::shared_ptr<frc::DoubleSolenoid> shifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#endif
	//	Declare constants
	const int					m_slotIndex = 0;					// Motor controller profile slot index
	const int 					m_pidIndex = 0; 					// PID slot index for sensors
	const int 					m_timeout = 10; 					// CAN timeout in msec to wait for response
	const double				WheelDiaInches = 6.0;
	const unsigned short int	CTRE_Mag_CPR = 1024; 				// CTRE magnetic encoder is 1024 counts per rev
	const unsigned short int	Encoder_CPR = (CTRE_Mag_CPR * 4); 	// Talons report CPR * 4
	const double				CountsPerInch = (double) Encoder_CPR / (WheelDiaInches * M_PI);

	// Declare module variables
	double	m_driveScaling;			// Scaling applied to Joystick, on high gear only
	double	m_turnScaling;			// Turn scaling (1.0 is disabled, < 1.0 is max X output)
	double	m_driveSpin;			// Spin turn power setting

	bool 	m_lowGear;				// Low Gear or High Gear
	bool 	m_brakeMode;			// Brake or Coast Mode for Talons

	Timer 	m_safetyTimer;			// Safety timer for use during autonomous modes
	double  m_safetyTimeout; 		// Time in seconds for safety timer

	double 	m_distTargetCounts;		// Drive distance target count value
	double 	m_distKp;				// Drive distance proportional value
	bool 	m_CL_pidStarted; 		// Flag to indicate PID has started and CL error is invalid
	int		m_CL_allowError;		// Closed loop allowable error

	double 	m_turnKp;				// Proportional value for PID for DriveTurn function

	AHRS 	*gyro;					// Initializes NavX Board and gyro

	PIDOutputDriveTurn	*driveTurnPIDOutput;	// Drive turn to angle with gyro
	PIDController		*driveTurnPIDLoop;		// Drive turn PID control

public:
	Drivetrain();
	void InitDefaultCommand() override;
	void Periodic() override;

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void Initialize(frc::Preferences *RobotConfig);
	void MoveWithJoystick(std::shared_ptr<Joystick>);
	void MoveSpin(bool spinRight);

	// Shifting Gears
    void MoveShiftGears(bool lowGear);
    //Brake or Coast Mode
    void MoveSetBrakeMode(bool m_brakeMode);

    //Autonomous Programs
    void MoveDriveDistancePIDInit(double distance);
    void MoveDriveDistancePIDExecute();
    bool MoveDriveDistanceIsPIDAtSetpoint();
	void MoveDriveDistancePIDStop();

    void MoveDriveTurnPIDInit(double angle);
    void MoveDriveTurnPIDExecute();
    bool MoveDriveTurnIsPIDAtSetPoint();
    void MoveDriveTurnPIDStop();
};

#endif
