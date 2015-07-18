#pragma once

#include "../Models/Waypoint.h"
#include "../Models/Cell.h"
#include "../Robot.h"
#include "../Consts.h"
#include "../Utils/MathUtil.h"

using namespace std;
using namespace Consts;
using namespace Utils;

namespace Managers {

	class WaypointsManager {
		public:
		// TODO: init radius
			WaypointsManager(vector<Waypoint> waypoints, float radius = RADIUS_AROUND_POINT);
			virtual ~WaypointsManager();

			bool WaypointDriver(Waypoint wp, Robot rob);
			bool IsInWaypoint(double xp, double yp);

		protected:
			void SmoothWaypoints();

		private:
			const double radius;
			vector<Waypoint> waypointsVec;
			Waypoint* currWaypoint;
			vector<Waypoint> smoothWaypoints;
			int smoothSize;

};
}
