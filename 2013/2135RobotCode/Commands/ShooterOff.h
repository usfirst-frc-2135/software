///////////////////////////////////////////////////////////////////////////////
//
//	ShooterOff.h
//
//	ShooterOff command header file.
//
#ifndef SHOOTEROFF_H
#define SHOOTEROFF_H

#include "../CommandBase.h"

/**
 *
 *
 * @author PHS-User
 */
class ShooterOff: public CommandBase {
public:
	ShooterOff();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
