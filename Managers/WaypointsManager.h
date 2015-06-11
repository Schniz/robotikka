#include <queue>

#include "../Models/Waypoint.h"
#include "../Models/Cell.h"
#include "../Robot.h"
#include "../Consts.h"
#include "../Models/Location.h"

using namespace std;
using namespace Consts;
using namespace Utils;

namespace Managers {

	class WaypointsManager {
		public:
		// TODO: init radius
			WaypointsManager(Robot* robot, vector<Waypoint> waypoints, float radius = RADIUS_AROUND_POINT);
			virtual ~WaypointsManager();

			Waypoint update(Location newRobotLoc);

		protected:
			bool shouldMoveNext(Location newRobotLoc);

		private:
			const double m_Radius;
			Robot* m_Robot;
			queue<Waypoint> m_WaypointsQueue;
			Waypoint* m_CurrWaypoint;
	};

}
