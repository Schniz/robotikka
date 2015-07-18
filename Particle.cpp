#include "Particle.h"

Particle::Particle() {
}

Particle::Particle(float x, float y, float yaw, float belief) {
	this->x = x;
	this->y = y;
	this->yaw = yaw;
	this->belief = belief;
}

void Particle::Update(float deltaX, float deltaY, float deltaYaw,
		float laserArray[], int laserCount) {
	this->x += deltaX;
	this->y += deltaY;
	this->yaw += deltaYaw;

	float predictionBelif = ProbMovement(deltaX, deltaY, deltaYaw)
			* this->belief;

	// TODO: check ?!
	float probabilityByScan = ProbByScan(laserArray, laserCount);

	this->belief = probabilityByScan * predictionBelif * BEL_NOR;

	if (this->belief > 1)
		this->belief = 1;
}

float Particle::ProbMovement(float deltaX, float deltaY, float deltaYaw) {
	float distance = sqrt(pow(deltaX,2) + pow(deltaY,2));

	// TODO: check this !
	if ((deltaYaw < NORMAL_ANGLE_TO_MOVE) && (deltaYaw > -NORMAL_ANGLE_TO_MOVE)) {
		if (distance <= SAFE_DISTANCE_TO_MOVE)
			return 1.0;
		else
			return (SAFE_DISTANCE_TO_MOVE + distance + 0.2);
	}
	else if ((deltaYaw < MAX_ANGLE_TO_MOVE) && (deltaYaw > -MAX_ANGLE_TO_MOVE))
	{
		if (distance <= SAFE_DISTANCE_TO_MOVE)
			return 1.0;
		else
			return (SAFE_DISTANCE_TO_MOVE + distance - 0.2);
	}
	return 1.0;

}

float Particle::ProbByScan(float laserArray[], int laserCount) {

}
Particle::~Particle() {
}
