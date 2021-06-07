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
// Subsystem outline and order
//
// RobotBuilder methods in all subsystems
//     Constructor
//     Periodic
//     SimulationPeriodic
//
// frc2135 methods in all subsystems
//     Initialize
//     FaultDump
//
// Initialization helpers
//     <config file loading>
//     <talon initialization>
//     <sensor initialization>
//
// Periodic helpers
//     <update sensors>
//     <update dashboard values>
//
// Private methods
//     <getter/setter functions for sensors>
//
// Public command methods
//     <command helpers>
//     <command interfaces>
//         Init
//         Execute
//         IsFinished
//         End
//

#include "frc2135/RobotConfig.h"
#include "frc2135/TalonUtils.h"

#include <frc/Filesystem.h>
#include <frc/RobotBase.h>
#include <frc/RobotController.h>
#include <frc/RobotState.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <fstream>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <wpi/SmallString.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "subsystems/Drivetrain.h"

#include <frc/smartdashboard/SmartDashboard.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

Drivetrain::Drivetrain()
{
    SetName("Drivetrain");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    SetSubsystem("Drivetrain");

    AddChild("Diff Drive", &m_diffDrive);
    m_diffDrive.SetSafetyEnabled(true);
    m_diffDrive.SetExpiration(0.1);
    m_diffDrive.SetMaxOutput(1.0);

    AddChild("Shifter", &m_shifter);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    //  Validate Talon controllers, reset and display firmware versions
    m_talonValidL1 = frc2135::TalonUtils::TalonCheck(m_motorL1, "DT", "L1");
    m_talonValidL2 = frc2135::TalonUtils::TalonCheck(m_motorL2, "DT", "L2");
    m_talonValidR3 = frc2135::TalonUtils::TalonCheck(m_motorR3, "DT", "R3");
    m_talonValidR4 = frc2135::TalonUtils::TalonCheck(m_motorR4, "DT", "R4");
    m_pigeonValid = frc2135::TalonUtils::PigeonIMUInitialize(m_pigeonIMU);

    //  Load config file values
    ConfigFileLoad();

    //  Initialize Talon motor controllers
    if (m_talonValidL1)
        TalonMasterInitialize(m_motorL1);
    if (m_talonValidL2)
        TalonFollowerInitialize(m_motorL2, 1);
    if (m_talonValidR3)
        TalonMasterInitialize(m_motorR3);
    if (m_talonValidR4)
        TalonFollowerInitialize(m_motorR4, 3);

    // Set to first drive mode option
    m_curDriveMode = DRIVEMODE_LAST;
    ToggleDriveMode();

    // If either master drive talons are valid, enable safety timer
    m_diffDrive.SetSafetyEnabled(m_talonValidL1 || m_talonValidR3);

    // Set up Field 2d for simulator
    frc::SmartDashboard::PutData("Field", &m_field);

    // Velocity Control Loop PID Controllers
    m_leftPIDController = frc2::PIDController(m_vcpidKp, m_vcpidKi, m_vcpidKd);
    m_rightPIDController = frc2::PIDController(m_vcpidKp, m_vcpidKi, m_vcpidKd);

    // Vision-based PID Controller
    driveVisionPIDLoop = frc2::PIDController(m_visionTurnKp, 0.0, 0.0);

    // Ramsete PID Controllers
    m_leftController = frc2::PIDController(DriveConstants::kPDriveVel, 0, 0);
    m_rightController = frc2::PIDController(DriveConstants::kPDriveVel, 0, 0);

    m_ramseteController = frc::RamseteController(DriveConstants::kRamseteB, DriveConstants::kRamseteZeta);
    LoadTrajectory();

    // Simulation only - quadrature encoders
    m_leftEncoder.SetDistancePerPulse(DriveConstants::kEncoderMetersPerCount.to<double>());
    m_rightEncoder.SetDistancePerPulse(DriveConstants::kEncoderMetersPerCount.to<double>());

    Initialize();
}

void Drivetrain::Periodic()
{
    // Put code here to be run every loop
    UpdateOdometry();
    UpdateDashboardValues();
    m_field.SetRobotPose(m_odometry.GetPose());
}

void Drivetrain::SimulationPeriodic()
{
    // This method will be called once per scheduler run when in simulation
    m_driverSim.SetInputs(
        units::volt_t{ m_motorL1.Get() } * frc::RobotController::GetInputVoltage(),
        units::volt_t{ -m_motorR3.Get() } * frc::RobotController::GetInputVoltage());
    m_driverSim.Update(20_ms);

    m_leftEncoderSim.SetDistance(m_driverSim.GetLeftPosition().to<double>());
    m_leftEncoderSim.SetRate(m_driverSim.GetLeftVelocity().to<double>());
    m_rightEncoderSim.SetDistance(m_driverSim.GetRightPosition().to<double>());
    m_rightEncoderSim.SetRate(m_driverSim.GetRightVelocity().to<double>());
    m_gyroSim.SetAngle(-m_driverSim.GetHeading().Degrees());
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

///////////////////////////////////////////////////////////////////////////////
//
//  Put methods for controlling this subsystem here. Call these from Commands.
//
void Drivetrain::Initialize(void)
{
    std::printf("2135: DT Initialize\n");

    // When disabled, set low gear and coast mode to allow easier pushing
    m_lowGear = true;
    m_brakeMode = false;
    m_throttleZeroed = false;

    // If NOT DISABLED and AUTON mode, set brake mode
    if (!frc::RobotState::IsDisabled())
        if (!frc::RobotState::IsOperatorControl())
            m_brakeMode = true;

    MoveShiftGears(m_lowGear);
    SetBrakeMode(m_brakeMode);
    MoveStop();
}

void Drivetrain::FaultDump(void)
{
    // Dump all Talon faults
    frc2135::TalonUtils::TalonFaultDump("DT L1", m_motorL1);
    frc2135::TalonUtils::TalonFaultDump("DT L2", m_motorL2);
    frc2135::TalonUtils::TalonFaultDump("DT R3", m_motorR3);
    frc2135::TalonUtils::TalonFaultDump("DT R4", m_motorR4);
    // frc2135::TalonUtils::PigeonIMUFaultDump("DT IMU", m_pigeonIMU);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Initialization helper methods
//
void Drivetrain::ConfigFileLoad(void)
{
    //  Retrieve drivetrain modified parameters from RobotConfig
    frc2135::RobotConfig *config = frc2135::RobotConfig::GetInstance();
    config->GetValueAsDouble("DT_DriveXScaling", m_driveXScaling, 1.0);
    config->GetValueAsDouble("DT_DriveYScaling", m_driveYScaling, 1.0);
    config->GetValueAsInt("DT_DriveMode", m_curDriveMode, 0);
    config->GetValueAsDouble("DT_VisionTurnKp", m_visionTurnKp, 0.0);
    config->GetValueAsDouble("DT_VCMaxSpeed", m_vcMaxSpeed, 6.73);
    config->GetValueAsDouble("DT_VCMaxAngSpeed", m_vcMaxAngSpeed, wpi::math::pi);
    config->GetValueAsDouble("DT_VCPIDKp", m_vcpidKp, 1.0);
    config->GetValueAsDouble("DT_VCPIDKi", m_vcpidKi, 0.0);
    config->GetValueAsDouble("DT_VCPIDKd", m_vcpidKd, 0.0);
    config->GetValueAsDouble("DT_OpenLoopRampRate", m_openLoopRampRate, 1.0);
    config->GetValueAsDouble("DT_ClosedLoopRampRate", m_closedLoopRampRate, 1.0);
    config->GetValueAsDouble("DT_AlignTurnTolerance", m_alignTurnTolerance, 1.0);
    config->GetValueAsDouble("DT_AlignTurnKp", m_alignTurnKp, 0.05);
}

void Drivetrain::TalonMasterInitialize(WPI_BaseMotorController &motor)
{
    //  Setup motor direction, neutral mode, voltage compensation, and encoder
    motor.SetInverted(true);
    motor.SetNeutralMode(NeutralMode::Coast);
    motor.ConfigVoltageCompSaturation(12.0, kCANTimeout);
    motor.EnableVoltageCompensation(true);

    motor.Set(ControlMode::PercentOutput, 0.0);
    motor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor, kPidIndex, kCANTimeout);
    motor.SetSensorPhase(false);
    motor.SetSelectedSensorPosition(0, kPidIndex, kCANTimeout);

    motor.ConfigOpenloopRamp(m_openLoopRampRate, kCANTimeout);
    motor.ConfigClosedloopRamp(m_closedLoopRampRate, kCANTimeout);
}

void Drivetrain::TalonFollowerInitialize(WPI_BaseMotorController &motor, int master)
{
    motor.Set(ControlMode::Follower, master);
    motor.SetInverted(InvertType::FollowMaster);
    motor.SetNeutralMode(NeutralMode::Coast);
    motor.ConfigVoltageCompSaturation(12.0, kCANTimeout);
    motor.EnableVoltageCompensation(true);
}

///////////////////////////////////////////////////////////////////////////////
//
//  Periodic helper methods
//
void Drivetrain::UpdateOdometry(void)
{
    m_odometry.Update(
        frc::Rotation2d(radian_t(GetHeadingAngle())),
        GetDistanceMetersLeft(),
        GetDistanceMetersRight());

    // Gather all odometry and telemetry
    if (frc::RobotBase::IsReal())
    {
        if (m_talonValidL1)
        {
            m_encoderLeft = m_motorL1.GetSelectedSensorPosition(kPidIndex); // counts
            m_velocityLeft = m_motorL1.GetSelectedSensorVelocity() * 10;    // counts/second
        }
        if (m_talonValidR3)
        {
            m_encoderRight = -m_motorR3.GetSelectedSensorPosition(kPidIndex); // counts
            m_velocityRight = m_motorR3.GetSelectedSensorVelocity() * 10;     // counts/second
        }

        if (m_driveDebug)
        {
            if (m_talonValidL1)
                m_currentl1 = m_motorL1.GetOutputCurrent();
            if (m_talonValidL2)
                m_currentL2 = m_motorL2.GetOutputCurrent();
            if (m_talonValidR3)
                m_currentR3 = m_motorR3.GetOutputCurrent();
            if (m_talonValidR4)
                m_currentR4 = m_motorR4.GetOutputCurrent();
        }
    }
}

void Drivetrain::UpdateDashboardValues(void)
{
    static int periodicInterval = 0;

    frc::SmartDashboard::PutNumber("DT_Encoder_L", m_encoderLeft);
    frc::SmartDashboard::PutNumber("DT_Encoder_R", m_encoderRight);
    frc::SmartDashboard::PutNumber("DT_Heading", m_headingDeg);

    frc::SmartDashboard::PutNumber("DT_Current_L1", m_currentl1);
    frc::SmartDashboard::PutNumber("DT_Current_L2", m_currentL2);
    frc::SmartDashboard::PutNumber("DT_Current_R3", m_currentR3);
    frc::SmartDashboard::PutNumber("DT_Current_R4", m_currentR4);

    // Only update indicators every 100 ms to cut down on network traffic
    if ((periodicInterval++ % 5 == 0) && (m_driveDebug > 1))
    {
        double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

        //change to spdlog
        std::printf(
            "2135: DT %6.3f deg %4.1f LR cts %5d %5d amps %6.3f %6.3f %6.3f %6.3f\n",
            secs,
            m_headingDeg,
            m_encoderLeft,
            m_encoderRight,
            m_currentl1,
            m_currentL2,
            m_currentR3,
            m_currentR4);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
//  Getters/Setters
//
//  Wheel encoders
//
void Drivetrain::ResetEncoders()
{
    if (frc::RobotBase::IsReal())
    {
        m_motorL1.SetSelectedSensorPosition(0);
        m_motorR3.SetSelectedSensorPosition(0);
    }

    else
    {
        m_leftEncoder.Reset();
        m_rightEncoder.Reset();
    }
}

meter_t Drivetrain::GetDistanceMetersLeft()
{
    if (frc::RobotBase::IsReal())
    {
        return DriveConstants::kEncoderMetersPerCount * m_motorL1.GetSelectedSensorPosition(kPidIndex);
    }
    else
    {
        return m_leftEncoder.GetDistance() * 1_m;
    }
}

meter_t Drivetrain::GetDistanceMetersRight()
{
    if (frc::RobotBase::IsReal())
    {
        return DriveConstants::kEncoderMetersPerCount * m_motorR3.GetSelectedSensorPosition(kPidIndex);
    }
    else
    {
        return m_rightEncoder.GetDistance() * 1_m;
    }
}

meter_t Drivetrain::GetAverageEncoderDistance()
{
    return (GetDistanceMetersLeft() + GetDistanceMetersRight()) / 2.0;
}

frc::DifferentialDriveWheelSpeeds Drivetrain::GetWheelSpeedsMPS()
{
    meters_per_second_t leftVelocity;
    meters_per_second_t rightVelocity;

    if (frc::RobotBase::IsReal())
    {
        leftVelocity = DriveConstants::kEncoderMetersPerCount * m_motorL1.GetSelectedSensorVelocity() * 10 / 1_s;
        rightVelocity = DriveConstants::kEncoderMetersPerCount * m_motorR3.GetSelectedSensorVelocity() * 10 / 1_s;
    }
    else
    {
        leftVelocity = m_leftEncoder.GetRate() * 1_mps;
        rightVelocity = m_rightEncoder.GetRate() * 1_mps;
    }
    return { leftVelocity, rightVelocity };
}

//
//  Gyro angle
//
double Drivetrain::GetHeading()
{
    return -std::remainder(m_headingDeg, 360);
}

degree_t Drivetrain::GetHeadingAngle()
{
    // if (frc::RobotBase::IsReal())
    // {
    //     return (-m_pigeonIMU.GetFusedHeading() * 1_deg);
    // }
    // else
    // {
        return (-m_gyro.GetAngle() * 1_deg);
    // }
}

double Drivetrain::GetTurnRate()
{
    //  TODO: Pigeon does not appear to have a turn rate - investigate
    //   return -m_pigeonIMU.GetFusedHeading();
    return 0;
}

//
//  Odometry

void Drivetrain::ResetOdometry(frc::Pose2d pose)
{
    ResetEncoders();
    m_driverSim.SetPose(pose);
    m_odometry.ResetPosition(pose, frc::Rotation2d(degree_t(GetHeading())));
}

frc::Pose2d Drivetrain::GetPose()
{
    return m_odometry.GetPose();
}

///////////////////////////////////////////////////////////////////////////////
//
//  Set Talon brake/coast mode
//
void Drivetrain::SetBrakeMode(bool brakeMode)
{
    m_brakeMode = brakeMode;

    std::printf("2135: DT %s Mode\n", (brakeMode) ? "BRAKE" : "COAST");
    frc::SmartDashboard::PutBoolean("DT Brake Mode", brakeMode);

    NeutralMode brakeOutput;
    brakeOutput = (brakeMode) ? NeutralMode::Brake : NeutralMode::Coast;
    if (m_talonValidL1)
        m_motorL1.SetNeutralMode(brakeOutput);
    if (m_talonValidL2)
        m_motorL2.SetNeutralMode(brakeOutput);
    if (m_talonValidR3)
        m_motorR3.SetNeutralMode(brakeOutput);
    if (m_talonValidR4)
        m_motorR4.SetNeutralMode(brakeOutput);
}

//
//  Voltage-based tank drive
//
void Drivetrain::TankDriveVolts(volt_t left, volt_t right)
{
    m_diffDrive.Feed();
    m_motorL1.SetVoltage(left);
    m_motorR3.SetVoltage(-right);
}

//
//  Velocity Control Loop Drive
//
void Drivetrain::VelocityCLDrive(const frc::DifferentialDriveWheelSpeeds &targetWheelSpeeds)
{
    // calculates FF output contribution
    volt_t leftFFVolts = m_feedforward.Calculate(targetWheelSpeeds.left);
    volt_t rightFFVolts = m_feedforward.Calculate(targetWheelSpeeds.right);

    // calculates PID feedback output contribution
    frc::DifferentialDriveWheelSpeeds curSpeed = GetWheelSpeedsMPS();
    double leftFBOutput =
        m_leftPIDController.Calculate(curSpeed.left.to<double>(), targetWheelSpeeds.left.to<double>());
    double rightFBOutput =
        m_rightPIDController.Calculate(curSpeed.right.to<double>(), targetWheelSpeeds.right.to<double>());

    // Divide FF by 12 to normalize to the same units as the outputs
    // TODO: Verify units on PID constants (are they scaled -1.0 to 1.0 or in volts)
    double leftTotalOutput = -(leftFBOutput + double(leftFFVolts) / 12.0);
    double rightTotalOutput = rightFBOutput + double(rightFFVolts) / 12.0;

    // Apply the calculated values to the motors
    m_motorL1.Set(ControlMode::PercentOutput, leftTotalOutput);
    m_motorR3.Set(ControlMode::PercentOutput, rightTotalOutput);

    if (m_driveDebug > 0)
    {
        frc::SmartDashboard::PutNumber("Vel_leftFF", -leftFFVolts.to<double>());
        frc::SmartDashboard::PutNumber("Vel_rightFF", rightFFVolts.to<double>());
        frc::SmartDashboard::PutNumber("Vel_curSpeed.left", curSpeed.left.to<double>());
        frc::SmartDashboard::PutNumber("Vel_curSpeed.right", curSpeed.right.to<double>());
        frc::SmartDashboard::PutNumber("Vel_targetWheelSpeeds.left", targetWheelSpeeds.left.to<double>());
        frc::SmartDashboard::PutNumber("Vel_targetWheelSpeed.right", targetWheelSpeeds.right.to<double>());
        frc::SmartDashboard::PutNumber("Vel_leftFBOutput", -leftFBOutput);
        frc::SmartDashboard::PutNumber("Vel_rightFBOutput", rightFBOutput);
        frc::SmartDashboard::PutNumber("Vel_leftTotalOutput", leftTotalOutput);
        frc::SmartDashboard::PutNumber("Vel_rightTotalOutput", rightTotalOutput);
        frc::SmartDashboard::PutNumber(
            "Vel_diffCurrent",
            curSpeed.right.to<double>() - curSpeed.left.to<double>());
        frc::SmartDashboard::PutNumber("Vel_diffOutput", rightFBOutput - leftFBOutput);
    }
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////// Public Interfaces ///////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
//  Reset all sensors prior to autonomous
//
void Drivetrain::ResetSensors(void)
{
    if (m_talonValidL1)
        m_motorL1.SetSelectedSensorPosition(0, kPidIndex, 0);

    if (m_talonValidR3)
        m_motorR3.SetSelectedSensorPosition(0, kPidIndex, 0);

    if (m_pigeonValid)
    {
        m_pigeonIMU.SetYaw(0.0);
        m_pigeonIMU.SetFusedHeading(0.0, 0);
    }
}

//
//  Set quick turn for curvature drive
//
void Drivetrain::MoveSetQuickTurn(bool quickTurn)
{
    m_isQuickTurn = quickTurn;
}

//
//  Shift transmission gearing
//
void Drivetrain::MoveShiftGears(bool lowGear)
{
    m_lowGear = lowGear;

    std::printf("2135: DT %s Gear\n", (lowGear) ? "LOW" : "HIGH");
    frc::SmartDashboard::PutBoolean("DT Low Gear", lowGear);

    m_shifter.Set((lowGear) ? m_shifter.kForward : m_shifter.kReverse);
}

//
//  Drive stop - used to feed the motors when stopped
//
void Drivetrain::MoveStop()
{
    if (m_talonValidL1 || m_talonValidR3)
        m_diffDrive.TankDrive(0.0, 0.0, false);
}

//
//  Joystick movement during Teleop
//
void Drivetrain::MoveWithJoysticks(frc::XboxController *throttleJstick)
{
    double xValue = 0.0;
    double yValue = 0.0;

    xValue = throttleJstick->GetX(frc::GenericHID::JoystickHand::kRightHand);
    yValue = throttleJstick->GetY(frc::GenericHID::JoystickHand::kLeftHand);

    xValue *= m_driveXScaling;
    if (!m_lowGear)
        yValue *= m_driveYScaling;

    if (m_talonValidL1 || m_talonValidR3)
    {
        // If joystick reports a very small throttle value
        if (fabs(yValue) < 0.05)
            m_throttleZeroed = true;

        // If throttle not zeroed, prevent joystick inputs from entering drive
        if (!m_throttleZeroed)
        {
            xValue = 0.0;
            yValue = 0.0;
        }
    }

    feet_per_second_t ySpeed = 0.0_fps;
    radians_per_second_t rot = 0.0_rad_per_s;

    switch (m_curDriveMode)
    {
        default:
        case DRIVEMODE_CURVATURE:
            m_diffDrive.CurvatureDrive(-yValue, xValue,
                                       m_isQuickTurn); // Boolean is for quick turn or not
            break;

        case DRIVEMODE_VELCONTROL:
            double yValueSquared = yValue * abs(yValue);
            double xValueSquared = xValue * abs(xValue);

            m_vcMaxSpeed = (m_lowGear) ? 6.73 : 16.77; //fps
            frc::SmartDashboard::PutBoolean("Robot in low gear", m_lowGear);

            ySpeed = yValueSquared * feet_per_second_t(m_vcMaxSpeed);
            rot = xValueSquared * radians_per_second_t(m_vcMaxAngSpeed);
            VelocityCLDrive(m_kinematics.ToWheelSpeeds({ ySpeed, 0_fps, rot }));
            break;
    }
}

void Drivetrain::ToggleDriveMode()
{
    if (++m_curDriveMode >= DRIVEMODE_LAST)
        m_curDriveMode = DRIVEMODE_FIRST;

    std::printf("2135: ToggleDriveMode: %d (curr)\n", m_curDriveMode);
    frc::SmartDashboard::PutNumber("DriveMode", m_curDriveMode);
}

//
//  Trajectory management
//
bool Drivetrain::LoadTrajectory()
{
    wpi::SmallString<64> outputDirectory;
    frc::filesystem::GetDeployDirectory(outputDirectory);
    outputDirectory.append("/output/testPath.wpilib.json");
    spdlog::info("Output Directory is {}", outputDirectory);
    std::ifstream pathFile(outputDirectory.c_str());
    if (pathFile.good())
    {
        spdlog::info("pathFile is good");
    }
    else
    {
        spdlog::error("pathFile not good");
    };
    return pathFile.good();
}

void Drivetrain::PlotTrajectory(frc::Trajectory trajectory)
{
#ifndef _WIN32 // Disable on Windows due to linker and runtime issues
    // std::vector<frc::Pose2d> poses;
    std::vector<frc::Trajectory::State> states = trajectory.States();
    std::vector<frc::Pose2d> poses;
    for (size_t i = 0; i < states.size(); i++)
        poses.push_back(states[i].pose);
    m_field.GetObject("trajectory")->SetPoses(poses);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
//  Autonomous command - Vision assisted drive
//
void Drivetrain::MoveAlignTurnInit(double angle)
{
    m_alignTurnError = angle;
    std::printf("2135: DTAT Init - Error %5.2f degrees\n", m_alignTurnError);
}

void Drivetrain::MoveAlignTurnExecute(frc::XboxController *throttleJstick, double angle)
{
    double throttle = 0.0;
    double alignTurnAdjustment = 0.0;

    // If no separate turn stick, then assume Thrustmaster HOTAS 4 z-axis
    throttle = throttleJstick->GetY(frc::GenericHID::JoystickHand::kLeftHand);

    m_alignTurnError = angle;
    alignTurnAdjustment = m_alignTurnError * m_alignTurnKp;

    double leftThrottle = throttle - alignTurnAdjustment;
    double rightThrottle = throttle + alignTurnAdjustment;

    if (m_driveDebug)
    {
        std::printf(
            "2135: DTAT - Error %5.2f degrees Adjustment %5.2f Left Throttle %5.2f Right Throttle %5.2f\n",
            m_alignTurnError,
            alignTurnAdjustment,
            leftThrottle,
            rightThrottle);
    }

    m_diffDrive.TankDrive(leftThrottle, rightThrottle);
}

bool Drivetrain::MoveAlignTurnIsFinished(double angle)
{
    bool isFinished = false;

    m_alignTurnError = angle;

    if (abs(m_alignTurnError) < m_alignTurnTolerance)
    {
        std::printf("2135: DTAT - Error Within Tolerance\n");
        isFinished = true;
    }

    // Check to see if the Safety Timer has timed out.
    if (m_safetyTimer.Get() >= m_safetyTimeout)
    {
        std::printf("2135: DTAT Safety timer has timed out\n");
        isFinished = true;
    }

    return isFinished;
}

void Drivetrain::MoveAlignTurnEnd(void) {}

///////////////////////////////////////////////////////////////////////////////
//
//  Autonomous command - Ramsete follower
//
void Drivetrain::RamseteFollowerInit(void)
{
    // Get our trajectory
    // TODO: Move this to be able to load a trajectory while disabled when the user changes the chooser selection

    wpi::SmallString<64> outputDirectory;
    frc::filesystem::GetDeployDirectory(outputDirectory);
    outputDirectory.append("/output/curvePath.wpilib.json");
    spdlog::info("Output Directory is: {}", outputDirectory);
    std::ifstream pathFile(outputDirectory.c_str());
    if (pathFile.good())
    {
        spdlog::info("pathFile is good");
    }
    else
    {
        spdlog::error("pathFile not good");
    };

    m_trajectory = frc::TrajectoryUtil::FromPathweaverJson(outputDirectory);
    PlotTrajectory(m_trajectory);
    std::vector<frc::Trajectory::State> trajectoryStates;
    trajectoryStates = m_trajectory.States();
    m_trajTimer.Reset();
    m_trajTimer.Start();

    spdlog::info("Size of state table is {}", trajectoryStates.size());

    for (unsigned int i = 0; i < trajectoryStates.size(); i++)
    {
        frc::Trajectory::State curState = trajectoryStates[i];
        spdlog::info(
            "state time {} Velocity {} Accleration {} Rotation {}",
            curState.t,
            curState.velocity,
            curState.acceleration,
            curState.pose.Rotation().Degrees());
    }

#if 0 // REMOVE - only for onboard trajectory generation
    //  Our trajectory maxSpeed/maxAccel will come from PathWeaver
    // Set up config for trajectory
    frc::TrajectoryConfig config(kMaxSpeed, kMaxAcceleration);

    // Add kinematics to ensure max speed is actually obeyed
    config.SetKinematics(m_kinematics);

    // Apply the voltage constraint
    config.AddConstraint(autoVoltageConstraint);

    // Create a voltage constraint to ensure we don't accelerate too fast
    frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(m_feedforward, m_kinematics, 10_V);
#endif

    // This initializes the odometry (where we are) and tolerance
    ResetOdometry(m_trajectory.InitialPose());

    // TODO: should reset trajectory states here

    double dashValue;
    dashValue = frc::SmartDashboard::GetNumber("L_Ctr", 0.99);
    m_leftController.SetTolerance(dashValue);
    m_rightController.SetTolerance(dashValue);
}

void Drivetrain::RamseteFollowerExecute(void)
{
    frc::ChassisSpeeds targetChassisSpeeds;
    frc::DifferentialDriveWheelSpeeds targetWheelSpeeds;

    // Need to step through the states through the trajectory
    frc::Trajectory::State trajState;
    frc::Pose2d currentPose;
    trajState = m_trajectory.Sample(m_trajTimer.Get() * 1_s);
    currentPose = GetPose();

    targetChassisSpeeds = m_ramseteController.Calculate(currentPose, trajState);
    targetWheelSpeeds = m_kinematics.ToWheelSpeeds(targetChassisSpeeds);

    // Calculates FF output contribution to reach the speed
    volt_t leftFFVolts = m_feedforward.Calculate(targetWheelSpeeds.left);
    volt_t rightFFVolts = m_feedforward.Calculate(targetWheelSpeeds.right);

    // Calculate PID feedback output contribution to reach the speed
    frc::DifferentialDriveWheelSpeeds curSpeed = GetWheelSpeedsMPS();
    double leftFBOutput =
        m_leftController.Calculate(curSpeed.left.to<double>(), targetWheelSpeeds.left.to<double>());
    double rightFBOutput =
        m_rightController.Calculate(curSpeed.right.to<double>(), targetWheelSpeeds.right.to<double>());

    // Divide FF by 12 to normalize to the same units as the outputs
    // TODO: Verify units on PID constants (are they scaled -1.0 to 1.0 or in volts)
    leftFBOutput = 0;
    rightFBOutput = 0;

    double leftTotalOutput = leftFBOutput + double(leftFFVolts) / 12.0;
    double rightTotalOutput = rightFBOutput + double(rightFFVolts) / 12.0;

    // Apply the calculated values to the motors
    m_diffDrive.TankDrive(leftTotalOutput, rightTotalOutput);

    spdlog::info(
        "cX {} cY {} cR {} tX {} tY {} tR {} lDist {} rDist {} tSpdX {} tSpdY {} tSpdO {} tLSpd {} tRSpd {}",
        currentPose.X(),
        currentPose.Y(),
        currentPose.Rotation().Degrees(),
        trajState.pose.X(),
        trajState.pose.Y(),
        trajState.pose.Rotation().Degrees(),
        m_driverSim.GetLeftPosition(),
        m_driverSim.GetRightPosition(),
        targetChassisSpeeds.vx,
        targetChassisSpeeds.vy,
        targetChassisSpeeds.omega,
        targetWheelSpeeds.left,
        targetWheelSpeeds.right);
}

bool Drivetrain::RamseteFollowerIsFinished(void)
{
    return ((m_trajTimer.Get() * 1_s) >= m_trajectory.TotalTime());
}

void Drivetrain::RamseteFollowerEnd(void)
{
    m_trajTimer.Stop();
}
