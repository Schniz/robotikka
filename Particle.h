#pragma once


#include <float.h>

#include <math.h>

#include "Consts.h"
#include "Managers/ConfigurationManager.h"
#include "Models/AnotherMap.h"
#include "Utils/MathUtil.h"


using namespace std;
using namespace PlayerCc;
using namespace Consts;
using namespace Managers;

class Particle {

private:
	AnotherMap* map;

public:
	float x;
	float y;
	float yaw;
	float belief;
	double maxDistance;

	Particle();
	Particle(float x, float y, float yaw, float belief);
	~Particle();
	void SetMap(AnotherMap* map);
	void SetMaxDistance(double maxDistance);

	void Update(float deltaX, float deltaY, float deltaYaw, float laserArray[]);
	float ProbMovement(float deltaX, float deltaY, float deltaYaw);
	float ProbByScan(float laserArray[]);
	float Randomize(float min, float max);
	void Paint(float paintGood);
	void UnPaint();
	Particle* CreateChild(float expansionRadius, float yawRange);
};

