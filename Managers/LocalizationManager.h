#pragma once

#include <vector>
#include "../Particle.h"
#include "../Models/Location.h"

using namespace std;

namespace Managers {

class LocalizationManager {


public:
	Location currLocation;
protected:
	// Data Member
	std::list<Particle> particleList;


	// Ctor
	LocalizationManager(Location currLocation);

	// Function
	void update (float deltaX, float deltaY, float deltaYaw, float laserArr[]);

	};
}
