#pragma once

#include "Consts.h"
#include "Utils/MathUtil.h"
#include "Models/Map.h"
#include "Robot.h"
#include <libplayerc++/playerc++.h>

using namespace std;
using namespace PlayerCc;
using namespace Consts;

class Particle {

private:
//	Robot* robot;

public:
	float x;
	float y;
	float yaw;
	float belief;

	Particle();
	Particle(float x, float y, float yaw, float belief);
	~Particle();
	void Update(float deltaX, float deltaY, float deltaYaw, float laserArray[],
			int laserCount);
	float ProbMovement(float deltaX, float deltaY, float deltaYaw);
	float ProbByScan(float laserArray[], int laserCount);

};

