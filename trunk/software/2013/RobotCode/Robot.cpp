// RobotBuilder Version: 0.0.2
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Robot.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
Chassis* Robot::chassis = 0;
Aiming* Robot::aiming = 0;
Shooter* Robot::shooter = 0;
Climber* Robot::climber = 0;
Pneumatics* Robot::pneumatics = 0;
OI* Robot::oi = 0;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
void Robot::RobotInit() {
	printf ( "\n2135: RobotInit - " __DATE__ " " __TIME__ "\n" );
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	chassis = new Chassis();
	aiming = new Aiming();
	shooter = new Shooter();
	climber = new Climber();
	pneumatics = new Pneumatics();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = new OI();
	lw = LiveWindow::GetInstance();
	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutonomousCommandGroup();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
}
	
void Robot::AutonomousInit() {
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}
	
void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}
	
void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to 
	// continue until interrupted by another command, remove
	// this line or comment it out.
	autonomousCommand->Cancel();
}
	
void Robot::TeleopPeriodic() {
	if (autonomousCommand != NULL)
		Scheduler::GetInstance()->Run();	
	SmartDashboard::PutNumber( "Driver Throttle", - ( Robot::oi->getDriverThrottle() - 1 ) / 2 );
	SmartDashboard::PutNumber( "Operator Throttle", - ( Robot::oi->getOperatorThrottle() - 1 ) / 2 );	
	SmartDashboard::PutNumber( "Shooter Exit Encoder", Robot::shooter->exitShooterEncoder->GetRate() );
	SmartDashboard::PutNumber( "Right Drive Encoder", Robot::chassis->rightEncoder->GetDistance());
	SmartDashboard::PutNumber ( "Left Drive Encoder", Robot::chassis->leftEncoder->GetDistance());
	SmartDashboard::PutData( "Scheduler Data", Scheduler::GetInstance() );
}
void Robot::TestPeriodic() {
	static int	i = 0;
	RobotMap::chassisDriveTrain->SetSafetyEnabled(false);
	if ( i++ > 10 ) {		// Update only once in every 5 DS packets ( 10 times per second)
		lw->Run();
		i = 0;
	}
}
START_ROBOT_CLASS(Robot);
