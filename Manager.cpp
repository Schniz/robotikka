
#include "Manager.h"
#include "Managers/ConfigurationManager.h"
#include "Managers/WaypointsManager.h"
#include "Models/Map.h"
#include "Utils/AStarUtil.h"
#include <vector>

using namespace std;
using namespace Utils;

Manager::Manager(Robot* robot, Plan* pln) {
	this->robot = robot;
	this->currentPoint = pln->getStartPoint();
	this->plan = pln;
	this->InitApp();
}
void Manager::run()
{
		robot->Read();
		while (currentPoint->stopCond())
		{
			currentPoint = currentPoint->selectNext();

			if (currentPoint == NULL) {
				return;
			}
		}
		currentPoint->action();
		while(currentPoint != NULL)
		{
			while(!currentPoint->stopCond())
			{
				currentPoint->action();
				robot->Read();
			}
			currentPoint = currentPoint->selectNext();
			robot->Read();
		}
}

Cell* locationToMapCell(AnotherMap* map, Location location) {
	return map->getResizedCellFromImageCoords(location.getX(), location.getY());
}

void Manager::InitApp()
{
	int i = 0;
	// init configuration manager
	cout << ++i << endl;
	ConfigurationManager* config = ConfigurationManager::LoadFromFile("Resources/parameters.txt");
	cout << ++i << endl;
	AnotherMap* map = new AnotherMap(config);
	cout << ++i << endl;
	AStarUtil astar(map);
	cout << ++i << endl;
	vector<Cell*> astarPath = astar.findPath(
			locationToMapCell(map, config->getStartLocation()),
			locationToMapCell(map, config->getEndLocation()));
	cout << ++i << endl;
	WaypointsManager wayPointsManager(astarPath);
	cout << ++i << endl;

	for (Cell* cell : astarPath) {
		cell->Cell_Cost = CellType::PATH;
	}

	for (Cell* cell : wayPointsManager.smoothWaypoints) {
		cout << "[" << cell->getX() << "," << cell->getY() << "]" << endl;
		cell->Cell_Cost = CellType::DESTINATION;
	}

	map->saveToFile("/tmp/waypoints.png", true);
	map->saveToFile("/tmp/waypoints2.png",false);

	cout << astarPath.size() << "-" << wayPointsManager.smoothWaypoints.size() << " = " << (astarPath.size() - wayPointsManager.smoothWaypoints.size()) << endl;
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
