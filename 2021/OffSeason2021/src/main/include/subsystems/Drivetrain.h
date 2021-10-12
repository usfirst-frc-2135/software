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

#include <frc/drive/DifferentialDrive.h>
#include <frc2/command/SubsystemBase.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

using namespace std;
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
    WPI_TalonFX m_motorR4{ 4 };
    WPI_TalonFX m_motorL2{ 2 };
    frc::DifferentialDrive m_diffDrive{ m_motorL1, m_motorR3 };
    WPI_TalonFX m_motorR3{ 3 };
    WPI_TalonFX m_motorL1{ 1 };

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
#else
    WPI_TalonSRX m_motorL1{ 1 };
    WPI_TalonSRX m_motorR3{ 3 };
    frc::DifferentialDrive m_diffDrive{ m_motorL1, m_motorR3 };
    WPI_TalonSRX m_motorL2{ 2 };
    WPI_TalonSRX m_motorR4{ 4 };
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

    // TODO: adjust kV and kA angular from robot characterization
    frc::sim::DifferentialDrivetrainSim m_driverSim{ frc::LinearSystemId::IdentifyDrivetrainSystem(
                                                         DriveConstants::kv,
                                                         DriveConstants::ka,
                                                         DriveConstants::KvAngular,
                                                         DriveConstants::KaAngular),
                                                     DriveConstants::kTrackWidthMeters,
                                                     frc::DCMotor::Falcon500(2),
                                                     DriveConstants::kGearRatio,
                                                     DriveConstants::kWheelDiaMeters / 2 };
    // Declare module variables
    bool m_talonValidL1; // Health indicator for drive Talon Left 1
    bool m_talonValidL2; // Health indicator for drive Talon Left 2
    bool m_talonValidR3; // Health indicator for drive Talon Right 3
    bool m_talonValidR4; // Health indicator for drive Talon Right 4

    // Joysticks
    double m_driveXScaling;  // Scaling applied to Joystick
    double m_driveYScaling;  // Scaling applied to Joystick
    double m_driveQTScaling; // Scaling applied to Joystick when QuickTurn enabled
    bool m_throttleZeroed;   // Throttle joystick zeroed check for safety

    // Talon input filter settings
    double m_openLoopRampRate;
    double m_closedLoopRampRate;

    // Drive modes
    bool m_brakeMode;   // Brake or Coast Mode for Talons
    int m_curDriveMode; // Current driving mode, arcade by default
    bool m_isQuickTurn; // Setting for quickturn in curvature drive

    // Odometry and telemetry
    meter_t m_distanceLeft;
    meter_t m_distanceRight;
    frc::DifferentialDriveWheelSpeeds m_wheelSpeeds;
    frc::DifferentialDriveOdometry m_odometry{ m_gyro.GetRotation2d() };

    double m_currentl1 = 0.0; // Motor L1 output current from Falcon
    double m_currentL2 = 0.0; // Motor L2 output current from Falcon
    double m_currentR3 = 0.0; // Motor R3 output current from Falcon
    double m_currentR4 = 0.0; // Motor R4 output current from Falcon

    // limelight drive
    double m_turnpidKp = 0.1;
    double m_turnpidKi = 0.0;
    double m_turnpidKd = 0.0;
    double m_throttlepidKp = 0.1;
    double m_throttlepidKi = 0.0;
    double m_throttlepidKd = 0.0;
    double m_maxTurn;
    double m_maxThrottle;
    double m_targetDistance;
    double m_angleThreshold;
    double m_distThreshold;
    double m_throttleShape;
    double m_targetAreaMin;
    double m_targetAreaMax;
    double m_distOffset;

    // Velocity closed-loop drive
    double m_vcMaxSpeed;
    double m_vcMaxAngSpeed;
    double m_vcpidKp = 1.0;
    double m_vcpidKi = 0.0;
    double m_vcpidKd = 0.0;

    // Do another drive characterization
    frc::SimpleMotorFeedforward<meter> m_feedforward{ DriveConstants::ks,
                                                      DriveConstants::kv,
                                                      DriveConstants::ka };
    frc::DifferentialDriveKinematics m_kinematics{ DriveConstants::kTrackWidthMeters };
    frc::Field2d m_field;

    // DriveWithLimelight pid controller objects
    frc2::PIDController m_turnController{ 0.0, 0.0, 0.0 };
    frc2::PIDController m_throttleController{ 0.0, 0.0, 0.0 };

    // Velocity Closed Loop Drive
    frc2::PIDController m_leftPIDController{ m_vcpidKp, m_vcpidKi, m_vcpidKd };
    frc2::PIDController m_rightPIDController{ m_vcpidKp, m_vcpidKi, m_vcpidKd };

    // Ramsete follower objects
    frc2::PIDController m_leftController{ DriveConstants::kPDriveVel, 0.0, 0.0 };
    frc2::PIDController m_rightController{ DriveConstants::kPDriveVel, 0.0, 0.0 };
    frc::RamseteController m_ramseteController;
    frc::Trajectory m_trajectory;
    frc::Timer m_trajTimer;

    // Path following variables
    double m_tolerance;
    bool leftNearStopped;
    bool rightNearStopped;

    ///////////////////////////////////////////////////////////////////////////

    // Initialization methods
    void ConfigFileLoad(void);
    void TalonMasterInitialize(WPI_BaseMotorController &motor);
    void TalonFollowerInitialize(WPI_BaseMotorController &motor, int master);

    // Periodic update methods
    void UpdateOdometry(void);
    void UpdateDashboardValues(void);

    // Encoders
    void ResetEncoders(void);
    meter_t GetDistanceMetersLeft(void);
    meter_t GetDistanceMetersRight(void);
    meter_t GetAverageEncoderDistance(void);
    frc::DifferentialDriveWheelSpeeds GetWheelSpeedsMPS(void);

    void ResetGyro(void);
    degree_t GetHeadingAngle(void);
    degrees_per_second_t GetTurnRate(void);

    void ResetOdometry(frc::Pose2d pose);

    void TankDriveVolts(volt_t left, volt_t right);
    void VelocityCLDrive(const frc::DifferentialDriveWheelSpeeds &speeds);

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
    void SetBrakeMode(bool brakeMode);
    void MoveSetQuickTurn(bool quickTurn);
    void MoveStop(void);
    void MoveWithJoysticks(frc::XboxController *driverPad);

    void MoveWithLimelightInit();
    void MoveWithLimelightExecute(frc::XboxController *driverPad);
    void MoveWithLimelightEnd();

    void ToggleDriveMode(void);

    // Autonomous - Ramsete follower command
    void RamseteFollowerInit(string pathName);
    void RamseteFollowerExecute(void);
    bool RamseteFollowerIsFinished(void);
    void RamseteFollowerEnd(void);
};
