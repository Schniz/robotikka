#include "RobotManager.h"

//#include <libplayerc++/playerc++.h>
//#include "../Consts.h"
//#include "../behaviors/MoveForward.h"
//#include "../behaviors/TurnInPlace.h"
//#include "../behaviors/TurnLeft.h"
//#include "../behaviors/TurnRight.h"
//#include "../behaviors/MoveBackward.h"
//#include "WaypointsManager.h"


using namespace std;
using namespace PlayerCc;
//using namespace Utils;

namespace Managers {

RobotManager::RobotManager(PlayerClient* player) {
//m_Robot = new Robot(player);

	initBehaviors();
	m_CurrBehavior = NULL;
	m_LocalizationManager = NULL;
	m_WaypointsManager = NULL;
}

RobotManager::RobotManager(const string hostname, uint port) {
//	m_Robot = new Robot(hostname, port);

	initBehaviors();
	m_CurrBehavior = NULL;
	m_LocalizationManager = NULL;
	m_WaypointsManager = NULL;
}

RobotManager::~RobotManager() {
	while (!m_Behaviors.empty()) {
		delete m_Behaviors.back();
		m_Behaviors.pop_back();
	}

	delete m_CurrBehavior;
	m_CurrBehavior = NULL;

	delete m_LocalizationManager;
	m_LocalizationManager = NULL;

	delete m_WaypointsManager;
	m_WaypointsManager = NULL;

	delete m_Robot;
	m_Robot = NULL;
}

void RobotManager::setLocalizationManager(
		LocalizationManager* localizationManager) {
	m_LocalizationManager = localizationManager;
}

void RobotManager::setWaypoints(vector<Location> landmarks) {
	vector<Waypoint> waypoints;

//	for (Location loc : landmarks) {
//		waypoints.push_back(Waypoint(loc.m_Y, loc.m_Y, loc.m_Yaw));
//	}

	m_WaypointsManager = new WaypointsManager(m_Robot, waypoints,
			RADIUS_AROUND_POINT);
}

void RobotManager::run() {
	// TODO check if really needed - prettier solution?
	//For fixing Player's reading BUG
	for (int i = 0; i < 15; i++) {
//		m_Robot->_pc->Read();
	}

	try {
		while (true) {
	//		m_Robot->_pc->Read();

			updateLocation();
			runStep();
		}
	} catch (const PlayerError & e) {
		// TODO
	}
}

void RobotManager::initBehaviors() {
	m_Behaviors.push_back(new TurnInPlace(m_Robot));
	m_Behaviors.push_back(new MoveForward(m_Robot));
	m_Behaviors.push_back(new TurnRight(m_Robot));
	m_Behaviors.push_back(new TurnLeft(m_Robot));
	m_Behaviors.push_back(new MoveBackward(m_Robot));
}

void RobotManager::updateLocation() {
//	Location newLocation = { m_Robot->getXPosition(), m_Robot->getYPosition(),
//			m_Robot->getYawPosition() };
	//m_LocalizationManager->update(newLocation, m_Robot->_lp);
	//m_RealLocation = m_LocalizationManager->getEstimatedRealLocation();
}

void RobotManager::runStep() {

//	if (!m_CurrBehavior || m_CurrBehavior->stopCond()()) {
//		for (uint i = 0; i < m_Behaviors.size(); i++) {
//
//			if (m_Behaviors[i]->startCond() {
//						m_CurrBehavior = m_Behaviors[i];
//						break;
//					}
//				}
//			}
//
//			m_CurrBehavior->execute();
//		}
	}
}
