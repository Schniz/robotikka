/*
 * main.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */
#include "Robot.h"
#include "Manager.h"
#include "Plans/PlnObstacleAvoid.h"

//map check
#include "Managers/ConfigurationManager.h"
#include "Models/Map.h"

int main()
{
//	Robot robot("localhost",6665);
//	PlnObstacleAvoid plnOA(&robot);
//	Manager manager(&robot, &plnOA);
//	manager.run();

	// init configuration manager
	ConfigurationManager::LoadFromFile("Reasurce\parameters.txt");
	// load map
	//const char* c = ConfigurationManager::GetInstance()->getPngMapPath();
	//Map *m = (Map*)malloc(sizeof(Map));
	//ConvertMapBlackToWhiteAndWhiteToBlack("/home/colman/git/robotikka/Reasurce/Grid.png");
	Map *m = new Map(strtok(&ConfigurationManager::GetInstance()->getPngMapPath()[0], " "));
	//m->PrintMap("/home/colman/git/robotikka/Release/Grid.png");
}
