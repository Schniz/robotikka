/*
 * TurnRight.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef TURNRIGHT_H_
#define TURNRIGHT_H_

#include "Behavior.h"

class TurnRight: public Behavior {
public:
	TurnRight(Robot* robot);
	bool startCond() {	//TODO: this
		if (_robot->isRightFree())
			return true;
		else
			return false;
	}
	bool stopCond() {	//TODO: this
		if (_robot->isForwardFree())
			return true;
		else
			return false;
	}

	void action() {	//TODO: this
		_robot->setSpeed(0.0, 0.3);
	}
	virtual ~TurnRight();
};

#endif /* TURNRIGHT_H_ */
