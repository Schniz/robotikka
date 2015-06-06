
#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behavior.h"

class TurnLeft: public Behavior {
public:
	TurnLeft(Robot* robot);

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
	{	//TODO: this
		_robot->setSpeed(0.0, 0.3);
	}

	virtual ~TurnLeft();
};

#endif /* TURNLEFT_H_ */
