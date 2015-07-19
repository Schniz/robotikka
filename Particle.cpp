#include "Particle.h"

#include <cmath>
#include <cstdlib>

#include "Models/Cell.h"



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

void Particle::SetMap(AnotherMap* map) {
	this->map = map;
}

void Particle::Update(float deltaX, float deltaY, float deltaYaw,
		float laserArray[]) {

	// Erase the old paint on map
	this->UnPaint();

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

	// Paint the partical on the map
	this->Paint(BEST_EFFORT);
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

	for (int i = 0; i < LASER_FOV_DEGREE; i++) {
		mapx = round((
				cos(this->yaw) * (double) laserArray[i] * 100.0
						+ (double) this->x)/ ConfigurationManager::GetInstance()->getPngGridResolution());
		mapy = round((
				sin(this->yaw) * (double) laserArray[i] * 100.0
						+ (double) this->y) / ConfigurationManager::GetInstance()->getPngGridResolution());

		Cell* cell = this->map->getResizedCell(mapx, mapy);

		if (cell != NULL) {
			if (laserArray[i] < MAX_LEASER_DISTANCE
					&& cell->Cell_Cost == CellType::WALL) {
				matchCount++;
			}

			else if ((cell->Cell_Cost != CellType::WALL) && ((laserArray[i] - MAX_LEASER_DISTANCE)/MAX_LEASER_DISTANCE) > 0.1) {
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

	return p;
}

void Particle::Paint(float paintGood)
{
	Cell * c = this->map->getResizedCell(this->x,this->y);
	if (this->belief >= paintGood)
	{
		c->Cell_Color = CellColor::PATH;
	}
	else
	{
		c->Cell_Color = CellColor::DESTINATION;
	}

}

void Particle::UnPaint()
{
	Cell * c = this->map->getResizedCell(this->x,this->y);
	c->Cell_Color = (CellColor)c->Cell_Cost;
}


Particle::~Particle() {
	this->UnPaint();
}

