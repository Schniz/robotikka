#include "WaypointsManager.h"

namespace Managers {

WaypointsManager::WaypointsManager(vector<Waypoint> waypoints, float radius) :
		radius(radius) {
	waypointsVec = waypoints;


	SmoothWaypoints();

	currWaypoint = NULL;
}

void WaypointsManager::SmoothWaypoints() {

	float firstIncline = MathUtil::incline(waypointsVec[0].getX(),
			waypointsVec[0].getY(), waypointsVec[1].getX(),
			waypointsVec[1].getY());

	float currIncline = 0;
	smoothWaypoints.push_back(waypointsVec[0]);

	for (int i = 0; i < waypointsVec.size() - 1; i++) {

		float firstIncline = MathUtil::incline(waypointsVec[i].getX(),
				waypointsVec[i].getY(), waypointsVec[i + 1].getX(),
				waypointsVec[i + 1].getY());

		if(currIncline != firstIncline && abs(currIncline - firstIncline) >= 5)
		{
			smoothWaypoints.push_back(waypointsVec[i+1]);
			firstIncline = currIncline;
		}
	}

}

WaypointsManager::~WaypointsManager() {
	delete currWaypoint;
	currWaypoint = NULL;
}

bool WaypointsManager::WaypointDriver(Waypoint wp, Robot rob) {

	// TODO: DO IT
	return false;

}

bool WaypointsManager::IsInWaypoint(double xp, double yp) {
	return MathUtil::equals(xp, currWaypoint->getX())
			&& MathUtil::equals(yp, currWaypoint->getY());

}
}
