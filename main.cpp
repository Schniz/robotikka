/*
 * main.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */
#include "Robot.h"
#include "Manager.h"
#include "Plans/PlnObstacleAvoid.h"
#include "lib/config.h"
#include "Managers/ConfigurationManager.h"
#include "Models/AnotherMap.h"

int main()
{
	cout << "<GAL MESAHEK IM MAPOT>" << endl;
	Managers::ConfigurationManager::LoadFromFile("./Resources/parameters.txt");
	AnotherMap* m = new AnotherMap();
	delete m;
	cout << "</GAL MESAHEK IM MAPOT>" << endl;
	Robot robot("localhost",6665);
	PlnObstacleAvoid plnOA(&robot);
	Manager manager(&robot, &plnOA);
	manager.run();
}
