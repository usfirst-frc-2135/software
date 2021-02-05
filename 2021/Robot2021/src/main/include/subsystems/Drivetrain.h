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

#define _USE_MATH_DEFINES
#include <math.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/XboxController.h>
#include <units/angle.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/acceleration.h>
#include "Vision.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include <frc/DoubleSolenoid.h>
#include <frc/drive/DifferentialDrive.h>

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

using namespace units;
using namespace units::angle;
using namespace units::length;
using namespace units::literals;
using namespace units::time;
using namespace units::velocity;

/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public frc2::SubsystemBase
{
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
WPI_TalonFX m_motorL1{1};
WPI_TalonFX m_motorR3{3};
frc::DifferentialDrive m_diffDrive{m_motorL1, m_motorR3};
WPI_TalonFX m_motorL2{2};
WPI_TalonFX m_motorR4{4};
frc::DoubleSolenoid m_shifter{0, 0, 7};
PigeonIMU m_pigeonIMU{0};

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    typedef enum driveMode_e
    {   // Driving Algorithms
        DRIVEMODE_FIRST      = 0,
        DRIVEMODE_ARCADE     = DRIVEMODE_FIRST,
        DRIVEMODE_CURVATURE  = 1,
        DRIVEMODE_VELCONTROL = 2,
        DRIVEMODE_LAST
    } driveMode_e;

    //    Declare constants
    const int       m_driveDebug = 0;               // Debug flag to disable extra logging calls
    const int       m_alignTurnDebug = 0;           // Debug flag to disable extra logging calls
    const int       kPidIndex = 0;                  // PID slot index for sensors
    const int       kCANTimeout = 30;               // CAN timeout in msec to wait for response

    // Drivetrain constants
    const double    kWheelDiaInches = 6.0;          // Measured wheel diameter
    const int       kEncoderCPR = 2048 * 4;         // CPR is 2048 for new TalonFX
    const foot_t    kTrackWidthFeet = 2.125_ft;     // Measured track width

    // Derived values
    const double    kWheelCircumInches = kWheelDiaInches * M_PI;
    const double    kWheelCountsPerInch = kEncoderCPR / kWheelCircumInches;
    const foot_t    kEncoderFeetPerCount = foot_t(kWheelCircumInches / 12.0) / kEncoderCPR;

    const meter_t   kWheelDiameterMeters = 6.0_in;
    // Assumes the encoders are directly mounted on the wheel shafts
    const meter_t   kEncoderMetersPerCount =
        (kWheelDiameterMeters * M_PI) / static_cast<double>(kEncoderCPR);

    // Kinematics values for 2135 Bebula - 2019 B-bot
    static constexpr auto   ks = 0.899_V;
    static constexpr auto   kv = 1.411_V / 1_fps;
    static constexpr auto   ka = 0.21_V / 1_fps_sq;

    // As above, this must be tuned for your drive!
    static constexpr double kPDriveVel = 0.00291;

    const meters_per_second_t            kMaxSpeed = 1.1336_mps;
    const meters_per_second_squared_t    MaxAcceleration = 10.668_mps_sq;

    // Reasonable baseline values for a RAMSETE follower in meters and seconds
    const double            kRamseteB = 2.0;
    const double            kRamseteZeta = 0.7;

    // Declare module variables
    bool            m_talonValidL1;     // Health indicator for drive Talon Left 1
    bool            m_talonValidL2;     // Health indicator for drive Talon Left 2
    bool            m_talonValidR3;     // Health indicator for drive Talon Right 3
    bool            m_talonValidR4;     // Health indicator for drive Talon Right 4
    bool            m_pigeonValid;      // Health indicator for Pigeon IMU

    double          m_driveXScaling;    // Scaling applied to Joystick
    double          m_driveYScaling;    // Scaling applied to Joystick
    bool            m_throttleZeroed;   // Throttle joystick zeroed check for safety
    double          m_driveSpin;        // Spin turn power  setting

    bool            m_lowGear;          // Low Gear or High Gear
    bool            m_brakeMode;        // Brake or Coast Mode for Talons
    int             m_curDriveMode;     // Current driving mode, arcade by default
    bool            m_isQuickTurn;      // Setting for quickturn in curvature drive

    frc::Timer      m_safetyTimer;      // Safety timer for use during autonomous modes
    double          m_safetyTimeout;    // Time in seconds for safety timer
    bool            m_isMovingAuto;     // Indicates an auton movement is active

    // Drive distance Magic Motion settings
    double          m_distTargetInches; // Drive to Position target inches value
    double          m_distTargetCounts; // Drive to Position target counts value
    double          m_distTolInches;    // Tolerated error for MM PID loop

    // Drive turn PID settings
    double          m_turnAngle = 0.0;  // Desired turn angle from present course
    double          m_turnTolDeg;       // DriveTurn tolerance in degrees
    double          m_visionTurnKp = 1.0; // Proportional value for PID for Drive Turn with Vision-Assist
    double          m_turnMaxOut;       // Max motor output value for PID for DriveTurn function
	double          m_alignTurnTolerance; // Minimum align turn error to finish aligning
    double          m_alignTurnKp;
    double          m_alignTurnError;

    // Talon SRX settings for internal PID loop
    double          m_peakOut;          // Drivetrain maximum speed during movement
    int             m_velocity;         // Drivetrain motion velocity
    int             m_acceleration;     // Drivetrain motion acceleration
    int             m_sCurveStrength;   // Drivetrain motion S curve smoothing strength
    double          m_pidKp;            // Drivetrain PID proportional constant
    double          m_pidKi;            // Drivetrain PID integral constant
    double          m_pidKd;            // Drivetrain PID derivative constant

    double          m_openLoopRampRate;
    double          m_closedLoopRampRate;

    double          m_vcMaxSpeed;
    double          m_vcMaxAngSpeed;
    double          m_vcpidKp = 1.0;
    double          m_vcpidKi = 0.0;
    double          m_vcpidKd = 0.0;

    const bool      kGyroReversed = true;

    // Odometry and telemetry
    int             m_encoderLeft = 0;      // Distance from Falcon - left side - counts
    int             m_encoderRight = 0;     // Distance from Falcon - right side - counts
    int             m_velocityLeft = 0;     // Velocity from Falcon - left side - counts/second
    int             m_velocityRight = 0;    // Velocity from Falcon - right side - counts/second
    double          m_currentl1 = 0.0;      // Motor L1 output current from Falcon
    double          m_currentL2 = 0.0;      // Motor L2 output current from Falcon
    double          m_currentR3 = 0.0;      // Motor R3 output current from Falcon
    double          m_currentR4 = 0.0;      // Motor R4 output current from Falcon
    double          m_headingDeg = 0.0;     // Pigeon IMU heading in degrees
    frc::Rotation2d gyroAngle;

    // Do another drive characterization
    frc::SimpleMotorFeedforward<meter>  m_feedforward {ks, kv, ka};
    frc::DifferentialDriveKinematics    m_kinematics {kTrackWidthFeet};
    frc::DifferentialDriveOdometry      m_odometry {gyroAngle};

    frc2::PIDController                 m_leftPIDController {m_vcpidKp, m_vcpidKi, m_vcpidKd};
    frc2::PIDController                 m_rightPIDController {m_vcpidKp, m_vcpidKi, m_vcpidKd};

    frc2::PIDController                 driveVisionPIDLoop {m_visionTurnKp, 0.0, 0.0};   // Drive with Vision PID controller loop

    std::vector<frc::Trajectory::State> trajectoryStates;
    uint32_t                            trajCurState;

    frc2::PIDController                 leftController {kPDriveVel, 0, 0};
    frc2::PIDController                 rightController {kPDriveVel, 0, 0};
    frc::RamseteController              ramseteController;

    ///////////////////////////////////////////////////////////////////////////

    void ConfigFileLoad(void);
    void TalonMasterInitialize(WPI_BaseMotorController &motor);
    void TalonFollowerInitialize(WPI_BaseMotorController &motor, int master);

    void UpdateOdometry(void);
    void UpdateDashboardValues(void);
    void UpdateMotorOutputs(void);

    // Brake or Coast Mode
    void MoveSetBrakeMode(bool m_brakeMode);

    // Conversion Functions
    double InchesToCounts(double inches);
    double CountsToInches(int counts);

    // Velocity Control Loop
    void VelocityCLDrive(const frc::DifferentialDriveWheelSpeeds& speeds);

    ///////////////////////////////////////////////////////////////////////////

    void TankDriveVolts(volt_t left, volt_t right);
    void ResetEncoders();
    meter_t GetAverageEncoderDistance();
    void SetMaxOutput(double maxOutput);
    double GetHeading();
    double GetTurnRate();
    frc::Pose2d GetPose();
    frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();
    void ResetOdometry(frc::Pose2d pose);
    meter_t GetDistanceMeters(int encoderCounts);
    feet_per_second_t GetWheelSpeeds(int encoderCountsPerSecond);
    meters_per_second_t GetVelocityMPS(int encoderCountsPerSecond);
    
    Vision *m_vision;

public:
    Drivetrain();

    void Periodic() override;
    void SimulationPeriodic() override;
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    void Initialize(void);
    void FaultDump(void);

    void ResetSensors();
    void BumpRampRate(bool bumpUp);
    void MoveSetQuickTurn(bool quickTurn);
    void MoveShiftGears(bool lowGear);
    void MoveSpin(bool spinRight);
    void MoveStop();
    void MoveWithJoysticks(frc::XboxController *driverPad);
    void ToggleDriveMode();

    // Autonomous - Driving to a distance using Motion Magic
    void MoveDriveDistanceMMInit(double distance);
    void MoveDriveDistanceMMExecute(void);
    bool MoveDriveDistanceMMIsFinished(void);
    void MoveDriveDistanceMMEnd(void);

    // Autonomous - Aligning with Target Using Vision Processing
    void MoveAlignTurnInit(void);
    void MoveAlignTurnExecute(frc::XboxController *throttleJstick);
    bool MoveAlignTurnIsFinished(void);
    void MoveAlignTurnEnd(void);

    // Autonomous - Ramsete follower command
    void RamseteFollowerInit(void);
    void RamseteFollowerExecute(void);
    bool RamseteFollowerIsFinished(void);
    void RamseteFollowerEnd(void);
};
