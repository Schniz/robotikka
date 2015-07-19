#pragma once

#include "Consts.h"
#include "Utils/MathUtil.h"
#include "Models/AnotherMap.h"
#include <libplayerc++/playerc++.h>
#include <math.h>
#include <float.h>
#include "Managers/ConfigurationManager.h"

using namespace std;
using namespace PlayerCc;
using namespace Consts;
using namespace Managers;

class Particle {

private:
	AnotherMap* map;

public:
	LaserProxy* laserProxy;
	float x;
	float y;
	float yaw;
	float belief;
	double maxDistance;

	Particle();
	Particle(float x, float y, float yaw, float belief);
	~Particle();
	void SetLaserProxy(LaserProxy* laserProxy);
	void SetMap(AnotherMap* map);
	void SetMaxDistance(double maxDistance);

	void Update(float deltaX, float deltaY, float deltaYaw, float laserArray[]);
	float ProbMovement(float deltaX, float deltaY, float deltaYaw);
	float ProbByScan(float laserArray[]);
	float Randomize(float min, float max);

	Particle* CreateChild(float expansionRadius, float yawRange);
};

