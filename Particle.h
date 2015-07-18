#pragma once

#include "Consts.h"
#include "Utils/MathUtil.h"
#include "Models/Map.h"
#include "Robot.h"
#include <libplayerc++/playerc++.h>
#include <math.h>
#include <float.h>

using namespace std;
using namespace PlayerCc;
using namespace Consts;

class Particle {

private:
	Map* map;

public:
	float x;
	float y;
	float yaw;
	float belief;

	Particle();
	Particle(float x, float y, float yaw, float belief, Map* map);
	~Particle();
	void Update(float deltaX, float deltaY, float deltaYaw, float laserArray[],
			int laserCount, LaserProxy* lp);
	float ProbMovement(float deltaX, float deltaY, float deltaYaw);
	float ProbByScan(float laserArray[], int laserCount, LaserProxy* lp);
	float Randomize(float dMin, float dMax);
	Particle* CreateChild();
	Particle* CreateChild(float expansionRadius, float yawRange);
};

