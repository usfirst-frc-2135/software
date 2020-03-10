// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include <frc/RobotController.h>
#include <frc/RobotState.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <Subsystems/Drivetrain.h>


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/DriveTeleop.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain")
{

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
motorL1.reset(new WPI_TalonFX(1));


motorR3.reset(new WPI_TalonFX(3));


diffDrive.reset(new frc::DifferentialDrive(*motorL1, *motorR3));
AddChild("Diff Drive", diffDrive);
diffDrive->SetSafetyEnabled(true);
diffDrive->SetExpiration(0.25);
diffDrive->SetMaxOutput(1.0);

motorL2.reset(new WPI_TalonFX(2));


motorR4.reset(new WPI_TalonFX(4));


shifter.reset(new frc::DoubleSolenoid(0, 0, 7));
AddChild("Shifter", shifter);

pigeonIMU.reset(new PigeonIMU(20));



    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	//Validate Talon FX controllers, initialize and display firmware versions
	m_talonValidL1 = frc2135::TalonUtils::TalonCheck(motorL1, "DT", "L1");
	m_talonValidL2 = frc2135::TalonUtils::TalonCheck(motorL2, "DT", "L2");
	m_talonValidR3 = frc2135::TalonUtils::TalonCheck(motorR3, "DT", "R3");
	m_talonValidR4 = frc2135::TalonUtils::TalonCheck(motorR4, "DT", "R4");

	// Retrieve drivetrain modified parameters from RobotConfig
	frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
	config->GetValueAsDouble("DT_DriveXScaling", m_driveXScaling, 1.0);
	config->GetValueAsDouble("DT_DriveYScaling", m_driveYScaling, 1.0);
	config->GetValueAsDouble("DT_DriveSpin", m_driveSpin, 0.45);
	config->GetValueAsDouble("DT_PidTurnKp", m_turnKp, 0.030);
	config->GetValueAsDouble("DT_VisionTurnKp", m_visionTurnKp, 0.0);
	config->GetValueAsDouble("DT_PeakOut", m_peakOut, 1.0);
	config->GetValueAsInt("DT_Velocity", m_velocity, 1918);
	config->GetValueAsInt("DT_Acceleration", m_acceleration, 3836);
	config->GetValueAsInt("DT_SCurveStrength", m_sCurveStrength, 0);
	config->GetValueAsDouble("DT_PidKf", m_pidKf, 0.0);
	config->GetValueAsDouble("DT_PidKp", m_pidKp, 0.25);
	config->GetValueAsDouble("DT_PidKi", m_pidKi, 0.0);
	config->GetValueAsDouble("DT_PidKd", m_pidKd, 0.0);
	config->GetValueAsDouble("DT_ArbFeedForward", m_arbFeedForward, 0.0);
	config->GetValueAsDouble("DT_VCMaxSpeed", m_vcMaxSpeed, 6.73);
	config->GetValueAsDouble("DT_VCMaxAngSpeed", m_vcMaxAngSpeed, M_PI);
	config->GetValueAsDouble("DT_VCPIDKp", m_vcpidKp, 1.0);
	config->GetValueAsDouble("DT_VCPIDKi", m_vcpidKi, 0.0);
	config->GetValueAsDouble("DT_VCPIDKd", m_vcpidKd, 0.0);
	config->GetValueAsInt("DT_DriveMode", m_curDriveMode, 0);
	config->GetValueAsDouble("DT_OpenLoopRampRate", m_openLoopRampRate, 1.0);
	config->GetValueAsDouble("DT_ClosedLoopRampRate", m_closedLoopRampRate, 1.0);

    // Invert the direction of the motors
    // Set to brake mode (in comparison to coast)
    // Set voltage compensation to 12V
    // Set encoder as a CTRE magnetic in relative mode with sensor in phase with output
    if (m_talonValidL1)
	{
        motorL1->SetInverted(true);
        motorL1->SetNeutralMode(NeutralMode::Coast);
        motorL1->ConfigVoltageCompSaturation(12.0, m_timeout);
		motorL1->EnableVoltageCompensation(true);

        motorL1->Set(ControlMode::PercentOutput, 0.0);
        motorL1->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorL1->SetSensorPhase(false);
        motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

		motorL1->ConfigOpenloopRamp(m_openLoopRampRate, m_timeout);
		motorL1->ConfigClosedloopRamp (m_closedLoopRampRate, m_timeout);
    }

    if (m_talonValidL2)
	{
        motorL2->Set(ControlMode::Follower,1);
        motorL2->SetInverted(InvertType::FollowMaster);
        motorL2->SetNeutralMode(NeutralMode::Coast);
        motorL2->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorL2->EnableVoltageCompensation(true);
    }

    if (m_talonValidR3)
	{
        motorR3->SetInverted(true);
        motorR3->SetNeutralMode(NeutralMode::Coast);
        motorR3->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorR3->EnableVoltageCompensation(true);

        motorR3->Set(ControlMode::PercentOutput, 0.0);
        motorR3->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorR3->SetSensorPhase(false);
        motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

		motorR3->ConfigOpenloopRamp(m_openLoopRampRate, m_timeout);
		motorR3->ConfigClosedloopRamp (m_closedLoopRampRate, m_timeout);
    }

    if (m_talonValidR4)
	{
        motorR4->Set(ControlMode::Follower, 3);
        motorR4->SetInverted(InvertType::FollowMaster);
        motorR4->SetNeutralMode(NeutralMode::Coast);
        motorR4->ConfigVoltageCompSaturation(12.0, m_timeout);
        motorR4->EnableVoltageCompensation(true);
    }

    // Set to low gear (default)
    m_lowGear = true;
    MoveShiftGears(m_lowGear);

    // Set drive mode to first option
	m_curDriveMode = DRIVEMODE_LAST;
	ToggleDriveMode();

    // If either master drive talons are valid, enable safety timer
    diffDrive->SetSafetyEnabled(m_talonValidL1 || m_talonValidR3);

    // Initialize and calibrate Pigeon IMU
	m_pigeonValid = PigeonIMUInitialize();

	// // Autonomous turn PID controller
    // driveTurnPIDSource = new PIDSourceDriveTurn();
	// driveTurnPIDOutput = new PIDOutputDriveTurn(diffDrive);
    // driveTurnPIDLoop = new frc::PIDController(m_turnKp, 0.0, 0.0, driveTurnPIDSource, driveTurnPIDOutput, 0.010);

	// Vision-based PID Controller
    driveVisionPIDSource = new PIDSourceDriveVision();
    driveVisionPIDOutput = new PIDOutputDriveVision(diffDrive);
// Ignore the warning that it is deprecated
// TODO: WE WILL REMOVE ALL DEPRECATED CODE IN OFF-SEASON
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    driveVisionPIDLoop = new frc::PIDController(m_visionTurnKp, 0.0, 0.0, driveVisionPIDSource, driveVisionPIDOutput);
#pragma GCC diagnostic pop

    // // Settings for Turn PID
   	// driveTurnPIDLoop->SetPID(m_turnKp, 0.0, 0.0);
   	// driveTurnPIDLoop->SetOutputRange(-m_turnMaxOut, m_turnMaxOut);
   	// driveTurnPIDLoop->SetAbsoluteTolerance(m_turnTolDeg);

	// Velocity Control Loop
// TODO: WE WILL REMOVE ALL DEPRECATED CODE IN OFF-SEASON
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	m_leftPIDController = new frc2::PIDController(m_vcpidKp, m_vcpidKi, m_vcpidKd);
#pragma GCC diagnostic pop

// TODO: WE WILL REMOVE ALL DEPRECATED CODE IN OFF-SEASON
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	m_rightPIDController = new frc2::PIDController(m_vcpidKp, m_vcpidKi, m_vcpidKd);
#pragma GCC diagnostic pop
	m_kinematics = new frc::DifferentialDriveKinematics(TRACK_WIDTH_FEET);
	m_odometry = new frc::DifferentialDriveOdometry(GetAngle());
}

void Drivetrain::InitDefaultCommand()
{
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Drivetrain::Periodic()
{
    // Put code here to be run every loop
    static int 	i = 0;
    int			encoderLeft = 0;
	int			encoderRight = 0;
 	double  	heading = 0.0;

    if (m_talonValidL1)
	{
		encoderLeft = motorL1->GetSelectedSensorPosition(m_pidIndex);
	}

	if (m_talonValidR3)
	{
		encoderRight = -motorR3->GetSelectedSensorPosition(m_pidIndex);
	}

	heading = GetIMUHeading();

	frc::SmartDashboard::PutNumber("DT_Encoder_L", encoderLeft);
	frc::SmartDashboard::PutNumber("DT_Encoder_R", encoderRight);
	frc::SmartDashboard::PutNumber("DT_Heading", heading);


    if (m_driveDebug > 1 || (m_driveDebug > 0 && m_isMovingAuto))
	{
		// Slow debug message rate to every 5 * 20ms periods
		if (i++ % 5 == 0)
		{
			double	outputL1 = 0.0, currentL1 = 0.0, currentL2 = 0.0;
			double	outputR3 = 0.0, currentR3 = 0.0, currentR4 = 0.0;

			if (m_talonValidL1)
			{
				outputL1 = motorL1->GetMotorOutputPercent();
				currentL1 = motorL1->GetOutputCurrent();
			}

			if (m_talonValidL2)
			{
				currentL2 = motorL2->GetOutputCurrent();
			}

			if (m_talonValidR3)
			{
				outputR3 = motorR3->GetMotorOutputPercent();
				currentR3 = motorR3->GetOutputCurrent();
			}

			if (m_talonValidR4)
			{
				currentR4 = motorR4->GetOutputCurrent();
			}

			double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;

			std::printf("2135: DT %6.3f deg %4.1f turn %4.1f LR cts %5d %5d out %4.2f %4.2f amps %6.3f %6.3f %6.3f %6.3f\n",
				secs, heading, m_turnAngle, encoderLeft, encoderRight, outputL1, outputR3, currentL1, currentL2, currentR3, currentR4);

			frc::SmartDashboard::PutNumber("DT_Output_L1", outputL1);
			frc::SmartDashboard::PutNumber("DT_Current_L1", currentL1);
			frc::SmartDashboard::PutNumber("DT_Current_L2", currentL2);

			frc::SmartDashboard::PutNumber("DT_Output_R3", outputR3);
			frc::SmartDashboard::PutNumber("DT_Current_R3", currentR3);
			frc::SmartDashboard::PutNumber("DT_Current_R4", currentR4);

			frc::SmartDashboard::PutNumber("DT_OpenLoopRampRate", m_openLoopRampRate);
			frc::SmartDashboard::PutNumber("DT_ClosedLoopRampRate", m_closedLoopRampRate);
		}
	}
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivetrain::Initialize(void)
{
    std::printf("2135: DT Initialize\n");

    //When disabled, low gear and coast mode to allow easier pushing
     m_lowGear = true;
     m_brakeMode = false;
     m_throttleZeroed = false;

    // If ENABLED and AUTON mode, set brake mode
     if(!frc::RobotState::IsDisabled())
	 {
        if(!frc::RobotState::IsOperatorControl())
		{
            m_brakeMode = true;
        }
    }

    MoveShiftGears(m_lowGear);
    MoveSetBrakeMode(m_brakeMode);
    MoveStop();
}

void Drivetrain::FaultDump(void)
{

    // Dump all Talon faults
    frc2135::TalonUtils::TalonFaultDump("DT L1", motorL1);
    frc2135::TalonUtils::TalonFaultDump("DT L2", motorL2);
    frc2135::TalonUtils::TalonFaultDump("DT R3", motorR3);
	frc2135::TalonUtils::TalonFaultDump("DT R4", motorR4);
	PigeonIMUFaultDump();

    // Dump Pigeon faults
    // frc2135::TalonUtils::PigeonIMUFaultDump("DT IMU", gyro);

}

// Joystick movement during Teleop
void Drivetrain::MoveWithJoysticks(std::shared_ptr<frc::Joystick> throttleJstick, std::shared_ptr<frc::Joystick> turnJstick)
{
	double xValue = 0.0;
	double yValue = 0.0;

	// If no separate turn stick, then assume Thrustmaster HOTAS 4
    if (turnJstick == nullptr)
	{
        xValue = throttleJstick->GetX();
	    yValue = throttleJstick->GetZ();
    }
    else
	{	// Separate throttle and turn stick
        xValue = turnJstick->GetX();
	    yValue = throttleJstick->GetY();
    }

    xValue *= m_driveXScaling;
	if (!m_lowGear)
	{
		yValue *= m_driveYScaling;
	}

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

	units::feet_per_second_t ySpeed = 0.0_fps;
	units::radians_per_second_t rot = 0.0_rad_per_s;

    switch (m_curDriveMode)
	{
		default:
		case DRIVEMODE_ARCADE:
			diffDrive->ArcadeDrive(-yValue, xValue, true);
			break;
		case DRIVEMODE_CURVATURE:
			diffDrive->CurvatureDrive(-yValue, xValue, false);	// Boolean is for quick turn or not
			break;
		case DRIVEMODE_VELCONTROL:
			double yValueSquared = yValue * abs(yValue);
			double xValueSquared = xValue * abs(xValue);

			// FIXME: (JLM) These print statements will flood the console!
			if (!m_lowGear)
			{
				m_vcMaxSpeed = 16.77;
				std::printf("2135: Changed Max Speed to High Gear");
			}
			else
			{
				m_vcMaxSpeed = 6.73;
				std::printf("2135: Changed Max Speed to Low Gear");
			}

			ySpeed = yValueSquared * units::feet_per_second_t(m_vcMaxSpeed);
			rot = xValueSquared * units::radians_per_second_t(m_vcMaxAngSpeed);
			VelocityCLDrive(m_kinematics->ToWheelSpeeds({ySpeed, 0_fps, rot}));
			break;
    }
}

void Drivetrain::ToggleDriveMode()
{
	std::printf("2135: Previous Drive: %d\n", m_curDriveMode);
	if (++m_curDriveMode >= DRIVEMODE_LAST)
		m_curDriveMode = DRIVEMODE_FIRST;

	std::printf("2135: Current Drive: %d\n", m_curDriveMode);
	frc::SmartDashboard::PutNumber("DriveMode", m_curDriveMode);
}

// Velocity Control Loop

void Drivetrain::VelocityCLDrive(const frc::DifferentialDriveWheelSpeeds& speeds)
{
	// calculates FF output
	const auto leftFeedforward = m_feedforward.Calculate(speeds.left);
	const auto rightFeedforward = m_feedforward.Calculate(speeds.right);
	double leftCurSpeed = GetSpeed(motorL1);
	double rightCurSpeed = GetSpeed(motorR3);
	double leftTargetSpeed = speeds.left.to<double>();
	double rightTargetSpeed = speeds.right.to<double>();
	// calculates PID output
  	const auto leftOutput = m_leftPIDController->Calculate(leftCurSpeed, leftTargetSpeed);
	const auto rightOutput = m_rightPIDController->Calculate(rightCurSpeed, rightTargetSpeed);

	// Divide FF by 12 to normalize to the same units as the outputs
	double leftTotalOutput = -leftOutput - double(leftFeedforward) / 12.0;
  	double rightTotalOutput = rightOutput + double(rightFeedforward) / 12.0;
	motorL1->Set(leftTotalOutput);
	motorR3->Set(rightTotalOutput);

	if (m_driveDebug > 0)
	{
		frc::SmartDashboard::PutNumber("leftOutput", -leftOutput);
		frc::SmartDashboard::PutNumber("rightOutput", rightOutput);
  		frc::SmartDashboard::PutNumber("leftTotalOutput", leftTotalOutput);
  		frc::SmartDashboard::PutNumber("rightTotalOutput", rightTotalOutput);
  		frc::SmartDashboard::PutNumber("leftCurSpeed", leftCurSpeed);
  		frc::SmartDashboard::PutNumber("rightCurSpeed", rightCurSpeed);
  		frc::SmartDashboard::PutNumber("leftTargetSpeed", leftTargetSpeed);
  		frc::SmartDashboard::PutNumber("rightTargetSpeed", rightTargetSpeed);
  		frc::SmartDashboard::PutNumber("speed difference", rightCurSpeed - leftCurSpeed);
  		frc::SmartDashboard::PutNumber("Output difference", rightOutput - leftOutput);
	}
}

void Drivetrain::UpdateOdometry()
{
  m_odometry->Update(GetAngle(), units::foot_t(GetDistance(motorL1)), units::foot_t(GetDistance(motorR3)));
}

double Drivetrain::GetDistance(std::shared_ptr<WPI_TalonFX> talon)
{
  return DIST_PER_COUNT * talon->GetSelectedSensorPosition();
}

double Drivetrain::GetSpeed(std::shared_ptr<WPI_TalonFX> talon)
{
  return DIST_PER_COUNT * (talon->GetSelectedSensorVelocity() * 10);
}

//	Automatic Drive Spin movement

void Drivetrain::MoveSpin(bool spinRight)
{
	double spinSpeed = m_driveSpin;

	if (!spinRight)
		spinSpeed *= -1.0;

	if (m_talonValidL1 || m_talonValidR3)
		diffDrive->TankDrive(spinSpeed, -spinSpeed, false);
}

void Drivetrain::MoveStop()
{
	if (m_talonValidL1 || m_talonValidR3)
		diffDrive->TankDrive(0.0, 0.0, false);
}

//	Shift transmission gears

void Drivetrain::MoveShiftGears(bool lowGear)
{
    m_lowGear = lowGear;

    std::printf("2135: DT %s Gear\n", (lowGear) ? "LOW" : "HIGH");
    frc::SmartDashboard::PutBoolean("DT Low Gear", lowGear);

    shifter->Set( (lowGear) ? shifter->kForward : shifter->kReverse);
}

//	Set Talon brake mode

void Drivetrain::MoveSetBrakeMode(bool brakeMode)
{
	m_brakeMode = brakeMode;

	std::printf("2135: DT %s Mode\n", (brakeMode) ? "BRAKE" : "COAST");
	frc::SmartDashboard::PutBoolean("DT Brake Mode", brakeMode);

	NeutralMode brakeOutput;
	brakeOutput = (brakeMode) ? NeutralMode::Brake : NeutralMode::Coast;
	if (m_talonValidL1)
		motorL1->SetNeutralMode(brakeOutput);
	if (m_talonValidL2)
		motorL2->SetNeutralMode(brakeOutput);
	if (m_talonValidR3)
		motorR3->SetNeutralMode(brakeOutput);
	if (m_talonValidR4)
		motorR4->SetNeutralMode(brakeOutput);
}

double Drivetrain::InchesToCounts(double inches)
{
	double counts;

	counts = (inches / m_circumInches) * COUNTS_PER_ROTATION;
	return counts;
}

double Drivetrain::CountsToInches(int counts)
{
	double inches;

	inches = ((double) counts / COUNTS_PER_ROTATION) * m_circumInches;
	return inches;
}

double Drivetrain::GetEncoderPosition(int motorID)
{
	int		ret = 0;

	switch (motorID)
	{
		case 1:			// Left Master
			if (m_talonValidL1)
				ret = motorL1->GetSelectedSensorPosition(m_pidIndex);
			break;
		case 3:			// Right Master
			if (m_talonValidR3)
				ret = motorR3->GetSelectedSensorPosition(m_pidIndex);
			break;
		default:
			break;
	}

	return ret;
}

///////////////////////////////////////////////////////////////////////////////

//	Pigeon IMU

bool Drivetrain::PigeonIMUInitialize()
{
	int			i;
	int			retries = 5;
	int			deviceID = 0;
	int			pigeonVersion = 0;
	bool 		pigeonValid = false;
	ErrorCode 	error = OKAY;
	char		subsystem[] = "DT";
	char		name[] = "Pigeon IMU";

	std::printf("2135: TalonFX Subsystem %s Name %s\n", subsystem, name);

    // Display Pigeon IMU firmware versions
	deviceID = pigeonIMU->GetDeviceNumber();
	if ((error = pigeonIMU->GetLastError()) != OKAY)
	{
		std::printf("2135: ERROR: %s %s GetDeviceNumber error - %d\n", subsystem, name, error);
		return error;
	}

	for (i = 0; i < retries; i++) {
		pigeonVersion = pigeonIMU->GetFirmwareVersion();
		if ((error = pigeonIMU->GetLastError()) != OKAY) {
			std::printf("2135: ERROR: %s %s ID %d GetFirmwareVersion error - %d\n", subsystem, name, deviceID, error);
			return error;
		}
		if (pigeonVersion == m_reqPigeonVer) {
			pigeonValid = true;
			break;
		}
		else {
			std::printf("2135: WARNING: %s %s ID %d Incorrect FW version %d.%d expected %d.%d\n",
				subsystem, name, deviceID, pigeonVersion/256, pigeonVersion%256, m_reqPigeonVer/256, m_reqPigeonVer%256);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	if (pigeonValid) {
		// Initialize Pigeon IMU to all factory defaults
		if ((error = pigeonIMU->ConfigFactoryDefault(m_timeout)) != OKAY)
		{
			std::printf("2135: ERROR: %s %s ID %d ConfigFactoryDefault error - %d\n", subsystem, name, deviceID, error);
			pigeonValid = false;
		}

		double	heading = pigeonIMU->GetFusedHeading();
		bool angleIsGood = (pigeonIMU->GetState() == PigeonIMU::Ready) ? true : false;
		std::printf("2135: %s %s ID %d fused heading %5.1f angle is %s\n",
				subsystem, name, deviceID, heading, (angleIsGood) ? "TRUE" : "FALSE");

		pigeonIMU->SetYaw(0.0, m_timeout);
		if ((error = pigeonIMU->GetLastError()) != OKAY)
		{
			std::printf("2135: ERROR: %s %s ID %d SetFusedHeading error - %d\n", subsystem, name, deviceID, error);
			pigeonValid = false;
		}

		pigeonIMU->SetFusedHeading(0.0, m_timeout);
		if ((error = pigeonIMU->GetLastError()) != OKAY)
		{
			std::printf("2135: ERROR: %s %s ID %d SetYaw error - %d\n", subsystem, name, deviceID, error);
			pigeonValid = false;
		}

		std::printf("2135: %s %s ID %d ver %d.%d is RESPONSIVE and INITIALIZED (error %d)\n",
				subsystem, name, deviceID, pigeonVersion/256, pigeonVersion&0xff, error);
   	}
   	else
	{
		std::printf("2135: ERROR: %s %s ID %d ver %d.%d is UNRESPONSIVE, (error %d)\n",
			subsystem, name, deviceID, pigeonVersion/256, pigeonVersion&0xff, error);
   	   	pigeonValid = false;
   	}

	return pigeonValid;
}

void Drivetrain::PigeonIMUFaultDump(void)
{
	PigeonIMU_Faults		faults;
	PigeonIMU_StickyFaults	stickyFaults;

	pigeonIMU->GetFaults(faults);
	if (faults.HasAnyFault())
		std::printf("2135: ERROR: %s %s ID %d has a FAULT - %d\n",
			"DT", "PigeonIMU", 2, faults.ToBitfield());

	pigeonIMU->GetStickyFaults(stickyFaults);
	pigeonIMU->ClearStickyFaults(m_timeout);
}

double Drivetrain::GetIMUHeading()
{
	// Fused Heading is better than Yaw from Pigeon
	double	heading = 0.0;

	if (m_pigeonValid)
	{
		if (pigeonIMU->GetState() != PigeonIMU::Ready)
			std::printf("2135: ERROR: %s %s ID %d is NOT READY\n", "DT", "PigeonIMU", 2);
		heading = pigeonIMU->GetFusedHeading();
	}

    return heading;
}

frc::Rotation2d Drivetrain::GetAngle()
{
	return frc::Rotation2d(units::degree_t(GetIMUHeading()));
}

void Drivetrain::ResetSensors(void)
{
	if (m_talonValidL1)
		motorL1->SetSelectedSensorPosition(0, m_pidIndex, 0);
	if (m_talonValidR3)
		motorR3->SetSelectedSensorPosition(0, m_pidIndex, 0);
	if (m_pigeonValid)
	{
		pigeonIMU->SetYaw(0.0);
		pigeonIMU->SetFusedHeading(0.0, 0);
	}
}

void Drivetrain::MoveDriveStraight(double output)
{
	diffDrive->TankDrive(output, output, false);
}

////////////////////////// MOTION MAGIC ///////////////////////////
void Drivetrain::MoveDriveDistanceMMInit(double inches)
{
    m_distTargetInches = inches;
    m_distTargetCounts = round(m_distTargetInches * CountsPerInch);
    std::printf("2135: DTDD Init %d cts %5.2f in %5.2f CountsPerInch\n",
        (int) m_distTargetCounts, m_distTargetInches, CountsPerInch);

    // Initialize the encoders ot start movement at reference of zero counts
	ResetSensors();

    diffDrive->SetSafetyEnabled(false);
	if (m_talonValidL1)
    	motorL1->Set(ControlMode::MotionMagic, m_distTargetCounts);
	if (m_talonValidR3)
    	motorR3->Set(ControlMode::MotionMagic, -m_distTargetCounts);

	// Start safety timer with 2.0 sec padding (feet * 6.73 fps)
	m_safetyTimeout = (inches / 12) * 5.0 + 2.0;
	m_safetyTimer.Reset();
	m_safetyTimer.Start();

	m_isMovingAuto = true;
}

void Drivetrain::MoveDriveDistanceMMExecute()
{
    // Internal - Talon
}

bool Drivetrain::MoveDriveDistanceMMIsFinished()
{
    bool isFinished = false;
    int curCounts_L = 0;
    int curCounts_R = 0;
    double errorInInches_L = 0.0;
    double errorInInches_R = 0.0;

    if (m_talonValidL1)
        curCounts_L = motorL1->GetSelectedSensorPosition(m_pidIndex);

    if (m_talonValidR3)
        curCounts_R = motorR3->GetSelectedSensorPosition(m_pidIndex);

    errorInInches_L = CountsToInches(m_distTargetCounts - curCounts_L);
    errorInInches_R = CountsToInches(-m_distTargetCounts - curCounts_R);

    m_distTolInches = 2.0;              // tolerance

    // Check to see if the error is in an acceptable number of inches.
    if ((fabs(errorInInches_L) < m_distTolInches) && (fabs(errorInInches_R) < m_distTolInches))
	{
        isFinished = true;
 		std::printf("2135: DTDD Move Finished - Time %f\n", m_safetyTimer.Get());
   }

    // Check to see if the Safety Timer has timed out.
	if (m_safetyTimer.Get() >= m_safetyTimeout)
	{
		isFinished = true;
		std::printf("2135: DTDD Move Safety timer has timed out\n");
	}

    return isFinished;
}

void Drivetrain::MoveDriveDistanceMMEnd()
{
	if (m_talonValidL1)
    	motorL1->Set(ControlMode::PercentOutput, 0.0);
	if (m_talonValidR3)
		motorR3->Set(ControlMode::PercentOutput, 0.0);

	// Stop the safety timer
    std::printf("2135: DTDD End %d cts %5.2f in TimeToTarget: %3.2f\n",
        (int) m_distTargetCounts, m_distTargetInches, m_safetyTimer.Get());

	m_safetyTimer.Stop();
	m_isMovingAuto = false;

    // If either master drive talons are valid, re-enable safety timer
    diffDrive->SetSafetyEnabled(m_talonValidL1 || m_talonValidR3);
}


////////////////////////// Aligning with Target Using Vision Processing ///////////////////////////

void Drivetrain::MoveAlignTurnInit()
{
	m_alignTurnError = (Robot::vision->GetHorzOffset());
	std::printf("2135: DTAT Init - Error %5.2f degrees/n", m_alignTurnError);
}

void Drivetrain::MoveAlignTurnExecute(std::shared_ptr<frc::Joystick> throttleJstick, std::shared_ptr<frc::Joystick> turnJstick)
{
	double throttle = 0.0;
	double alignTurnAdjustment = 0.0;

	// If no separate turn stick, then assume Thrustmaster HOTAS 4 z-axis
	throttle = (turnJstick == nullptr) ? throttleJstick->GetZ(): throttleJstick->GetY();

	m_alignTurnError = (Robot::vision->GetHorzOffset());
	alignTurnAdjustment = m_alignTurnError * m_alignTurnKp;

	double leftThrottle = throttle - alignTurnAdjustment;
	double rightThrottle = throttle + alignTurnAdjustment;

	if (m_alignTurnDebug)
	{
		std::printf("2135: DTAT - Error %5.2f degrees Adjustment %5.2f Left Throttle %5.2f Right Throttle %5.2f/n",
			m_alignTurnError, alignTurnAdjustment, leftThrottle, rightThrottle);
	}

	diffDrive->TankDrive(leftThrottle, rightThrottle);
}

bool Drivetrain::MoveAlignTurnIsFinished()
{
	bool isFinished = false;

	m_alignTurnError = (Robot::vision->GetHorzOffset());

	if (abs(m_alignTurnError) < 1.0)
	{		// TODO: change tolerance to variable set in config
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

///////// Aligning with Target Using Vision Processing with (deprecated) PID Controller ///////////

void Drivetrain::MoveAlignTurnPIDInit(double targetHorz)
{
	// Set current angle
	double currAngle = Robot::vision->GetHorzOffset();
	driveVisionPIDOutput->SetTurnAngle(currAngle);
	driveVisionPIDSource->SetTurnAngle(currAngle);

	// Set target turn angle
	driveVisionPIDLoop->SetSetpoint(targetHorz);

	driveVisionPIDLoop->SetOutputRange(-0.75, 0.75);

	// Enable the PID loop (tolerance is in encoder count units)
	driveVisionPIDLoop->SetAbsoluteTolerance(0.5);	// This is +/-, so 0.5 => 1.0 degree
	driveVisionPIDLoop->Enable();

	//Start safety timer
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
	m_safetyTimeout = 2.5;

	// Disable safety feature during movement, since motors will be fed by loop
	diffDrive->SetSafetyEnabled(false);
}

bool Drivetrain::MoveAlignTurnPIDISFinished()
{
	double isFinished = false;

	// Test the PID to see if it is on the programmed target
	if (driveVisionPIDLoop->OnTarget())
	{
		isFinished = true;

		std::printf("2135: DT Turned to Horizontal Target. Horz: %3.2f\n",
			Robot::vision->GetHorzOffset());
	}

	// Check if safety timer has expired, set value to about 2x the cycle
	if (m_safetyTimer.HasPeriodPassed(m_safetyTimeout))
	{
		std::printf("2135: Safety Timer timed out %3.2f\n", m_safetyTimeout);
		isFinished = true;
	}

	return isFinished;
}

void Drivetrain::MoveAlignTurnPIDStop()
{
	double closedLoopError;

	// Disable PID loop
	driveVisionPIDLoop->Disable();

	// Stop safety timer
	std::printf("2135: TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	// Gets closed loop error and prints it
	closedLoopError = driveVisionPIDLoop->GetError();
	std::printf("2135: ClosedLoopError: %f\n", closedLoopError);

	// Re-enable the motor safety helper (temporarily disabled)
	diffDrive->SetSafetyEnabled(false);
}

void Drivetrain::BumpUpRampRate()
{
	m_openLoopRampRate += 0.1;
	m_closedLoopRampRate += 0.1;
	motorL1 -> ConfigOpenloopRamp(m_openLoopRampRate, m_timeout);
	motorL1 -> ConfigClosedloopRamp(m_closedLoopRampRate, m_timeout);
	motorR3 -> ConfigOpenloopRamp(m_openLoopRampRate, m_timeout);
	motorR3 -> ConfigClosedloopRamp(m_closedLoopRampRate, m_timeout);
}

void Drivetrain::BumpDownRampRate()
{
	m_openLoopRampRate -= 0.1;
	m_closedLoopRampRate -= 0.1;
	motorL1 -> ConfigOpenloopRamp(m_openLoopRampRate, m_timeout);
	motorL1 -> ConfigClosedloopRamp(m_closedLoopRampRate, m_timeout);
	motorR3 -> ConfigOpenloopRamp(m_openLoopRampRate, m_timeout);
	motorR3 -> ConfigClosedloopRamp(m_closedLoopRampRate, m_timeout);
}
