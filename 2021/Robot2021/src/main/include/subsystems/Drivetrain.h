// RobotBuilder Version: 3.1
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
//

#pragma once

#include "Constants.h"
#include "Vision.h"

#include <frc/ADXRS450_Gyro.h>
#include <frc/Encoder.h>
#include <frc/XboxController.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/simulation/ADXRS450_GyroSim.h>
#include <frc/simulation/DifferentialDrivetrainSim.h>
#include <frc/simulation/EncoderSim.h>
#include <frc/smartdashboard/Field2d.h>
#include <frc/system/plant/LinearSystemId.h>
#include <frc/trajectory/Trajectory.h>
#include <units/acceleration.h>
#include <units/angle.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>
#include <wpi/math>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "ctre/Phoenix.h"

#include <frc/DoubleSolenoid.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc2/command/SubsystemBase.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

using namespace units;
using namespace units::angle;
using namespace units::length;
using namespace units::literals;
using namespace units::time;
using namespace units::velocity;
using namespace units::acceleration;
using namespace units::angular_velocity;
using namespace units::angular_acceleration;

/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain : public frc2::SubsystemBase
{
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities

#ifdef __FRC_ROBORIO__
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    WPI_TalonFX m_motorL1{ 1 };
    WPI_TalonFX m_motorR3{ 3 };
    frc::DifferentialDrive m_diffDrive{ m_motorL1, m_motorR3 };
    WPI_TalonFX m_motorL2{ 2 };
    WPI_TalonFX m_motorR4{ 4 };
    frc::DoubleSolenoid m_shifter{ 0, 0, 7 };
    PigeonIMU m_pigeonIMU{ 0 };
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#else
    WPI_TalonSRX m_motorL1{ 1 };
    WPI_TalonSRX m_motorR3{ 3 };
    frc::DifferentialDrive m_diffDrive{ m_motorL1, m_motorR3 };
    WPI_TalonSRX m_motorL2{ 2 };
    WPI_TalonSRX m_motorR4{ 4 };
    frc::DoubleSolenoid m_shifter{ 0, 0, 7 };
    PigeonIMU m_pigeonIMU{ 0 };
#endif

    // Sensors

    // Simulated quadrature encoders, since TalonFX is not supported
    frc::Encoder m_leftEncoder{ DriveConstants::kLeftEncoderPorts[0], DriveConstants::kLeftEncoderPorts[1] };
    frc::Encoder m_rightEncoder{ DriveConstants::kRightEncoderPorts[0],
                                 DriveConstants::kRightEncoderPorts[1] };
    frc::sim::EncoderSim m_leftEncoderSim{ m_leftEncoder };
    frc::sim::EncoderSim m_rightEncoderSim{ m_rightEncoder };

    // Gyro - same on robot and in simulation
    frc::ADXRS450_Gyro m_gyro;
    frc::sim::ADXRS450_GyroSim m_gyroSim{ m_gyro };

    typedef enum driveMode_e
    { // Driving Algorithms
        DRIVEMODE_FIRST = 0,
        DRIVEMODE_CURVATURE = 1,
        DRIVEMODE_VELCONTROL = 2,
        DRIVEMODE_LAST
    } driveMode_e;

    //    Declare constants
    const int m_driveDebug = 0; // Debug flag to disable extra logging calls
    const int kPidIndex = 0;    // PID slot index for sensors
    const int kCANTimeout = 30; // CAN timeout in msec to wait for response

    /*
    // Create the simulation model of our drivetrain.
    frc::sim::DifferentialDrivetrainSim m_driveSim{
        // Create a linear system from our characterization gains.
        frc::LinearSystemId::IdentifyDrivetrainSystem(KvLinear, KaLinear, KvAngular, KaAngular),
        0.7112_m,                   // The track width is 0.7112 meters.
        frc::DCMotor::GetNEO(2),    // 2 NEO motors on each side of the drivetrain.
        7.29,                       // 7.29:1 gearing reduction.
        3_in,                       // The robot uses 3" radius wheels.

        // The standard deviations for measurement noise:
        // x and y:          0.001 m
        // heading:          0.001 rad
        // l and r velocity: 0.1   m/s
        // l and r position: 0.005 m
        {0.001, 0.001, 0.001, 0.1, 0.1, 0.005, 0.005}
        };

    static constexpr auto KvAngular = 1.5_V / 1_rad_per_s;
    static constexpr auto KaAngular = 0.3_V / 1_rad_per_s_sq;
    */

    // TODO: adjust kV and kA angular from robot characterization
    frc::sim::DifferentialDrivetrainSim m_driverSim{
        frc::LinearSystemId::IdentifyDrivetrainSystem(DriveConstants::kv, DriveConstants::ka, DriveConstants::KvAngular, DriveConstants::KaAngular),
        DriveConstants::kTrackWidthMeters,
        frc::DCMotor::Falcon500(2),
        DriveConstants::kGearRatio,
        DriveConstants::kWheelDiaMeters / 2
    };

    // Declare module variables
    bool m_talonValidL1; // Health indicator for drive Talon Left 1
    bool m_talonValidL2; // Health indicator for drive Talon Left 2
    bool m_talonValidR3; // Health indicator for drive Talon Right 3
    bool m_talonValidR4; // Health indicator for drive Talon Right 4
    bool m_pigeonValid;  // Health indicator for Pigeon IMU

    // Joysticks
    double m_driveXScaling; // Scaling applied to Joystick
    double m_driveYScaling; // Scaling applied to Joystick
    bool m_throttleZeroed;  // Throttle joystick zeroed check for safety

    // Talon input filter settings
    double m_openLoopRampRate;
    double m_closedLoopRampRate;

    // Drive modes
    bool m_brakeMode;   // Brake or Coast Mode for Talons
    bool m_lowGear;     // Low Gear or High Gear
    int m_curDriveMode; // Current driving mode, arcade by default
    bool m_isQuickTurn; // Setting for quickturn in curvature drive

    // Drive turn PID settings
    double m_visionTurnKp = 1.0; // Proportional value for PID for Drive Turn with Vision-Assist
    double m_alignTurnTolerance; // Minimum align turn error to finish aligning
    double m_alignTurnKp;
    double m_alignTurnError;

    // Odometry and telemetry
    int m_encoderLeft = 0;     // Distance from Falcon - left side - counts
    int m_encoderRight = 0;    // Distance from Falcon - right side - counts
    int m_velocityLeft = 0;    // Velocity from Falcon - left side - counts/second
    int m_velocityRight = 0;   // Velocity from Falcon - right side - counts/second
    double m_currentl1 = 0.0;  // Motor L1 output current from Falcon
    double m_currentL2 = 0.0;  // Motor L2 output current from Falcon
    double m_currentR3 = 0.0;  // Motor R3 output current from Falcon
    double m_currentR4 = 0.0;  // Motor R4 output current from Falcon
    double m_headingDeg = 0.0; // Pigeon IMU heading in degrees

    // Auton safety timer
    frc::Timer m_safetyTimer; // Safety timer for use during autonomous modes
    double m_safetyTimeout;   // Time in seconds for safety timer

    // Velocity closed-loop drive
    double m_vcMaxSpeed;
    double m_vcMaxAngSpeed;
    double m_vcpidKp = 1.0;
    double m_vcpidKi = 0.0;
    double m_vcpidKd = 0.0;

    // Do another drive characterization
    frc::SimpleMotorFeedforward<meter> m_feedforward{ DriveConstants::ks, DriveConstants::kv, DriveConstants::ka };
    frc::DifferentialDriveKinematics m_kinematics{ DriveConstants::kTrackWidthMeters };
    frc::DifferentialDriveOdometry m_odometry{ 0.0_deg };
    frc::Field2d m_field;

    frc2::PIDController m_leftPIDController{ m_vcpidKp, m_vcpidKi, m_vcpidKd };
    frc2::PIDController m_rightPIDController{ m_vcpidKp, m_vcpidKi, m_vcpidKd };

    frc2::PIDController driveVisionPIDLoop{ m_visionTurnKp, 0.0, 0.0 }; // Drive with Vision

    frc2::PIDController m_leftController{ DriveConstants::kPDriveVel, 0.0, 0.0 };
    frc2::PIDController m_rightController{ DriveConstants::kPDriveVel, 0.0, 0.0 };
    frc::RamseteController m_ramseteController;
    frc::Trajectory m_trajectory;
    frc::Timer m_trajTimer;

    ///////////////////////////////////////////////////////////////////////////

    void ConfigFileLoad(void);
    void TalonMasterInitialize(WPI_BaseMotorController &motor);
    void TalonFollowerInitialize(WPI_BaseMotorController &motor, int master);

    void UpdateOdometry(void);
    void UpdateDashboardValues(void);

    void ResetEncoders(void);
    meter_t GetDistanceMetersLeft(void);
    meter_t GetDistanceMetersRight(void);
    meter_t GetAverageEncoderDistance(void);
    frc::DifferentialDriveWheelSpeeds GetWheelSpeedsMPS(void);

    double GetHeading(void);
    degree_t GetHeadingAngle(void);
    double GetTurnRate(void);

    void ResetOdometry(frc::Pose2d pose);
    frc::Pose2d GetPose(void);

    void SetBrakeMode(bool m_brakeMode);
    void TankDriveVolts(volt_t left, volt_t right);
    void VelocityCLDrive(const frc::DifferentialDriveWheelSpeeds &speeds);

    bool LoadTrajectory(void);
    void PlotTrajectory(frc::Trajectory trajectory);

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

    void ResetSensors(void);
    void MoveSetQuickTurn(bool quickTurn);
    void MoveShiftGears(bool lowGear);
    void MoveStop(void);
    void MoveWithJoysticks(frc::XboxController *driverPad);
    void ToggleDriveMode(void);

    // Autonomous - Aligning with Target Using Vision Processing
    void MoveAlignTurnInit(double angle);
    void MoveAlignTurnExecute(frc::XboxController *throttleJstick, double angle);
    bool MoveAlignTurnIsFinished(double angle);
    void MoveAlignTurnEnd(void);

    // Autonomous - Ramsete follower command
    void RamseteFollowerInit(void);
    void RamseteFollowerExecute(void);
    bool RamseteFollowerIsFinished(void);
    void RamseteFollowerEnd(void);
};
