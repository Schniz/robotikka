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
const double MIN_LEASER_DISTANCE = 0; // meters
double const MAX_LEASER_DISTANCE = 4.096; // meters
const double LASER_FRONT_SAMPLES_HALF = 75;
const double OBJECTS_DISTANCE_FROM_LASER_METER = 0.65;
const double LASER_ANGULAR_RESOLUTION = LASER_FOV_DEGREE / LASER_SLEASER_ARRAY_SIZE;
const double START_RIGHT_RAYS_RANGE_ANGLE = -120;
const double END_RIGHT_RAYS_RANGE_ANGLE = -60;
const double START_LEFT_RAYS_RANGE_ANGLE = 60;
const double END_LEFT_RAYS_RANGE_ANGLE = 120;

/* PLAYER */
const string PLAYER_HOST = PlayerCc::PLAYER_HOSTNAME;
const int PLAYER_PORT = PlayerCc::PLAYER_PORTNUM;

/* BEHAVIORS */
const double MOVE_FORWARD_SPEED = 0.5;
const double TURN_SPEED = 0.1;
const double TURN_ANGULAR_SPEED = 0.5;
const double TURN_IN_PLACE_ANGULAR_SPEED = 3.0;
//const double MOVE_BACKWARD_SPEED = -MOVE_FORWARD_SPEED;
const int BEHAVIOR_NUM = 3;

/* PARTICLE */
const double BEL_NOR = 2;
const double MAX_ANGLE_TO_MOVE = 1.0;
const double NORMAL_ANGLE_TO_MOVE =  0.5;
const double SAFE_DISTANCE_TO_MOVE = 0.3;
const double SENSOR_FROM_END = 15;
const double SENSOR_DETECTION_RANGE = 60;
const double CELL_DIM = 5;

const double MAX_ACCURATE_MOVEMENT = 0.5; /*Meter*/
const double MAX_ACCURATE_ANGLE = 1.0; /*Radians*/
const double NIE = 0.02;

const double YAW_RANGE = 0.2; // yaw range for each child particle
const double MAX_PARTICLES_COUNT = 200; // max particles count
const double EXPANSION_RADIUS = 0.3; // expansion radius for each child particle
const double EMERGENCY_EXPANSION_RADIUS = EXPANSION_RADIUS * 2; // emergency expansion radius when no particles exists
const double EMERGENCY_YAW_RANGE = YAW_RANGE * 2; // emergency yaw range when no particles exists
const double PARTICLE_EMERGENCY_BREED = MAX_PARTICLES_COUNT - 2; // Particles emergency breed count when no particles exists
}
