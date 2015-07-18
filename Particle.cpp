#include "Particle.h"

Particle::Particle() {
	this->x = 0;
	this->y = 0;
	this->yaw = 0;
	this->belief = 0;
}

Particle::Particle(float x, float y, float yaw, float belief) {
	this->x = x;
	this->y = y;
	this->yaw = yaw;
	this->belief = belief;
}

void Particle::SetMap(Map* map)
{
	this->map = map;
}

void Particle::Update(float deltaX, float deltaY, float deltaYaw,
		float laserArray[], int laserCount, LaserProxy* lp) {
	this->x += deltaX;
	this->y += deltaY;
	this->yaw += deltaYaw;

	float predictionBelif = ProbMovement(deltaX, deltaY, deltaYaw)
			* this->belief;

	// TODO: check ?!
	float probabilityByScan = ProbByScan(laserArray, laserCount, lp);

	this->belief = probabilityByScan * predictionBelif * BEL_NOR;

	if (this->belief > 1)
		this->belief = 1;
}

float Particle::ProbMovement(float deltaX, float deltaY, float deltaYaw) {
	float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

//	// TODO: check this !
//	if ((deltaYaw < NORMAL_ANGLE_TO_MOVE)
//			&& (deltaYaw > -NORMAL_ANGLE_TO_MOVE)) {
//		if (distance <= SAFE_DISTANCE_TO_MOVE)
//			return 1.0;
//		else
//			return (SAFE_DISTANCE_TO_MOVE + distance + 0.2);
//	} else if ((deltaYaw < MAX_ANGLE_TO_MOVE)
//			&& (deltaYaw > -MAX_ANGLE_TO_MOVE)) {
//		if (distance <= SAFE_DISTANCE_TO_MOVE)
//			return 1.0;
//		else
//			return (SAFE_DISTANCE_TO_MOVE + distance - 0.2);
//	}
//	return 1.0;

	//float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
	float movementProb, angleProb, prob;

	movementProb = MAX_ACCURATE_MOVEMENT / distance;
	angleProb = MAX_ACCURATE_ANGLE / deltaYaw;

	if (deltaYaw > -MAX_ACCURATE_ANGLE && deltaYaw < MAX_ACCURATE_ANGLE)
		if (movementProb >= 1)
			return 1;

	prob = NIE * movementProb * angleProb;

	if (prob > 1)
		prob = 1;

	return prob;
}

float Particle::ProbByScan(float laserArray[], int laserCount, LaserProxy* lp) {

	double mapx, mapy;
	int countMiss = 0;
	int countHit = 0;
}

float Particle::Randomize(float min, float max)
{
	float num = (float)rand() / RAND_MAX;
	return min + num * (max - min);
}

Particle* Particle::CreateChild() {
	return CreateChild(EXPANSION_RADIUS, YAW_RANGE);
}

Particle* Particle::CreateChild(float dExpansionRadius, float dYawRange) {
	float newX = this->x + Randomize(-dExpansionRadius, dExpansionRadius);
	float newY = this->y + Randomize(-dExpansionRadius, dExpansionRadius);
	float newYaw = this->yaw + Randomize(-dYawRange, dYawRange);
	return new Particle(newX, newY, newYaw, 1);
}

Particle::~Particle() {
}
