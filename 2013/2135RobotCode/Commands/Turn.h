#ifndef TURN_H
#define TURN_H

#include "../CommandBase.h"

class Turn: public CommandBase {
	
private:
	double m_timeout;

public:
	Turn( double timeout );
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
