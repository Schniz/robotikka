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
#include "Utils/AStarUtil.h"

using namespace Utils;

int main()
{
//	Robot robot("localhost",6665);
//	PlnObstacleAvoid plnOA(&robot);
//	Manager manager(&robot, &plnOA);
//	manager.run();

	// init configuration manager
	ConfigurationManager::LoadFromFile("Resources/parameters.txt");
	// load map
	//const char* c = ConfigurationManager::GetInstance()->getPngMapPath();
	//Map *m = (Map*)malloc(sizeof(Map));
	//ConvertMapBlackToWhiteAndWhiteToBlack("/home/colman/git/robotikka/Reasurce/Grid.png");
	Map *m = new Map(strtok(&ConfigurationManager::GetInstance()->getPngMapPath()[0], " "));
	//m->PrintMap("/home/colman/git/robotikka/Release/Grid.png");
	cout << "HEY" << endl;

	// Throws an exception :D
	//	AStarUtil astar(m);
	//	Cell* start = m->getCell(0, 0);
	//	Cell* destination = m->getCell(4, 4);
	//	vector<Cell*> path = astar.findPath(start, destination);
	//	cout << "PATH LENGTH: " << path.size() << endl;
	//	for (Cell* cell : path) {
	//		cout << "[" << cell->getX() << "," << cell->getY() << "]" << endl;
	//	}
}
