#include <queue>

#include "../Models/Waypoint.h"
#include "../Models/Cell.h"
#include "../Robot.h"
#include "../Consts.h"

using namespace std;
using namespace Consts;

namespace Managers {

	class WaypointsManager {
		public:
			WaypointsManager(Robot* robot, float radius = RADIUS_AROUND_POINT);
			virtual ~WaypointsManager();

			void update();

		protected:
			bool shouldMoveNext();

		private:
			const double c_Radius;
			Robot* m_Robot;
			queue<Waypoint*> m_WaypointsQueue;
			Waypoint* m_CurrWaypoint;
	};

}
