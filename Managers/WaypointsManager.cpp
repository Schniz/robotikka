#include "WaypointsManager.h"

namespace Managers {

	WaypointsManager::WaypointsManager(Robot* robot, float radius) :
			m_Robot(robot), c_Radius(radius) {
		m_CurrWaypoint = NULL;
	}


	void WaypointsManager::update() {
		if (shouldMoveNext()) {
			m_CurrWaypoint = m_WaypointsQueue.front();
			m_WaypointsQueue.pop();
		}

		// TODO Calculate where the robot is currently,
		// and what speed and yawSpeed it needs to get to the next Waypoint.
		// TODO Use the RobotManager to move it?
	}

	bool WaypointsManager::shouldMoveNext() {
		return false;
		//TODO DO IT HAHAH
	}

	WaypointsManager::~WaypointsManager() {
		delete m_CurrWaypoint;
		m_CurrWaypoint = NULL;

		while (!m_WaypointsQueue.empty()) {
			delete m_WaypointsQueue.front();
			m_WaypointsQueue.pop();
		}

		delete m_Robot;
		m_Robot = NULL;
	}
}
