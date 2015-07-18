#include "LocalizationManager.h"



namespace Managers {

LocalizationManager::LocalizationManager(Location currLocation, AnotherMap* currMap)
{
	// add the location
	this->currLocation = Location(currLocation);
	this->particleList = std::list<Particle>();

	// firest particle
	Particle fatherParticle = Particle(this->currLocation.m_X,this->currLocation.m_Y,this->currLocation.m_Yaw,1);

	// give the father particle the map
	fatherParticle.SetMap(this->m_Map);

	// rando all the particle list
	for (unsigned i=0; i <= NUMBER_OF_PARTICLE; i++)
	{
		this->particleList.push_front(*(fatherParticle.CreateChild(PARTICALE_RADIOS_FROM_ROBOT,PARTICAL_DGREE_YAW_FROM_ROBOT)));
	}

}

void LocalizationManager::upDate(float deltaX, float deltaY, float deltaYaw, float laserArr[])
{
	//creat new chileds
	vector<list<Particle>::iterator> BestParticle;
	unsigned itCount = 0;
	cout << this->particleList.size() << endl;

	// update and delete
	for (std::list<Particle>::iterator it = this->particleList.begin(); it != this->particleList.end(); it++)
	{
		it->Update(deltaX,deltaY,deltaYaw,laserArr);
		if (it->belief < TRASHHOLE)
		{
			this->particleList.erase(it);
		}
		else if (it->belief > BEST_EFFORT)
		{
			BestParticle.push_back(it);
		}
	}

	// born new children
	for (unsigned i = 0; i < NUMBER_OF_PARTICLE - this->particleList.size(); i++)
	{
		this->particleList.push_front((*(BestParticle[i%BestParticle.size()])->CreateChild(PARTIACLE_CHILED_RADIOS_CM,PARTICAL_DGREE_YAW)));
	}
}

Location LocalizationManager::BestLocation()
{
	Particle best = this->particleList.front();
	for (Particle p : this->particleList)
	{
		if (best.belief < p.belief)
		{
			best = p;
		}
	}

	return (Location(best.x,best.y,best.yaw));
}

LocalizationManager::~LocalizationManager()
{
	this->currLocation.~Location();
	this->particleList.~list();
	}
}
