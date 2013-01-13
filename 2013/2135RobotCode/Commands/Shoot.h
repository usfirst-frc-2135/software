#ifndef SHOOT_H
#define SHOOT_H

#include "../CommandBase.h"

/**
 *
 *
 * @author PHS-User
 */
class Shoot: public CommandBase {
	
public:
	Shoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
