// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ShootFrameControl.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ShootFrameControl::ShootFrameControl(bool frameUp): Command() {
    m_frameUp = frameUp;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    m_timeout = 0.0;
    m_frameState = FRAME_START;
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ShootFrameControl::Initialize() {
	m_timer.Reset();
	m_timer.Start();
	m_timeout = Robot::LoadPreferencesVariable("ShootFrameTimeout", 0.4);
	SmartDashboard::PutNumber("ShootFrameTimeout", m_timeout);
	m_frameState = FRAME_START;

	printf("2135: Shooter Frame Extend\n");
	if (m_frameUp == true)
	{
		Robot::shooter->SetMotorSpeeds(0.0, -0.80);		// Run lower shooter motor
	}
}

// Called repeatedly when this Command is scheduled to run
void ShootFrameControl::Execute() {
	if (m_frameUp == true) {
		switch (m_frameState)
			{
			case FRAME_START:
				if (m_timer.HasPeriodPassed(m_timeout)) {
					m_frameState = FRAME_NEXT;
					Robot::shooter->SetWhiskerControl(true);		// Whiskers closed
					Robot::shooter->SetMotorSpeeds(0.0, 0.0);		// Motors off
					m_timer.Reset();
					m_timer.Start();
				}
				break;
			case FRAME_NEXT:
				if (m_timer.HasPeriodPassed(0.5)) {
					m_frameState = FRAME_MOVE;
					Robot::shooter->SetFrameControl(m_frameUp);		// Frame up
					m_timer.Reset();
					m_timer.Start();
				}
				break;
			case FRAME_MOVE:
				if (m_timer.HasPeriodPassed(0.5)) {
					m_frameState = FRAME_READY;
					Robot::shooter->SetFireSolenoid(false);			// Basket down
				}
				break;
			case FRAME_READY:
			default:
				break;
		}
	}
	else {
		switch (m_frameState)
			{
			case FRAME_START:
				if (m_timer.HasPeriodPassed(0.5)) {
					m_frameState = FRAME_NEXT;
					Robot::shooter->SetWhiskerControl(false);		// Whiskers open
					Robot::shooter->SetFireSolenoid(true);			// Basket up
					m_timer.Reset();
					m_timer.Start();
				}
				break;
			case FRAME_NEXT:
				if (m_timer.HasPeriodPassed(0.5)) {
					m_frameState = FRAME_READY;
					Robot::shooter->SetFrameControl(m_frameUp);		// Frame down
				}
				break;
			case FRAME_READY:
			default:
				break;
		}
	}

}

// Make this return true when this Command no longer needs to run execute()
bool ShootFrameControl::IsFinished() {
	return (m_frameState == FRAME_READY);
}

// Called once after isFinished returns true
void ShootFrameControl::End() {
	m_timer.Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShootFrameControl::Interrupted() {
	m_timer.Stop();
}
