
#include "Robot.h"
#include <stdexcept>

Robot::Robot(char* ip, int port) {

	_pc = new PlayerClient(ip, port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);

	//For fixing Player's reading BUG
	for (int i = 0; i < 15; i++)
		Read();
}

double Robot::getXPosition() {
	return _pp->GetXPos();
}

double Robot::getYPosition() {
	return _pp->GetYPos();
}

double Robot::getYawPosition() {
	return _pp->GetYaw();
}

double Robot::getRangeLaser(unsigned index) {
	if (index < 0 || index > LASER_SLEASER_ARRAY_SIZE) {
		return -1;
	}
	return _lp->GetRange(index);;
}

double Robot::getRangeLaser(double angle) {
	return getRangeLaser(angleToindex(angle));
}


double Robot::indexToAngle(int index, double fov, int size) {
	double angular_resolution = fov / (double) size;
	double min_angle = fov / 2;

	double angle = index * angular_resolution - min_angle;
	return angle;
}

unsigned Robot::angleToIndex(double angle, double fov, int size) {
	double min_angle = fov / 2;

	int index = ((double) size / fov) * (angle + min_angle);
	if (index >= size) {
		throw new out_of_range("index larger than possible.");
	}

	return index;
}

double Robot::indexToAngle(int index) {
	return Robot::indexToAngle(index, LASER_FOV_DEGREE,
			LASER_SLEASER_ARRAY_SIZE);
}

unsigned Robot::angleToindex(double angle) {
	return Robot::angleToIndex(angle, LASER_FOV_DEGREE,
			LASER_SLEASER_ARRAY_SIZE);
}



double Robot::getDistanceFromObstacle(int index)
{
	return (*_lp)[index];
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
