///////////////////////////////////////////////////////////////////////////////
//
//	CommandBase.cpp
//
//	Command Base initialization file.
//
#include "Commands/Scheduler.h"
#include "CommandBase.h"

//	Name method

CommandBase::CommandBase( const char *name ) : Command( name ) {
}

//	Command method

CommandBase::CommandBase() : Command() {
}

//	Subsystem pointer definition and initialization

Chassis*	CommandBase::chassis = NULL;
Shooter*	CommandBase::shooter = NULL;
OI*			CommandBase::oi = NULL;

//	Initialization routine to create valid subsystems

void CommandBase::init() {
	chassis = new Chassis();
	shooter = new Shooter();
	oi = new OI();
}
