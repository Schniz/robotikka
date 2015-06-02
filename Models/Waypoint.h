class Waypoint {
public:
	Waypoint(double x, double y, double yaw) :
			m_X(x), m_Y(y), m_Yaw(yaw) {

	}

private:
	double m_X;
	double m_Y;
	double m_Yaw;
};
