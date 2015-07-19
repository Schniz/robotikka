#include "Particle.h"

Particle::Particle() {
	this->x = 0;
	this->y = 0;
	this->yaw = 0;
	this->belief = 0;
	this->maxDistance = 0;
}

Particle::Particle(float x, float y, float yaw, float belief) {
	this->x = x;
	this->y = y;
	this->yaw = yaw;
	this->belief = belief;
	this->maxDistance = 0;
}

void Particle::SetLaserProxy(LaserProxy* laserProxy) {
	this->laserProxy = laserProxy;
}

void Particle::SetMap(AnotherMap* map) {
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
			- ((distance / this->maxDistance)
					* (deltaYaw / LASER_FOV_DEGREE));

	if (prob > 1)
		prob = 1;

	return prob;
}

float Particle::ProbByScan(float laserArray[]) {

	int matchCount = 0;

	int mapx = 0;
	int mapy = 0;

	for (int i = 0; i < 1024; i++) {
		mapx = round((
				cos(DTOR(this->yaw) + laserProxy->GetBearing(i)) * (double) laserArray[i] * 100.0
						+ (double) this->x)/ ConfigurationManager::GetInstance()->getPngGridResolution());
		mapy = map->gridHeight - round((
				sin(DTOR(this->yaw) + laserProxy->GetBearing(i)) * (double) laserArray[i] * 100.0
						+ (double) this->y) / ConfigurationManager::GetInstance()->getPngGridResolution());

		Cell* cell = this->map->getResizedCell(mapx, mapy);

		if (cell != NULL) {
			if (laserArray[i] < MAX_LEASER_DISTANCE
					&& cell->Cell_Cost == CellType::WALL) {
				matchCount++;
			}

			else if (cell->Cell_Cost != CellType::WALL) {
				matchCount++;
			}
		}

	}

	return matchCount / LASER_FOV_DEGREE;

}

float Particle::Randomize(float min, float max) {
	float num = (float) rand() / RAND_MAX;
	return min + num * (max - min);
}

void Particle::SetMaxDistance(double maxDistance) {
	this->maxDistance = maxDistance;
}

Particle* Particle::CreateChild(float dExpansionRadius, float dYawRange) {
	float newX = this->x + Randomize(-dExpansionRadius, dExpansionRadius);
	float newY = this->y + Randomize(-dExpansionRadius, dExpansionRadius);
	float newYaw = this->yaw + Randomize(-dYawRange, dYawRange);
	Particle* p = new Particle(newX, newY, newYaw, 1);
	p->SetMap(this->map);
	p->SetMaxDistance(this->maxDistance);
	p->SetLaserProxy(this->laserProxy);

	return p;
}

Particle::~Particle() {
}

