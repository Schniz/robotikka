#pragma once

#include <vector>
#include "../Particle.h"
#include "../Models/Location.h"
#include "../Consts.h"
#include <float.h>

using namespace std;

namespace Managers {

class LocalizationManager {


public:
	// Data Member
	Location currLocation;
	AnotherMap* m_Map;

	// Function
	void upDate(float deltaX, float deltaY, float deltaYaw, float laserArr[]);
	Location BestLocation();

protected:
	// Data Member
	std::list<Particle> particleList;

	// Ctor
	LocalizationManager(Location currLocation,  AnotherMap* currMap);

	// Dtor
	~LocalizationManager();
	};
}
