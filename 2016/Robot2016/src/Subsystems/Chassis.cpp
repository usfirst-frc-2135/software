// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Chassis.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Chassis::Chassis() : Subsystem("Chassis") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    motorL2 = RobotMap::chassisMotorL2;
    leftEncoder = RobotMap::chassisLeftEncoder;
    leftPID = RobotMap::chassisLeftPID;
    motorR4 = RobotMap::chassisMotorR4;
    rightEncoder = RobotMap::chassisRightEncoder;
    rightPID = RobotMap::chassisRightPID;
    motorL3 = RobotMap::chassisMotorL3;
    motorR5 = RobotMap::chassisMotorR5;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

    printf("2135: Creating New Robot Drive\n");
    robotDrive = new RobotDrive(motorL2, motorR4);
    printf("2135: Finish Creating New Robot Drive\n");

    robotDrive->SetSafetyEnabled(false);

    motorL3->SetControlMode(CANSpeedController::kFollower);
    motorL3->Set(2);
    motorR5->SetControlMode(CANSpeedController::kFollower);
    motorR5->Set(4);

    m_drivePidSpeedMin = -0.5;
    m_drivePidSpeedMax = 0.5;
    m_driveDistance = 0.0;
}

void Chassis::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Chassis::DriveUsingLeftRightMotorOutputs(double left, double right)
{
	robotDrive->SetLeftRightMotorOutputs(left, right);
}

void Chassis::DriveStop(void)
{
	robotDrive->SetLeftRightMotorOutputs (0.0,0.0);
}

void Chassis::DriveDistanceWithPIDInit( double distance ) {
	double leftDistance;
	double rightDistance;
	double abstolerance = 0.2;

	leftPID->SetPID(0, 0, 0);
	leftPID->SetOutputRange(m_drivePidSpeedMin, m_drivePidSpeedMax);
	leftPID->SetAbsoluteTolerance(abstolerance);
	leftEncoder->SetDistancePerPulse(4 * M_PI / 360);

	rightPID->SetPID(0, 0, 0);
	rightPID->SetOutputRange(m_drivePidSpeedMin, m_drivePidSpeedMax);
	rightPID->SetAbsoluteTolerance(abstolerance);
	rightEncoder->SetDistancePerPulse(4 * M_PI / 360);

	// get current encoder values
	leftDistance = leftEncoder->GetDistance();
	rightDistance = rightEncoder->GetDistance();
	printf("2135: Encoder Distance %f %f\n", leftDistance, rightDistance);

	//add distance to current encoder values
	leftDistance += distance;
	rightDistance += distance;
	printf("2135: Encoder Distance %f %f\n", leftDistance, rightDistance);

	//set SetPoint with calculated target distance
	leftPID->SetSetpoint(leftDistance);
	rightPID->SetSetpoint(rightDistance);
	robotDrive->SetSafetyEnabled(false);

	//enable PID loops
	leftPID->Enable();
	printf("2135: Left PID is enabled\n");
	rightPID->Enable();
	printf("2135: Right PID is enabled\n");

}


void Chassis::DriveDistanceWithPIDExecute()
{
	if (leftPID->OnTarget()) {
		leftPID->Disable();
		printf("2135: Left PID is Disabled\n");
	}
	if (rightPID->OnTarget()) {
		rightPID->Disable();
		printf("2135: Right PID is Disabled\n");
	}
	if (!leftPID->IsEnabled()) {
		motorL2->Set(0, 0);
	}
	if (!rightPID->IsEnabled()) {
		motorR4->Set(0, 0);
	}

	static int counter = 0;
	if (counter++ % 50 == 0) {
	printf("2135: LeftPID %d %d\n", RobotMap::chassisLeftEncoder->Get(), leftPID->IsEnabled());
	printf("2135: RightPID %d %d\n", RobotMap::chassisRightEncoder->Get(), rightPID->IsEnabled());
	}
}

bool Chassis::DriveDistanceWithPIDIsAtSetpoint(void) {
	bool bothOnTarget;
	// are both PIDs on target
	bothOnTarget = false;
	if (!leftPID->IsEnabled() && !rightPID->IsEnabled()) {
		DriveDistanceWithPIDStop();
		bothOnTarget = true;
	}

	return bothOnTarget;
}

void Chassis::DriveDistanceWithPIDStop( void ){
	leftPID->Disable();
	rightPID->Disable();
	robotDrive->SetSafetyEnabled(false);
}
