#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behavior.h"
#include "../Consts.h"

class TurnLeft: public Behavior {
public:
	TurnLeft(Robot* robot);

	bool startCond() {
		//TODO: this
		return true;
	}

	bool stopCond() {
		//TODO: this
		return true;
	}

	void action() {
		_robot->setSpeed(TURN_SPEED, TURN_ANGULAR_SPEED);
	}

	virtual ~TurnLeft();
};

#endif /* TURNLEFT_H_ */
