///////////////////////////////////////////////////////////////////////////////
//
//	ShooterOff.cpp
//
//	ShooterOff command definition file.
//

#include "ShooterOff.h"

ShooterOff::ShooterOff() {
	printf( "2135: ShooterOff - Constructed\n" );
	Requires( shooter );
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
}

// Called just before this Command runs the first time
void ShooterOff::Initialize() {
	printf( "2135: ShooterOff - Initialize\n" );
}

// Called repeatedly when this Command is scheduled to run
void ShooterOff::Execute() {
	static int i = 0;
	if ( i++ > 20 ) {
		i = 0 ;
		printf( "2135: ShooterOff\n" );
	}
	shooter->SetPower( 1, 1 );
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterOff::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ShooterOff::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterOff::Interrupted() {
}
