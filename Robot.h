#pragma once

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "Consts.h"
#include "Utils/MathUtil.h"

using namespace std;
using namespace PlayerCc;
using namespace Consts;

class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;

public:
	Robot(char* ip, int port);
	void Read() {
		// TODO
		_pc->Read();
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		// TODO: check if we need to do:  cm_to_m to the x speed! we need.
		// TODO: need to check if do it here or in the caller method

		_pp->SetSpeed(xSpeed, angularSpeed);
	}

	bool canMoveForward();
	bool canTurnRight();
	bool canTurnLeft();

	void calcLocationDeltas(double &DelX, double &DelY, double &DelYaw);
	double getDistanceFromObstacle(int index);
	double getXPosition();
	double getYPosition();
	double getYawPosition();

	double getRangeLaser(unsigned index);
	double getRangeLaser(double angle);
	double getRaysRangeSum(double rangeStartAngle, double rangeEndAngle);

	virtual ~Robot();

protected:
	static double indexToAngle(int index);
	static unsigned angleToIndex(double angle);
	static double convertDegreesToRadians(double deg);
	bool canTurnInDirection(double startRangeAngle, double endRangeAngle);

	double robot_XPos;
	double robot_YPos;
	double robot_Yaw;
};

#endif /* ROBOT_H_ */
