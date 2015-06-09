
#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "Consts.h"
#include "Utils/MathUtil.h"

using namespace std;
using namespace PlayerCc;
using namespace Consts;
using namespace Utils;

class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
public:
	Robot(char* ip, int port);
	void Read() {
		_pc->Read();
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		// TODO: check if we need to do:  cm_to_m to the x speed!

		_pp->SetSpeed(xSpeed, angularSpeed);
	}
	bool isRightFree() {
		if ((*_lp)[50] > 0.5)
			return true;
		else
			return false;
	}
	bool isForwardFree() {
		if ((*_lp)[332] > 0.5)
			return true;
		else
			return false;
	}

	double getXPosition();
	double getYPosition();
	double getYawPosition();

	double getRangeLaser(unsigned index);
	double getRangeLaser(double angle);

	virtual ~Robot();

protected:
	static double indexToAngle(int index, double fov, int size);
	static double indexToAngle(int index);
	static unsigned angleToIndex(double angle, double fov, int size);
	static unsigned angleToindex(double angle);
};

#endif /* ROBOT_H_ */
