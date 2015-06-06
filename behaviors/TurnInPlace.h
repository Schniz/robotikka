
#ifndef TURNINPLACE_H_
#define TURNINPLACE_H_

#include "Behavior.h"

class TurnInPlace: public Behavior {
public:
	TurnInPlace(Robot* robot);

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

	virtual ~TurnInPlace();
};

#endif /* TURNINPLACE_H_ */
