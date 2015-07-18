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

void Particle::SetMap(Map* map) {
	this->map = map;
}

void Particle::Update(float deltaX, float deltaY, float deltaYaw,
		float laserArray[]) {
	this->x += deltaX;
	this->y += deltaY;
	this->yaw += deltaYaw;

	float predictionBelif = ProbMovement(deltaX, deltaY, deltaYaw)
			* this->belief;

	// TODO: check ?!
	float probabilityByScan = ProbByScan(laserArray);

	this->belief = probabilityByScan * predictionBelif * BEL_NOR;

	if (this->belief > 1)
		this->belief = 1;
}

float Particle::ProbMovement(float deltaX, float deltaY, float deltaYaw) {
	float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2)); // cm?

	float prob = 0;

	prob = 1
			- (distance / (MAX_LEASER_DISTANCE * 100)
					+ deltaYaw / DTOR(LASER_FOV_DEGREE));

	if (prob > 1)
		prob = 1;

	return prob;
}

float Particle::ProbByScan(float laserArray[]) {

	int matchCount = 0;

	int mapx = 0;
	int mapy = 0;

	for (int i = 0; i < LASER_FOV_DEGREE; i++) {
		mapx = round(cos(this->yaw) * laserArray[i] * 100 + this->x);
		mapy = round(sin(this->yaw) * laserArray[i] * 100 + this->y);

		if (laserArray[i] < MAX_LEASER_DISTANCE
				&& this->map->getCell(mapx, mapy)->Cell_Cost == CellType::WALL)
			matchCount++;

		else if (this->map->getCell(mapx, mapy)->Cell_Cost != CellType::WALL)
			matchCount++;

	}

	return matchCount / LASER_FOV_DEGREE;

}

float Particle::Randomize(float min, float max) {
	float num = (float) rand() / RAND_MAX;
	return min + num * (max - min);
}


Particle* Particle::CreateChild(float dExpansionRadius, float dYawRange) {
	float newX = this->x + Randomize(-dExpansionRadius, dExpansionRadius);
	float newY = this->y + Randomize(-dExpansionRadius, dExpansionRadius);
	float newYaw = this->yaw + Randomize(-dYawRange, dYawRange);
	Particle* p = new Particle(newX, newY, newYaw, 1);
	p->SetMap(this->map);

	return p;
}

Particle::~Particle() {
}
