#include "WPILib.h"
#include "Commands/Command.h"
#include "CommandBase.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/Shoot.h"

class CommandBasedRobot : public IterativeRobot {

private:
	Command *autonomousCommand;
	Command *teleopCommand;

	virtual void RobotInit() {
		CommandBase::init();
		printf( "2135: RobotInit\n" );
		autonomousCommand = new Shoot();
		teleopCommand = new DriveWithJoystick();
//		SmartDashboard::PutData( "SchedulerData", (Sendable*) Scheduler::GetInstance() );
	}
	
	virtual void AutonomousInit() {
		printf( "2135: AutonomousInit\n" );
		autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
//		printf( "2135: AutonomousPeriodic\n" );
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit() {
		printf( "2135: TeleopInit\n" );
		autonomousCommand->Cancel();
		teleopCommand->Start();
//		shootCommand->Start();
	}
	
	virtual void TeleopPeriodic() {
//		printf( "2135: TeleopPeriodic\n" );
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestPeriodic() {
//		printf( "2135: TestPeriodic\n" );
		Scheduler::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

