///////////////////////////////////////////////////////////////////////////////
//
//	CommandBasedRobot.cpp
//
//	This is the main robot control structure which defines the driver station
//	interfaces and methods.
//
#include "WPILib.h"
#include "Subsystems/Chassis.h"
#include "Commands/DriveStraight.h"
#include "CommandBase.h"

//	Main Robot Class - subclass of IterativeRobot

class CommandBasedRobot : public IterativeRobot {
	
private:
	Command		*autonomousCommand;				// Our autonomous command
	LiveWindow	*lw;							// Our live window object

	//	Robot initialization - runs at power on
	
	virtual void RobotInit() {
		printf( "2135: RobotInit\n" );
		CommandBase::init();
		lw = LiveWindow::GetInstance();
		autonomousCommand = new DriveStraight(1);
	}
	
	//	Autonomous initialization - runs once at start of Autonomous
	
	virtual void AutonomousInit() {
		printf( "2135: AutonomousInit\n" );
		autonomousCommand->Start();
	}
	
	//	Autonomous periodic - runs each time a driver station packet is received
	
	virtual void AutonomousPeriodic() {
//		printf( "2135: AutonomousPeriodic\n" );
		Scheduler::GetInstance()->Run();
	}
	
	//	Teleop initialization - runs once at start of Teleop
	
	virtual void TeleopInit() {
		printf( "2135: TeleopInit\n" );
		autonomousCommand->Cancel();		// Explicitly stop Autonomous command
	}
	
	//	Teleop periodic - runs each time a driver station packet is received
	
	virtual void TeleopPeriodic() {
//		printf( "2135: TeleopPeriodic\n" );
		Scheduler::GetInstance()->Run();
	}
	
	//	Test periodic - runs test routines in Live Window mode
	
	virtual void TestPeriodic() {
//		printf( "2135: TestPeriodic\n" );
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

