#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
public:
	double m_X;
	double m_Y;
	double m_Yaw;
	Location();
	Location(double x, double y, double Yaw);
	virtual ~Location();
};

#endif /* LOCATION_H_ */
