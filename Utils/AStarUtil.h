#pragma once

#include <vector>
#include "stlastar.h"
#include "./AStar/SearchNode.h"
#include "../Models/Cell.h"

using namespace std;

namespace Utils {
  class AStarUtil {
  public:
	  AStarUtil(Map* map) {
		  this->map = map;
	  }
	  vector<Cell*> findPath(Cell* start, Cell* destination);
  protected:
	  Map* map;
	  AStarSearch<SearchNode> search;
  };
}
