// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
Encoder* RobotMap::chassisEncoderL = NULL;
CANTalon* RobotMap::chassisMotorL2 = NULL;
PIDController* RobotMap::chassisLeftPID = NULL;
CANTalon* RobotMap::chassisMotorL3 = NULL;
Encoder* RobotMap::chassisEncoderR = NULL;
CANTalon* RobotMap::chassisMotorR4 = NULL;
PIDController* RobotMap::chassisRightPID = NULL;
CANTalon* RobotMap::chassisMotorR5 = NULL;
Ultrasonic* RobotMap::chassisUltrasonicDrive = NULL;
Encoder* RobotMap::hWheelEncoderH = NULL;
DoubleSolenoid* RobotMap::hWheelEngage = NULL;
CANTalon* RobotMap::hWheelMotorHL6 = NULL;
CANTalon* RobotMap::hWheelMotorHR7 = NULL;
DoubleSolenoid* RobotMap::intakeClamp = NULL;
DigitalInput* RobotMap::intakeToteFullIn = NULL;
SpeedController* RobotMap::intakeAcquireL = NULL;
SpeedController* RobotMap::intakeAcquireR = NULL;
DoubleSolenoid* RobotMap::stackerClamp = NULL;
DigitalInput* RobotMap::stackerToteFullIn = NULL;
DigitalInput* RobotMap::stackerToteFullOut = NULL;
SpeedController* RobotMap::stackerAcquireL = NULL;
SpeedController* RobotMap::stackerAcquireR = NULL;
AnalogPotentiometer* RobotMap::elevatorHeightPot = NULL;
CANTalon* RobotMap::elevatorMove = NULL;
Compressor* RobotMap::pneumaticsCompressor = NULL;
AnalogInput* RobotMap::pneumaticsAnalogInput1 = NULL;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();

	chassisEncoderL = new Encoder(0, 1, false, Encoder::k4X);
	lw->AddSensor("Chassis", "Encoder L", chassisEncoderL);
	chassisEncoderL->SetDistancePerPulse(1.0);
        chassisEncoderL->SetPIDSourceParameter(Encoder::kDistance);
	chassisMotorL2 = new CANTalon(2);
	
	
	chassisLeftPID = new PIDController(1.0, 0.0, 0.0,/* F: 0.0, */ chassisEncoderL, chassisMotorL2, 0.02);
	lw->AddActuator("Chassis", "Left PID", chassisLeftPID);
	chassisLeftPID->SetContinuous(false); chassisLeftPID->SetAbsoluteTolerance(0.2); 
        chassisLeftPID->SetOutputRange(-1.0, 1.0);
	chassisMotorL3 = new CANTalon(3);
	
	
	chassisEncoderR = new Encoder(2, 3, true, Encoder::k4X);
	lw->AddSensor("Chassis", "Encoder R", chassisEncoderR);
	chassisEncoderR->SetDistancePerPulse(1.0);
        chassisEncoderR->SetPIDSourceParameter(Encoder::kDistance);
	chassisMotorR4 = new CANTalon(4);
	
	
	chassisRightPID = new PIDController(1.0, 0.0, 0.0,/* F: 0.0, */ chassisEncoderR, chassisMotorR4, 0.02);
	lw->AddActuator("Chassis", "Right PID", chassisRightPID);
	chassisRightPID->SetContinuous(false); chassisRightPID->SetAbsoluteTolerance(0.2); 
        chassisRightPID->SetOutputRange(-1.0, 1.0);
	chassisMotorR5 = new CANTalon(5);
	
	
	chassisUltrasonicDrive = new Ultrasonic(9, 10);
	lw->AddSensor("Chassis", "Ultrasonic Drive", chassisUltrasonicDrive);
	
	hWheelEncoderH = new Encoder(4, 5, false, Encoder::k4X);
	lw->AddSensor("H Wheel", "Encoder H", hWheelEncoderH);
	hWheelEncoderH->SetDistancePerPulse(1.0);
        hWheelEncoderH->SetPIDSourceParameter(Encoder::kRate);
	hWheelEngage = new DoubleSolenoid(0, 0, 1);      
	lw->AddActuator("H Wheel", "Engage", hWheelEngage);
	
	hWheelMotorHL6 = new CANTalon(6);
	
	
	hWheelMotorHR7 = new CANTalon(7);
	
	
	intakeClamp = new DoubleSolenoid(0, 2, 3);      
	lw->AddActuator("Intake", "Clamp", intakeClamp);
	
	intakeToteFullIn = new DigitalInput(6);
	lw->AddSensor("Intake", "Tote Full In", intakeToteFullIn);
	
	intakeAcquireL = new Talon(0);
	lw->AddActuator("Intake", "Acquire L", (Talon*) intakeAcquireL);
	
	intakeAcquireR = new Talon(1);
	lw->AddActuator("Intake", "Acquire R", (Talon*) intakeAcquireR);
	
	stackerClamp = new DoubleSolenoid(0, 4, 5);      
	lw->AddActuator("Stacker", "Clamp", stackerClamp);
	
	stackerToteFullIn = new DigitalInput(7);
	lw->AddSensor("Stacker", "Tote Full In", stackerToteFullIn);
	
	stackerToteFullOut = new DigitalInput(8);
	lw->AddSensor("Stacker", "Tote Full Out", stackerToteFullOut);
	
	stackerAcquireL = new Talon(2);
	lw->AddActuator("Stacker", "Acquire L", (Talon*) stackerAcquireL);
	
	stackerAcquireR = new Talon(3);
	lw->AddActuator("Stacker", "Acquire R", (Talon*) stackerAcquireR);
	
	elevatorHeightPot = new AnalogPotentiometer(0, 1.0, 0.0);
	lw->AddSensor("Elevator", "Height Pot", elevatorHeightPot);
	
	elevatorMove = new CANTalon(9);
	
	
	pneumaticsCompressor = new Compressor(0);
	
	
	pneumaticsAnalogInput1 = new AnalogInput(1);
	lw->AddSensor("Pneumatics", "Analog Input 1", pneumaticsAnalogInput1);
	


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
