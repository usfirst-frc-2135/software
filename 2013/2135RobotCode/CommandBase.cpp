#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase( const char *name ) : Command( name ) {
}

CommandBase::CommandBase() : Command() {
}

Chassis* CommandBase::chassis = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
	chassis = new Chassis();
	
	oi = new OI();
}
