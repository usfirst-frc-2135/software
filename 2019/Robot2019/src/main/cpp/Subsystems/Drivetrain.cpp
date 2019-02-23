// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Subsystems/Drivetrain.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/DriveTeleop.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

#include "Commands/DriveTeleop.h"


Drivetrain::Drivetrain() : frc::Subsystem("Drivetrain") {

    std::printf("2135: DT Drivetrain Constructor\n");

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL1.reset(new WPI_TalonSRX(1));
    
    
    motorR3.reset(new WPI_TalonSRX(3));
    
    
    diffDrive.reset(new frc::DifferentialDrive(*motorL1, *motorR3));
    AddChild("Diff Drive", diffDrive);
    diffDrive->SetSafetyEnabled(true);
        diffDrive->SetExpiration(0.25);
        diffDrive->SetMaxOutput(1.0);

    motorL2.reset(new WPI_TalonSRX(2));
    
    
    motorR4.reset(new WPI_TalonSRX(4));
    
    
    shifter.reset(new frc::DoubleSolenoid(0, 0, 1));
    AddChild("Shifter", shifter);
    

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	pigeonIMU.reset(new PigeonIMU(motorL2.get()));

    // Validate Talon SRX controllers, initialize and display firmware versions
    m_talonValidL1 = frc2135::TalonSRXUtils::TalonSRXCheck(motorL1, "DT", "L1");
    m_talonValidL2 = frc2135::TalonSRXUtils::TalonSRXCheck(motorL2, "DT", "L2");
    m_talonValidR3 = frc2135::TalonSRXUtils::TalonSRXCheck(motorR3, "DT", "R3");
    m_talonValidR4 = frc2135::TalonSRXUtils::TalonSRXCheck(motorR4, "DT", "R4");

    // Retrieve drivetrain modified parameters from RobotConfig
     frc2135::RobotConfig* config = frc2135::RobotConfig::GetInstance();
     config->GetValueAsDouble("DT_DriveXScaling", m_driveXScaling, 1.0);
 	 config->GetValueAsDouble("DT_DriveYScaling", m_driveYScaling, 1.0);
	 config->GetValueAsDouble("DT_DriveSpin", m_driveSpin, 0.45);
	 config->GetValueAsDouble("DT_PidTurnKp", m_turnKp, 0.030);

    // Invert the direction of the motors
    // Set to brake mode (in comparison to coast)
    // Set Voltage Compensation to 12V
    // Set encoder as a CTRE magnetic in relative mode with sensor in phase with output
    if (m_talonValidL1) {
        motorL1->SetInverted(true);
        motorL1->SetNeutralMode(NeutralMode::Brake);
        motorL1->ConfigVoltageCompSaturation(12.0, 0);
        motorL1->EnableVoltageCompensation(true);

        motorL1->Set(ControlMode::PercentOutput, 0.0);
        motorL1->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorL1->SetSensorPhase(false);
        motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    }

    if (m_talonValidL2) {
    	motorL2->SetInverted(true);
        motorL2->SetNeutralMode(NeutralMode::Brake);
        motorL2->Set(ControlMode::Follower, 1);
    }

    if (m_talonValidR3) {
        motorR3->SetInverted(true);
        motorR3->SetNeutralMode(NeutralMode::Brake);
        motorL1->ConfigVoltageCompSaturation(12.0, 0);
        motorL1->EnableVoltageCompensation(true);

        motorR3->Set(ControlMode::PercentOutput, 0.0);
        motorR3->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, m_pidIndex, m_timeout);
        motorR3->SetSensorPhase(false);
        motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    }

    if (m_talonValidR4) {
        motorR4->SetInverted(true);
        motorR4->SetNeutralMode(NeutralMode::Brake);
        motorR4->Set(ControlMode::Follower, 3);
    }

    // Set to low gear (default)
    m_lowGear = true;
    MoveShiftGears(m_lowGear);

    // If both drive talons not valid, disable safety timer
    if (m_talonValidL1 || m_talonValidR3) {
        diffDrive->SetSafetyEnabled(true);
    }
    else {
        diffDrive->SetSafetyEnabled(false);
    }

	// Initialize and calibrate Pigeon IMU
	m_pigeonValid = InitializePigeonIMU();

	// Autonomous turn PID controller
	driveTurnPIDSource = new PIDSourceDriveTurn();
	driveTurnPIDOutput = new PIDOutputDriveTurn(diffDrive);
    driveTurnPIDLoop = new frc::PIDController(m_turnKp, 0.0, 0.0, driveTurnPIDSource, driveTurnPIDOutput, 0.010);
	
	// Adjust Kp for encoder being used
    driveVisionPIDSource = new PIDSourceDriveVision();
    driveVisionPIDOutput = new PIDOutputDriveVision(diffDrive);
    driveVisionPIDLoop = new frc::PIDController((m_visionTurnKp/COUNTS_PER_ROTATION) * 1.5, 0.0, 0.0, driveVisionPIDSource, driveVisionPIDOutput);

   	// Settings for Turn PID
   	driveTurnPIDLoop->SetPID(m_turnKp, 0.0, 0.0);
   	driveTurnPIDLoop->SetOutputRange(-m_turnMaxOut, m_turnMaxOut);
   	driveTurnPIDLoop->SetAbsoluteTolerance(m_turnTolDeg);
}

void Drivetrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new DriveTeleop());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Drivetrain::Periodic() {
    // Put code here to be run every loop
    double	encoderLeft = 0.0;
	double	encoderRight = 0.0;
    double	outputL1 = 0.0, currentL1 = 0.0;
	double	outputL2 = 0.0, currentL2 = 0.0;
	double	outputR3 = 0.0, currentR3 = 0.0;
	double	outputR4 = 0.0, currentR4 = 0.0;
	double  gyroYaw = 0.0;

    if (m_talonValidL1) {
		encoderLeft = motorL1->GetSelectedSensorPosition(m_pidIndex);
		outputL1 = motorL1->GetMotorOutputPercent();
		currentL1 = motorL1->GetOutputCurrent();
	}

	if (m_talonValidL2) {
		outputL2 = motorL2->GetMotorOutputPercent();
		currentL2 = motorL2->GetOutputCurrent();
	}

	if (m_talonValidR3) {
		encoderRight = motorR3->GetSelectedSensorPosition(m_pidIndex);
		outputR3 = motorR3->GetMotorOutputPercent();
		currentR3 = motorR3->GetOutputCurrent();
	}

	if (m_talonValidR4) {
		outputR4 = motorR4->GetMotorOutputPercent();
		currentR4 = motorR4->GetOutputCurrent();
	}

	if (m_pigeonValid) {
		double	ypr[3];
		pigeonIMU->GetYawPitchRoll(ypr);
		gyroYaw = ypr[0];
	}

    if (m_driveDebug) {
		frc::SmartDashboard::PutNumber("DT_Encoder_L", encoderLeft);
		frc::SmartDashboard::PutNumber("DT_Output_L1", outputL1);
		frc::SmartDashboard::PutNumber("DT_Current_L1", currentL1);
		frc::SmartDashboard::PutNumber("DT_Output_L2", outputL2);
		frc::SmartDashboard::PutNumber("DT_Current_L2", currentL2);

		frc::SmartDashboard::PutNumber("DT_Encoder_R", encoderRight);
		frc::SmartDashboard::PutNumber("DT_Output_R3", outputR3);
		frc::SmartDashboard::PutNumber("DT_Current_R3", currentR3);
		frc::SmartDashboard::PutNumber("DT_Output_R4", outputR4);
		frc::SmartDashboard::PutNumber("DT_Current_R4", currentR4);
		frc::SmartDashboard::PutNumber("DT_GyroAngle", gyroYaw);
	}
}

    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CMDPIDGETTERS

////////////////////////////////////////////////////////////////////////////////////////

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivetrain::Initialize(void) {
	std::printf("2135: DT Initialize\n");

	// When disabled, low gear and coast mode to allow easier pushing
	m_lowGear = true;
	m_brakeMode = false;
	if (frc::RobotState::IsDisabled()) {
	}
	else {
		// Enabled and teleop - low gear and coast mode
		if (frc::RobotState::IsOperatorControl()) {
		}
		else {	// Auton always low gear and brake mode
			m_brakeMode = true;
		}
	}

	MoveShiftGears(m_lowGear);
    MoveSetBrakeMode(m_brakeMode);
}

void Drivetrain::FaultDump(void) {
	
	//	Dump all Talon faults
	frc2135::TalonSRXUtils::TalonSRXFaultDump("DT L1", motorL1);
	frc2135::TalonSRXUtils::TalonSRXFaultDump("DT L2", motorL2);
	frc2135::TalonSRXUtils::TalonSRXFaultDump("DT R3", motorR3);
	frc2135::TalonSRXUtils::TalonSRXFaultDump("DT R4", motorR4);

	// Dump Pigeon faults
	//frc2135::TalonSRXUtils::PigeonIMUFaultDump("DT IMU", gyro);
}

bool Drivetrain::InitializePigeonIMU() {
	int			i;
	int			retries = 5;
	int			deviceID = 0;
	int			pigeonVersion = 0;
	bool 		pigeonValid = false;
	ErrorCode 	error = OKAY;
	char		subsystem[] = "DT";
	char		name[] = "Pigeon IMU";

	std::printf("2135: TalonSRX Subsystem %s Name %s\n", subsystem, name);

    // Display Pigeon IMU firmware versions
	deviceID = pigeonIMU->GetDeviceNumber();
	if ((error = pigeonIMU->GetLastError()) != OKAY) {
		std::printf("2135: ERROR: %s %s GetDeviceNumber error - %d\n", 
			subsystem, name, error);
		return error;
	}

	for (i = 0; i < retries; i++) {
		pigeonVersion = pigeonIMU->GetFirmwareVersion();
		if ((error = pigeonIMU->GetLastError()) != OKAY) {
			std::printf("2135: ERROR: %s %s ID %d GetFirmwareVersion error - %d\n", 
				subsystem, name, deviceID, error);
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
		if ((error = pigeonIMU->ConfigFactoryDefault(m_timeout)) != OKAY) {
			std::printf("2135: ERROR: %s %s ID %d ConfigFactoryDefault error - %d\n", 
				subsystem, name, deviceID, error);
			pigeonValid = false;
		}

		pigeonIMU->SetYaw(0.0, m_timeout);
		if ((error = pigeonIMU->GetLastError()) != OKAY) {
			std::printf("2135: ERROR: %s %s ID %d SetFusedHeading error - %d\n", 
				subsystem, name, deviceID, error);
			pigeonValid = false;
		}

		pigeonIMU->SetFusedHeading(0.0, m_timeout);
		if ((error = pigeonIMU->GetLastError()) != OKAY) {
			std::printf("2135: ERROR: %s %s ID %d SetYaw error - %d\n", 
				subsystem, name, deviceID, error);
			pigeonValid = false;
		}

		std::printf("2135: %s %s ID %d ver %d.%d is RESPONSIVE and INITIALIZED (error %d)\n",
				subsystem, name, deviceID, pigeonVersion/256, pigeonVersion&0xff, error);
   	}
   	else {
		std::printf("2135: ERROR: %s %s ID %d ver %d.%d is UNRESPONSIVE, (error %d)\n",
			subsystem, name, deviceID, pigeonVersion/256, pigeonVersion&0xff, error);
   	   	pigeonValid = false;
   	}

	return pigeonValid;
}


//	Joystick movement during Teleop

void Drivetrain::MoveWithJoystick(std::shared_ptr<frc::Joystick> throttleJstick, std::shared_ptr<frc::Joystick> turnJstick) {
	double xValue = 0.0;
	double yValue = 0.0;

    if (turnJstick == nullptr) {
        xValue = throttleJstick->GetX();
	    yValue = throttleJstick->GetZ();
    }
    else {
        xValue = turnJstick->GetX();
	    yValue = throttleJstick->GetY();
    }

    xValue *= m_driveXScaling;
	if (!m_lowGear) {
		yValue *= m_driveYScaling;
	}

	if (m_talonValidL1 || m_talonValidR3)
		diffDrive->ArcadeDrive(-yValue, xValue, true);
}

//	Automatic Drive Spin movement

void Drivetrain::MoveSpin(bool spinRight) {
	double spinSpeed = m_driveSpin;

	if (!spinRight)
		spinSpeed *= -1.0;

	if (m_talonValidL1 && m_talonValidR3)
		diffDrive->TankDrive(spinSpeed, -spinSpeed, false);
}

void Drivetrain::MoveStop() {
	if (m_talonValidL1 && m_talonValidR3)
		diffDrive->TankDrive(0.0, 0.0, false);
}

//	Shift transmission gears

void Drivetrain::MoveShiftGears(bool lowGear) {
    m_lowGear = lowGear;

    std::printf("2135: DT %s Gear\n", (lowGear) ? "LOW" : "HIGH");
    frc::SmartDashboard::PutBoolean("DT Low Gear", lowGear);

    shifter->Set( (lowGear) ? shifter->kForward : shifter->kReverse);
}

//	Set Talon brake mode

void Drivetrain::MoveSetBrakeMode(bool brakeMode) {
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

double Drivetrain::InchesToCounts(double inches) {
	double counts;

	counts = (inches / m_circumInches) * COUNTS_PER_ROTATION;
	return counts;
}

double Drivetrain::CountsToInches(int counts) {
	double inches;

	inches = ((double) counts / COUNTS_PER_ROTATION) * m_circumInches;
	return inches;
}

double Drivetrain::GetAngle() {
    return (double)pigeonIMU->GetYawPitchRoll(0);
}

double Drivetrain::GetEncoderPosition(int motorID) {
    if (motorID == 1)
        return motorL1->GetSelectedSensorPosition(0);
    if (motorID == 3)
        return motorR3->GetSelectedSensorPosition(0);
}

///////////////////////// MOTION MAGIC ///////////////////////////////////

void Drivetrain::MoveDriveDistanceMMInit(double inches) {
    m_distTargetInches = inches;
    m_distTargetCounts = round(m_distTargetInches * CountsPerInch);
    std::printf("2135: DTDD Init %d counts, %5.2f inches, %5.2f CountsPerInch\n", 
        (int) m_distTargetCounts, m_distTargetInches, CountsPerInch);

    // Initialize the encoders ot start movement at reference of zero counts
    if (m_talonValidL1) {
        motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    }

    if (m_talonValidR3) {
        motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
    }

    if (m_talonValidL1) {
        motorL1->SelectProfileSlot(0, 0);
       // motorL1->Config_kF(0, 0.0, 0);
        motorL1->Config_kF(0, 0.5832, 0);         // 0.5832 for 6.73 fps?
        motorL1->Config_kP(0, 0.0, 0);
        motorL1->Config_kI(0, 0.0, 0);
        motorL1->Config_kD(0, 0.0, 0);
        motorL1->ConfigMotionCruiseVelocity(950);   // 877 for 6.73 fps?
        motorL1->ConfigMotionAcceleration(1100);
    }

    if (m_talonValidR3) {
        motorR3->SelectProfileSlot(0, 0);
        //motorR3->Config_kF(0, 0.0, 0);
        motorR3->Config_kF(0, 0.5832, 0);
        motorR3->Config_kP(0, 0.0, 0);
        motorR3->Config_kI(0, 0.0, 0);
        motorR3->Config_kD(0, 0.0, 0);
        motorR3->ConfigMotionCruiseVelocity(877);
        motorR3->ConfigMotionAcceleration(1000); 
    }

     diffDrive->SetSafetyEnabled(false);
     motorL1->Set(ControlMode::MotionMagic, m_distTargetCounts); 
     motorR3->Set(ControlMode::MotionMagic, -m_distTargetCounts);
}

void Drivetrain::MoveDriveDistanceMMExecute() {
    // Internal - Talon
}

bool Drivetrain::MoveDriveDistanceMMIsFinished() {
    bool mmIsFinished = false;
    int curCounts_L = 0;
    int curCounts_R = 0;
    double motorOutput_L = 0.0, motorOutput_R = 0.0;
    double motorAmps_L1 = 0.0, motorAmps_L2 = 0.0, motorAmps_R3 = 0.0, motorAmps_R4 = 0.0;
    double errorInInches_L = 0.0;
    double errorInInches_R = 0.0;

    if (m_talonValidL1) {
        curCounts_L = motorL1->GetSelectedSensorPosition(m_pidIndex);
        motorOutput_L = motorL1->GetMotorOutputPercent();
        motorAmps_L1 = motorL1->GetOutputCurrent();
    }

    if (m_talonValidL2) {
        motorAmps_L2 = motorL2->GetOutputCurrent();
    }

    if (m_talonValidR3) {
        curCounts_R = motorR3->GetSelectedSensorPosition(m_pidIndex);
        motorOutput_R = motorR3->GetMotorOutputPercent();
        motorAmps_R3 = motorR3->GetOutputCurrent();
    }

    if (m_talonValidR4) {
        motorAmps_R4 = motorL2->GetOutputCurrent();
    }

    errorInInches_L = CountsToInches(m_distTargetCounts - curCounts_L);
    errorInInches_R = CountsToInches(-m_distTargetCounts - curCounts_R);

    double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;
	std::printf("2135: DTDD %6.3f LR encCts %5d %5d Out %5.3f %5.3f Amps %6.3f %6.3f %6.3f %6.3f\n",
		secs, curCounts_L, -curCounts_R, motorOutput_L, -motorOutput_R, motorAmps_L1, motorAmps_L2, motorAmps_R3, motorAmps_R4);

    m_distTolInches = 2.0;              // tolerance

    // Check to see if the error is in an acceptable number of inches.
    if (/*(fabs(errorInInches_L) < m_distTolInches) &&*/ (fabs(errorInInches_R) < m_distTolInches)) {
        mmIsFinished = true;
    }

    // Check to see if the Safety Timer has timed out.
	if (m_safetyTimer.Get() >= m_safetyTimeout) {
		mmIsFinished = true;
		m_safetyTimer.Stop();
		std::printf("2135: EL Move Safety timer has timed out\n");
	}

    return mmIsFinished;
}

void Drivetrain::MoveDriveDistanceMMEnd() {
    motorL1->Set(ControlMode::PercentOutput, 0.0);
    motorR3->Set(ControlMode::PercentOutput, 0.0);

    diffDrive->SetSafetyEnabled(true);
}

///////////////////////////////////////////////////////////////////////////////

// Autonomous turn PID initialization and setup

void Drivetrain::MoveDriveTurnPIDInit(double angle) {
	m_turnAngle = angle;
	std::printf("2135: DTDT Init %f degrees\n", m_turnAngle);

	// Initialize the encoders to start movement at reference of zero counts
	if (m_talonValidL1)
		motorL1->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);
	if (m_talonValidR3)
		motorR3->SetSelectedSensorPosition(0, m_pidIndex, m_timeout);

	pigeonIMU->SetYaw(0.0, 0);
	driveTurnPIDLoop->SetSetpoint(angle);
	driveTurnPIDLoop->Enable();

	// Disable motor safety helper during PID
   	diffDrive->SetSafetyEnabled(false);

	// Start safety timer with 1.0 sec padding (45 deg -> 0.75 sec, 90 deg -> 1.30 sec)
	m_safetyTimeout = (fabs(m_turnAngle) * 0.020) + 1.0;
	m_safetyTimer.Reset();
	m_safetyTimer.Start();
}

// Autonomous turn PID periodic execution

void Drivetrain::MoveDriveTurnPIDExecute(void) {
	// No work needed since done by PID controller
}

// Autonomous turn PID setpoint monitoring

bool Drivetrain::MoveDriveTurnPIDIsFinished(void) {
	bool pidFinished = false;
	int curCounts_L = 0;
	int curCounts_R = 0;
	double motorOutput_L = 0.0;
	double motorOutput_R = 0.0;
	double curAngle = 0.0;
	double errorInDegrees = 0.0;

	if (m_talonValidL1) {
		curCounts_L = motorL1->GetSelectedSensorPosition(m_pidIndex);
		motorOutput_L = motorL1->GetMotorOutputPercent();
	}
	if (m_talonValidR3) {
		curCounts_R = motorR3->GetSelectedSensorPosition(m_pidIndex);
		motorOutput_R = motorR3->GetMotorOutputPercent();
	}
	curAngle = (double)pigeonIMU->GetYawPitchRoll(0);

	errorInDegrees = m_turnAngle - curAngle;

	double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;
	std::printf("2135: DTDT %5.3f deg %4.2f -> %4.2f (err %4.2f) cts %5d %5d Out %4.2f %4.2f\n",
			secs, curAngle, m_turnAngle, errorInDegrees,
			curCounts_L, curCounts_R, motorOutput_L, motorOutput_R);

	if (driveTurnPIDLoop->OnTarget())
		pidFinished = true;

	// Check to see if the Safety Timer has timed out.
	if (m_safetyTimer.Get() >= m_safetyTimeout) {
		std::printf("2135: DTDT Safety timer has timed out\n");
		pidFinished = true;
	}

	// If on target or safety time has expired
	return pidFinished;
}

// Autonomous turn PID to clean up after reaching the target position

void Drivetrain::MoveDriveTurnPIDEnd(void) {
	int curCounts_L = 0;
	int curCounts_R = 0;
	double motorOutput_L = 0.0;
	double motorOutput_R = 0.0;
	double curAngle = 0.0;
	double errorInDegrees = 0.0;

	// Stop the safety timer
	std::printf("2135: DTDT TimeToTarget:  %3.2f\n", m_safetyTimer.Get());
	m_safetyTimer.Stop();

	driveTurnPIDLoop->Disable();
	curAngle = (double)pigeonIMU->GetYawPitchRoll(0);

	// Re-enable the motor safety helper
    if (m_talonValidL1 && m_talonValidR3)
    	diffDrive->SetSafetyEnabled(true);

	// Snapshot of results to SmartDashboard
//	frc::SmartDashboard::PutNumber("DT DEG", curAngle);
//	frc::SmartDashboard::PutNumber("DT TIME", m_safetyTimer.Get());

	errorInDegrees = m_turnAngle - curAngle;

	// Print final results to console
	double secs = (double)frc::RobotController::GetFPGATime() / 1000000.0;
	std::printf("2135: DTDT %5.3f deg %4.2f -> %4.2f (err %4.2f) cts %5d %5d Out %4.2f %4.2f\n",
			secs, curAngle, m_turnAngle, errorInDegrees,
			curCounts_L, curCounts_R, motorOutput_L, motorOutput_R);
}
