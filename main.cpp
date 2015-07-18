/*
 * main.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */
#include "Robot.h"
#include "Manager.h"
#include "Plans/PlnObstacleAvoid.h"
#include <stdarg.h>

#define RUN_ROBOT false

//map check
#include "Managers/ConfigurationManager.h"
#include "Models/Map.h"
#include "Utils/AStarUtil.h"
#include "Models/AnotherMap.h"

using namespace std;
using namespace Utils;

int main()
{
	if (RUN_ROBOT) {
		Robot robot("localhost",6665);
		PlnObstacleAvoid plnOA(&robot);
		Manager manager(&robot, &plnOA);
		manager.run();
	}

	ConfigurationManager::LoadFromFile("Resources/parameters.txt");
	Managers::ConfigurationManager* config =
			ConfigurationManager::GetInstance();
	AnotherMap* m = new AnotherMap(config);
	AStarUtil::testWithMap(m);
}
