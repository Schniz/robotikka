#include "Manager.h"
#include "Managers/ConfigurationManager.h"
#include "Managers/WaypointsManager.h"
#include "Models/Map.h"
#include "Utils/MathUtil.h"
#include "Utils/AStarUtil.h"
#include <vector>

#define POSITION_INACCURACY 3

using namespace std;
using namespace Utils;

Manager::Manager(Robot* robot, Plan* pln) {
	this->robot = robot;
	this->currentPoint = pln->getStartPoint();
	this->plan = pln;
	this->InitApp();
}
void Manager::run() {
	while (
		MathUtil::distance(
			robot->getXPosition(),
			robot->getYPosition(),
			this->destination->getX(),
			this->destination->getY()
		) <= POSITION_INACCURACY
	) {
		robot->Read();
	}

	/*
	while (currentPoint->stopCond()) {
		currentPoint = currentPoint->selectNext();

		if (currentPoint == NULL) {
			return;
		}
	}
	currentPoint->action();
	while (currentPoint != NULL) {
		while (!currentPoint->stopCond()) {
			currentPoint->action();
			robot->Read();
		}
		currentPoint = currentPoint->selectNext();
		robot->Read();
	}
	*/
}

Cell* locationToMapCell(AnotherMap* map, Location location) {
	return map->getResizedCellFromImageCoords(location.getX(), location.getY());
}

void Manager::InitApp() {
	// init configuration manager
	ConfigurationManager* config = ConfigurationManager::LoadFromFile(
			"Resources/parameters.txt");
	AnotherMap* map = this->map = new AnotherMap(config);
	AStarUtil astar(map);
	Cell* startCell = locationToMapCell(map, config->getStartLocation());
	Cell* endCell = locationToMapCell(map, config->getEndLocation());
	vector<Cell*> astarPath = astar.findPath(
		startCell,
		endCell
	);
	WaypointsManager* wayPointsManager = this->waypointsManager =
			new WaypointsManager(astarPath);

	Location startLocationPx = startCell->getLocation();
	startLocationPx.m_Yaw = config->getStartLocation().m_Yaw;
	this->localizationManager = new LocalizationManager(startLocationPx, map);

	for (Cell* cell : astarPath) {
		cell->Cell_Cost = CellType::PATH;
	}

	for (Cell* cell : wayPointsManager->smoothWaypoints) {
		cout << "[" << cell->getX() << "," << cell->getY() << "]" << endl;
		cell->Cell_Cost = CellType::DESTINATION;
	}

	map->saveToFile("/tmp/waypoints.png", true);

	cout << astarPath.size() << "-" << wayPointsManager->smoothWaypoints.size()
			<< " = "
			<< (astarPath.size() - wayPointsManager->smoothWaypoints.size())
			<< endl;
}

Manager::~Manager() {
	delete this->waypointsManager;
	delete this->localizationManager;
}
