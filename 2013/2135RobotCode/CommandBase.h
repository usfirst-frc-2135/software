///////////////////////////////////////////////////////////////////////////////
//
//	CommandBase.h
//
//	Header file base for all commands.
//
#ifndef COMMANDBASE_H
#define COMMANDBASE_H

#include "Commands/Command.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Shooter.h"
#include "OI.h"

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command {
	
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static Chassis	*chassis;
	static Shooter	*shooter;
	static OI 		*oi;
};

#endif
