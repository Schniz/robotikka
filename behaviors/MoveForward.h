#ifndef MOVEFORWARD_H_
#define MOVEFORWARD_H_

#include "Behavior.h"

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
		_robot->setSpeed(0.0, 0.3);
	}

	virtual ~MoveForward();
};

#endif /* MOVEFORWARD_H_ */
