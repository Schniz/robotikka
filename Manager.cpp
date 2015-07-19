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

double circle(double num) {
	return fmod(num + 4 * 360, 360.0);
}

double calRawYaw(Cell* waypoint, Location* bestLocation) {
	unsigned int deltaY = abs(waypoint->getY() - bestLocation->getY());
	unsigned int deltaX = abs(waypoint->getX() - bestLocation->getX());
	double rawYaw = RTOD(atan(deltaY / deltaX));
	return rawYaw;
}

double getAngleToBe(Cell* waypoint, Location* bestLocation) {
	double rawYaw = calRawYaw(waypoint, bestLocation);
	double realYaw = rawYaw;

	if (bestLocation->getY() < waypoint->getY()) {
		if (bestLocation->getX() < waypoint->getX()) { // 1st
			realYaw = rawYaw;
		} else { // 2nd
			realYaw = 180 - rawYaw;
		}
	} else {
		if (bestLocation->getX() < waypoint->getX()) { // 4rd
			realYaw = 360 - rawYaw;
		} else { // 3th
			realYaw = 180 + rawYaw;
		}
	}

	return fmod(realYaw + 360, 360.0);
}

void Manager::rotateLikeShawarma(Cell* waypoint, Location* bestLocation) {
	double angleToBe = getAngleToBe(waypoint, bestLocation);
	cout << "angleToBe (radians): " << angleToBe << endl;
	double yaw = bestLocation->getYaw();
	double angleDifference = circle(angleToBe - yaw);
	while (angleDifference > 15) {
		int factor = angleDifference >= 180 ? -1 : 1;
		robot->setSpeed(0, factor * Consts::TURN_ANGULAR_SPEED);
		robot->Read();
		yaw = this->getBestLocation(waypoint).getYaw();
		angleDifference = circle(angleToBe - yaw);
	}
}

Location Manager::getBestLocation(Cell* waypoint) {
	double dx, dy, dyaw;
	float* allLasers = robot->getAllLasers();
	robot->calcLocationDeltas(dx, dy, dyaw);
	this->localizationManager->update((float) dx, (float) dy, (float) dyaw,
			allLasers, waypoint);
	Location bestLocation = this->localizationManager->BestLocation();
	delete[] allLasers;
	return bestLocation;
}

void Manager::run() {
	double dx = this->start->getX();
	double dy = this->start->getY();
	double dyaw =
			ConfigurationManager::GetInstance()->getStartLocation().getYaw();
	Location bestLocation = Location(dx, dy, dyaw);
	for (Cell* waypoint : waypointsManager->smoothWaypoints) {
		cout << "Starting to walk to " << waypoint->getX() << ","
				<< waypoint->getY() << endl;
		this->waypointsManager->currWaypoint = waypoint;
		bestLocation = this->getBestLocation(waypoint);
		while (!waypointsManager->IsInWaypoint(dx, dy)) {
			robot->Read();
			cout << "LOCATION: " << bestLocation.getX() << ","
					<< bestLocation.getY() << endl;
			this->rotateLikeShawarma(waypoint, &bestLocation);
			this->robot->setSpeed(Consts::MOVE_FORWARD_SPEED, 0);
			sleep(1);
			this->robot->setSpeed(0, 0);
			bestLocation = this->getBestLocation(waypoint);
		}
	}

	cout << "finished" << endl;
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
	Location startLocation = config->getStartLocation();
	Cell* startCell = this->start = locationToMapCell(map, startLocation);
	Cell* endCell = this->destination = locationToMapCell(map,
			config->getEndLocation());
	vector<Cell*> astarPath = astar.findPath(startCell, endCell);
	WaypointsManager* wayPointsManager = this->waypointsManager =
			new WaypointsManager(astarPath);

	Location startLocationPx = startCell->getLocation();
	startLocationPx.m_Yaw = startLocation.m_Yaw;
	double odemX = MathUtil::pxToCm(startLocationPx.getX()) / 100;
	double odemY = MathUtil::pxToCm(startLocationPx.getY()) / 100;
	this->robot->setOdemetry(
			odemX,
			odemY,
			DTOR(startLocationPx.getYaw()));
	this->robot->setLocation(
			startLocationPx.getX(),
			startLocationPx.getY(),
			startLocationPx.getYaw());
	this->robot->kickstart();
	this->localizationManager = new LocalizationManager(
		startLocationPx,
		map,
		wayPointsManager->longestDistance,
		robot->_lp
	);

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
	delete this->map;
	delete this->localizationManager;
}
