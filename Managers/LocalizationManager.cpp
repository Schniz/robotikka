#include "LocalizationManager.h"

namespace Managers {

LocalizationManager::LocalizationManager(Location currLocation)
{
	// add the location
	this->currLocation = new Location(currLocation);
	this->particleList = new std::list<Particle>();

	// rando all the particle list
	for (unsigned i=0; i <= NUMBER_OF_PARTICAL; i++)
	{}
}
}
