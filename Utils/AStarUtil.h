#pragma once

#include <vector>
#include "stlastar.h"
#include "./AStar/SearchNode.h"
#include "../Models/Cell.h"

using namespace std;

namespace Utils {
  class AStarUtil {
  public:
	  AStarUtil(Map* map) : map(map), search(NULL) {
		  cout << "AStarUtil.h: Creating a map." << endl;
	  }
	  vector<Cell*> findPath(Cell* start, Cell* destination);
  protected:
	  Map* map;
	  AStarSearch<SearchNode> search;
	  vector<Cell*> buildPath();
  };
}
