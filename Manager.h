/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Plans/PlnObstacleAvoid.h"
#include "Robot.h"


class Manager {
	Behavior* _curr;
	Robot* _robot;
	Plan* _plan;

public:
	Manager(Robot* robot, Plan* pln);
	void run();
	virtual ~Manager();
	void InitApp();
};

#endif /* MANAGER_H_ */
