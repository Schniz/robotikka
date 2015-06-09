#pragma once

#include <string>
#include <player-2.0/libplayerc++/utility.h>

using namespace std;

namespace Consts {

/* CFG FILE */
const string CFG_PATH_TO_PNG = "pngFile";
const string CFG_START_LOCATION_X = "robotLocationX";
const string CFG_START_LOCATION_Y = "robotLocationY";
const string CFG_START_LOCATION_YAW = "robotLocationYaw";
const string CFG_END_LOCATION_X = "endLocationX";
const string CFG_END_LOCATION_Y = "endLocationY";
const string CFG_PPCM_KEY_KEY = "0.1"; //"ppcm";
const string CFG_PNG_GRID_RESOLUTION = "0.5"; //"gridResolution";
const string CFG_ROBOT_SIZE_WIDTH = "robotWidthCM";
const string CFG_ROBOT_SIZE_HEIGHT = "robotHeightCM";

const double MAP_RESOLUTION_CM = 2.5;
const double GRID_RESOLUTION_CM = 10;
const double CFG_ROBOT_SIZE_WIDTH_CM = 30; //"robotWidthCM";
const double CFG_ROBOT_SIZE_HEIGHT_CM = 30; //"robotHeightCM";

/* WAY POINTS */
const float RADIUS_AROUND_POINT = 10.0;

/* LASER */
const unsigned LASER_SLEASER_ARRAY_SIZE = 666;
const double LASER_FOV_DEGREE = 240.0;
const double MIN_LEASER_DISTANCE = 0;
double const MAX_LEASER_DISTANCE = 4.096;

/* PLAYER */
const string PLAYER_HOST = PlayerCc::PLAYER_HOSTNAME;
const int PLAYER_PORT = PlayerCc::PLAYER_PORTNUM;

}
