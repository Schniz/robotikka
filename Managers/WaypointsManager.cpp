#include "WaypointsManager.h"

namespace Managers {

WaypointsManager::WaypointsManager(Robot* robot, vector<Waypoint> waypoints,
		float radius) :
		m_Radius(radius), m_Robot(robot) {

	for (int i = 0; i < waypoints.size(); i++) {
		m_WaypointsQueue.push(waypoints[i]);
	}

	m_CurrWaypoint = NULL;
}

WaypointsManager::~WaypointsManager() {
	delete m_CurrWaypoint;
	m_CurrWaypoint = NULL;

	delete m_Robot;
	m_Robot = NULL;
}

Waypoint WaypointsManager::update(Location newRobotLoc) {
	if (m_CurrWaypoint == NULL || shouldMoveNext(newRobotLoc)) {
		m_CurrWaypoint = &m_WaypointsQueue.front();
		m_WaypointsQueue.pop();
	}

	return *m_CurrWaypoint;

	// TODO Calculate where the robot is currently, and what speed and yawSpeed it needs to get to the next Waypoint.
	// TODO Use the RobotManager to move it?
}

bool WaypointsManager::shouldMoveNext(Location newRobotLoc) {
	return MathUtil::equals(newRobotLoc.getX(), m_CurrWaypoint->getX(),
			m_Radius)
			&& MathUtil::equals(newRobotLoc.getY(),
					m_CurrWaypoint->getY(), m_Radius);
}
}

