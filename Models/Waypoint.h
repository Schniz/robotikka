class Waypoint {
public:
	Waypoint(double x, double y, double yaw) :
			m_X(x), m_Y(y), m_Yaw(yaw) {

	}


	inline double getX() {
		return m_X;
	};

	inline double getY() {
		return m_Y;
	};

	inline double getYaw() {
		return m_Yaw;
	};




private:
	double m_X;
	double m_Y;
	double m_Yaw;
};
