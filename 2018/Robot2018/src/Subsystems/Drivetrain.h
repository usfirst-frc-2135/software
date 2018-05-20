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
#include "../frc2135/RobotConfig.h"
#include "AHRS.h"
#include "../frc2135/PIDOutputDriveTurn.h"

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
	const double				COUNTS_PER_ROTATION = (1024*4);		// CPR is 1024 and multipled by 4 because it is a quadrature encoder
	const double				WHEEL_DIA_INCHES = 6.0;
	const double 				m_circumInches = (WHEEL_DIA_INCHES*M_PI);		//Circumference in inches (Real Robot)
	const double				CountsPerInch = COUNTS_PER_ROTATION / (WHEEL_DIA_INCHES * M_PI);

	// Declare module variables
	bool	m_talonValidL1;			// Health indicator for drive Talon Left 1
	bool	m_talonValidL2;			// Health indicator for drive Talon Left 2
	bool	m_talonValidR3;			// Health indicator for drive Talon Right 3
	bool	m_talonValidR4;			// Health indicator for drive Talon Right 4
	double	m_driveXScaling;		// Scaling applied to Joystick
	double	m_driveYScaling;		// Scaling applied to Joystick
	double	m_turnScaling;			// Turn scaling (1.0 is disabled, < 1.0 is max X output)
	double	m_driveSpin;			// Spin turn power setting

	bool 	m_lowGear;				// Low Gear or High Gear
	bool 	m_brakeMode;			// Brake or Coast Mode for Talons

	Timer 	m_safetyTimer;			// Safety timer for use during autonomous modes
	double  m_safetyTimeout; 		// Time in seconds for safety timer

	double 	m_distTargetCounts;		// Drive distance target count value
	double 	m_distTargetInches;		// Drive distance target inches value
	double	m_distErrInches;		// Drive distance tolerance in inches
	double	m_distMaxInches;		// Drive distance maximum inches allowed as input
	double 	m_distKp;				// Drive distance proportional value for PID
	double 	m_distMaxOut;			// Drive distance max motor output value for PID
	double	m_CL_rampRate;			// Closed loop ramp rate for PID
	int		m_CLAllowedError;		// Closed loop allowable error for PID

	double 	m_turnAngle;			// Desired turn angle from present course
	double	m_turnErrDeg;			// DriveTurn tolerance in degrees
	double 	m_turnKp;				// Proportional value for PID for DriveTurn function
	double 	m_turnMaxOut;			// Max motor output value for PID for DriveTurn function

	AHRS 	*gyro;					// Initializes NavX Board and gyro

	PIDOutputDriveTurn	*driveTurnPIDOutput;	// Drive turn to angle with gyro
	PIDController		*driveTurnPIDLoop;		// Drive turn PID control

public:
	Drivetrain();
	void InitDefaultCommand() override;
	void Periodic() override;

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void Initialize(void);
	void MoveWithJoystick(std::shared_ptr<Joystick>);
	void MoveSpin(bool spinRight);
	void MoveStop(void);

	// Shifting Gears
    void MoveShiftGears(bool lowGear);
    //Brake or Coast Mode
    void MoveSetBrakeMode(bool m_brakeMode);

	double InchesToCounts(double inches);
	double CountsToInches(int counts);
	double GetCurrentInches(WPI_TalonSRX& motor);

    //Autonomous Programs
    void MoveDriveDistancePIDInit(double distance);
    void MoveDriveDistancePIDExecute();
    bool MoveDriveDistanceIsPIDAtSetpoint();
	void MoveDriveDistancePIDStop();

    void MoveDriveTurnPIDInit(double angle);
    void MoveDriveTurnPIDExecute();
    bool MoveDriveTurnIsPIDAtSetPoint();
    void MoveDriveTurnPIDStop();

    //Manual Reset of Drivetrain Encoders
    void ResetSensors();
};

#endif
