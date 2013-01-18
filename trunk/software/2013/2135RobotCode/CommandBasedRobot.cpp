#include "WPILib.h"
#include "Commands/Command.h"
#include "Subsystems/Chassis.h"
#include "CommandBase.h"
//#include "Commands/Shoot.h"
#include "Commands/DriveStraight.h"
#include "DashboardDataFormat.h"

class CommandBasedRobot : public IterativeRobot {
	DashboardDataFormat dashboardDataFormat;

private:
	Command *autonomousCommand;
	LiveWindow *lw;

	virtual void RobotInit() {
		printf( "2135: RobotInit\n" );
		CommandBase::init();
		autonomousCommand = new DriveStraight(1);
		lw = LiveWindow::GetInstance();
	}
	
	virtual void AutonomousInit() {
		printf( "2135: AutonomousInit\n" );
		autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
//		printf( "2135: AutonomousPeriodic\n" );
		Scheduler::GetInstance()->Run();
		dashboardDataFormat.SendIOPortData();
		dashboardDataFormat.SendVisionData();
		SmartDashboard::PutData( "SchedulerData", (Sendable*) Scheduler::GetInstance() );
	}
	
	virtual void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		printf( "2135: TeleopInit\n" );
		autonomousCommand->Cancel();
	}
	
	virtual void TeleopPeriodic() {
//		printf( "2135: TeleopPeriodic\n" );
		Scheduler::GetInstance()->Run();
		dashboardDataFormat.SendIOPortData();
		dashboardDataFormat.SendVisionData();
		SmartDashboard::PutData( "SchedulerData", (Sendable*) Scheduler::GetInstance() );
//		SmartDashboard::PutData( chassis );
	}
	
	virtual void TestPeriodic() {
//		printf( "2135: TestPeriodic\n" );
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

