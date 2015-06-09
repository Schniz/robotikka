#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include "Behavior.h"
#include "../Consts.h"

class MoveForward: public Behavior {
public:
	MoveForward(Robot* robot);

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
		_robot->setSpeed(MOVE_FORWARD_SPEED, 0);
	}

	virtual ~MoveForward();
};

#endif /* MOVEFORWARD_H_ */
