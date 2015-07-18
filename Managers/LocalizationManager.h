#pragma once

#include <vector>
#include "../Particle.h"
#include "../Models/Location.h"
#include <float.h>

// defind
#define NUMBER_OF_PARTICLE 100
#define TRASHHOLE 0.5
#define BEST_EFFORT 0.9

using namespace std;

namespace Managers {

class LocalizationManager {


public:
	// Data Member
	Location currLocation;
	Map* m_Map;

	// Function
	void upDate(float deltaX, float deltaY, float deltaYaw, float laserArr[]);
	Location BestLocation();

protected:
	// Data Member
	std::list<Particle> particleList;

	// Ctor
	LocalizationManager(Location currLocation,  Map* currMap);

	// Dtor
	~LocalizationManager();
	};
}
