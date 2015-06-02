#include <vector>
#include "../Models/Cell.h"

using namespace std;

namespace Utils {
  class AStarUtil {
  public:
	  static vector<Cell*> findPath(Cell* start, Cell* destination);
  };
}
