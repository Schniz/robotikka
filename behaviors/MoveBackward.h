#ifndef MOVEBACKWARD_H_
#define MOVEBACKWARD_H_

#include "Behavior.h"

class MoveBackward: public Behavior {
public:
	MoveBackward(Robot* robot);

	bool startCond()
	{
		//TODO: this
		return true;
	}

	bool stopCond()
	{
		//TODO: this
		return true;
	}

	void action()
	{
		_robot->setSpeed(0.0, 0.3);
	}

	virtual ~MoveBackward();
};

#endif /* MOVEBACKWARD_H_ */
