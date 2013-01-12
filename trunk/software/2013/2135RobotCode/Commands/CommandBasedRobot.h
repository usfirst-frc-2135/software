#ifndef DRIVESTRAIGHT_H
#define DRIVESTRAIGHT_H

#include "../CommandBase.h"

class DriveStraight: public CommandBase {
public:
	DriveStraight(double timeout);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
