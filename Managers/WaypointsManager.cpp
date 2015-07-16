#include "WaypointsManager.h"

namespace Managers {

WaypointsManager::WaypointsManager(vector<Waypoint> waypoints, float radius) :
		radius(radius) {
	waypointsVec = waypoints;

	smoothSize = waypoints.size() / 100 + 1;

	smoothWaypoints = vector<Waypoint>(smoothSize);

	SmoothWaypoints();

	currWaypoint = NULL;
}

void WaypointsManager::SmoothWaypoints() {
	for (int i = 0; i < smoothSize; i++) {
		smoothWaypoints[i] = new Waypoint(waypointsVec[i + 100]);
	}
}

WaypointsManager::~WaypointsManager() {
	delete currWaypoint;
	currWaypoint = NULL;
}

//Waypoint WaypointsManager::update(Location newRobotLoc) {
////	if (crrWaypoint == NULL || shouldMoveNext(newRobotLoc)) {
////		currWaypoint = &waypointsQueue.front();
////		m_WaypointsQueue.pop();
////	}
////
////	return *m_CurrWaypoint;
////
//	return NULL;
//
//
//}
//
//bool WaypointsManager::shouldMoveNext(Location newRobotLoc) {
////	return MathUtil::equals(newRobotLoc.getX(), m_CurrWaypoint->getX(),
////			m_Radius)
////			&& MathUtil::equals(newRobotLoc.getY(),
////					m_CurrWaypoint->getY(), m_Radius);
//
//	retun NULL;
//}
}

