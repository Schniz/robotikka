/*
 * PlnObstacleAvoid.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "../behaviors/MoveBackward.h"
#include "../behaviors/MoveForward.h"
#include "../behaviors/TurnInPlace.h"
#include "../behaviors/TurnLeft.h"
#include "../behaviors/TurnRight.h"
#include "Plan.h"

class PlnObstacleAvoid: public Plan {
	Behavior* _beh[5];

public:
	PlnObstacleAvoid(Robot* robot);
	Behavior* getStartPoint(){return _start;}
	virtual ~PlnObstacleAvoid();
};

#endif /* PLNOBSTACLEAVOID_H_ */
