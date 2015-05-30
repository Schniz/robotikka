#include "ConfigurationManager.h"
#include <iostream>
#include <string>
#include "../lib/config.h"
#include "../Consts.h"
using namespace std;

namespace Managers {
ConfigurationManager::ConfigurationManager(string filePath) {
		Config configParser = Config(filePath);

		m_PngMapPath = configParser.pString(CFG_PATH_TO_PNG);
		m_StartLocation.m_X = configParser.pDouble(CFG_START_LOCATION_X);
		m_StartLocation.m_Y = configParser.pDouble(CFG_START_LOCATION_Y);
		m_StartLocation.m_Yaw = configParser.pDouble(CFG_START_LOCATION_YAW);
		m_EndLocation.m_X = configParser.pDouble(CFG_END_LOCATION_X);
		m_EndLocation.m_Y = configParser.pDouble(CFG_END_LOCATION_Y);
		m_PpCM = configParser.pDouble(CFG_PPCM_KEY_KEY);
		m_PngGridResolution = configParser.pDouble(CFG_PNG_GRID_RESOLUTION);
		m_RobotSize.m_Width = configParser.pDouble(CFG_ROBOT_SIZE_WIDTH);
		m_RobotSize.m_Height = configParser.pDouble(CFG_ROBOT_SIZE_HEIGHT);
	}

ConfigurationManager::~ConfigurationManager() {
	}

	string ConfigurationManager::getPngMapPath() {
		return m_PngMapPath;
	}

	Location ConfigurationManager::getStartLocation() {
		return m_StartLocation;
	}

	Location ConfigurationManager::getEndLocation() {
		return m_EndLocation;
	}

	float ConfigurationManager::getPixelPerCm() {
		return m_PpCM;
	}

	float ConfigurationManager::getPngGridResolution() {
		return m_PngGridResolution;
	}

	Size ConfigurationManager::getRobotSize() {
		return m_RobotSize;
	}

	ostream& operator<<(ostream& os, ConfigurationManager* config) {
		os << "PngMapPath: " << config->m_PngMapPath << endl;
		os << "Start Location: [" << config->m_StartLocation.m_X << ", " << config->m_StartLocation.m_Y << ", " << config->m_StartLocation.m_Yaw << "]" << endl;
		os << "End Location : [" << config->m_EndLocation.m_X << "," << config->m_EndLocation.m_Y << "]" << endl;
		os << "PixelPerCM: " << config->m_PpCM << endl;
		os << "Png Grid Resolution: " << config->m_PngGridResolution << endl;
		os << "Robot Size: [" << config->m_RobotSize.m_Width << ", " << config->m_RobotSize.m_Height << "]";
		return os;
	}

}
