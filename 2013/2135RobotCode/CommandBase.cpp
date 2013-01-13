#include "CommandBase.h"
#include "Commands/Scheduler.h"
#include "Subsystems/Shooter.h"

CommandBase::CommandBase( const char *name ) : Command( name ) {
}

CommandBase::CommandBase() : Command() {
}

Chassis* CommandBase::chassis = NULL;
Shooter* CommandBase::shooter = NULL;
OI* CommandBase::oi = NULL;

void CommandBase::init() {
	chassis = new Chassis();
	shooter = new Shooter();
	oi = new OI();
}
