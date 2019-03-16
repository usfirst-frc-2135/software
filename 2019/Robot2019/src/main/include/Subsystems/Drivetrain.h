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
#include "frc/commands/Subsystem.h"
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
#include "ctre/phoenix/sensors/PigeonIMU.h"
#include "RobotDefaults.h"
#include "frc2135/TalonSRXUtils.h"
#include "frc2135/RobotConfig.h"
#include "frc2135/PIDSourceDriveTurn.h"
#include "frc2135/PIDOutputDriveTurn.h"
#include "frc2135/PIDSourceDriveVision.h"
#include "frc2135/PIDOutputDriveVision.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> motorL1;
	std::shared_ptr<WPI_TalonSRX> motorR3;
	std::shared_ptr<frc::DifferentialDrive> diffDrive;
	std::shared_ptr<WPI_TalonSRX> motorL2;
	std::shared_ptr<WPI_TalonSRX> motorR4;
	std::shared_ptr<frc::DoubleSolenoid> shifter;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	std::shared_ptr<PigeonIMU> 	pigeonIMU;

	//	Declare constants
	int				m_driveDebug = 0;					// Debug flag to disable extra logging calls
	const int 		m_pidIndex = 0; 					// PID slot index for sensors
	const int 		m_timeout = 30; 					// CAN timeout in msec to wait for response
	const double	COUNTS_PER_ROTATION = (1024*4);		// CPR is 1024 and multiplied by 4
	const double 	WHEEL_DIA_INCHES = 6.0;				
	const double 	CountsPerInch = COUNTS_PER_ROTATION/(WHEEL_DIA_INCHES*M_PI); 
	const double	m_circumInches = (WHEEL_DIA_INCHES*M_PI);
	const int		m_reqPigeonVer = ((4*256)+13);		// Pigeon IMU version is 4.13

	//Declare module variables
	bool	m_talonValidL1;			// Health indicator for drive Talon Left 1
	bool	m_talonValidL2;			// Health indicator for drive Talon Left 2
	bool	m_talonValidR3;			// Health indicator for drive Talon Right 3
	bool	m_talonValidR4;			// Health indicator for drive Talon Right 4
	bool	m_pigeonValid;			// Health indicator for Pigeon IMU

	double	m_driveXScaling;		// Scaling applied to Joystick
	double	m_driveYScaling;		// Scaling applied to Joystick
	double  m_driveSpin;			// Spin turn power  setting

	bool	m_lowGear;				// Low Gear or High Gear
	bool 	m_brakeMode;			// Brake or Coast Mode for Talons

	frc::Timer 	m_safetyTimer;		// Safety timer for use during autonomous modes
	double  m_safetyTimeout; 		// Time in seconds for safety timer
	bool	m_isMovingAuto;			// Indicates an auton movement is active

	double 	m_distTargetInches;		// Drive to Position target inches value
	double	m_distTargetCounts;		// Drive to Position target counts value
	double 	m_distTolInches;		// Tolerated error for MM PID loop

	double 	m_turnAngle = 0.0;		// Desired turn angle from present course
	double	m_turnTolDeg;			// DriveTurn tolerance in degrees
	double 	m_turnKp;				// Proportional value for PID for DriveTurn function
	double	m_visionTurnKp;			// Proportional value for PID for Drive Turn with Vision-Assist
	double 	m_turnMaxOut;			// Max motor output value for PID for DriveTurn function

	double 	m_peakOut;				// Drivetrain maximum speed during movement
	int		m_velocity;				// Drivetrain motion velocity
	int		m_acceleration;			// Drivetrain motion acceleration
	int		m_sCurveStrength;		// Drivetrain motion S curve smoothing strength
	double	m_pidKf;				// Drivetrain PID force constant
	double	m_pidKp;				// Drivetrain PID proportional constant
	double	m_pidKi;				// Drivetrain PID integral constant
	double	m_pidKd;				// Drivetrain PID derivative constant
	double	m_arbFeedForward;		// Drivetrain Motion Magic Arbitrary Feed Forward		

	PIDOutputDriveTurn	*driveTurnPIDOutput;		// Drive turn to angle with gyro
	PIDSourceDriveTurn	*driveTurnPIDSource;		// Drive turn PID source loop
	frc::PIDController	*driveTurnPIDLoop;			// Drive turn PID control

	PIDOutputDriveVision *driveVisionPIDOutput;		// Drive with Vision to angle using gyro - initialize output
	PIDSourceDriveVision *driveVisionPIDSource;		// Drive with Vision PID source loop
	frc::PIDController 	 *driveVisionPIDLoop;		// Drive with Vision PID controller loop

public:
	Drivetrain();
	void InitDefaultCommand() override;
	void Periodic() override;

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

	void Initialize(void);
	void FaultDump(void);
	void MoveWithJoystick(std::shared_ptr<frc::Joystick>, std::shared_ptr<frc::Joystick>);
	void MoveSpin(bool spinRight);
	void MoveStop();

	// Shifting Gears
    void MoveShiftGears(bool lowGear);
    // Brake or Coast Mode
    void MoveSetBrakeMode(bool m_brakeMode);

	// Conversion Functions
	double InchesToCounts(double inches);
	double CountsToInches(int counts);

	double GetEncoderPosition(int motorID);
	
	// Motion Magic Test - Moves to a Position
	void MoveDriveDistanceMMInit(double inches);
	void MoveDriveDistanceMMExecute();
	bool MoveDriveDistanceMMIsFinished();
	void MoveDriveDistanceMMEnd();

	void MoveDriveTurnPIDInit(double angle);
    void MoveDriveTurnPIDExecute();
    bool MoveDriveTurnPIDIsFinished();
    void MoveDriveTurnPIDEnd();

	bool PigeonIMUInitialize();
	void PigeonIMUFaultDump(void);
	double GetIMUHeading();

	void ResetSensors(); 
};

#endif
