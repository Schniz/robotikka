#pragma once

#include "../Models/AnotherMap.h";
#include <vector>
#include "stlastar.h"
#include "./AStar/SearchNode.h"
#include "../Models/Cell.h"

using namespace std;

namespace Utils {
  class AStarUtil {
  public:
	  AStarUtil(AnotherMap* map) : map(map), search(NULL) {
		  cout << "AStarUtil.h: Creating a map." << endl;
	  }
	  vector<Cell*> findPath(Cell* start, Cell* destination);
  protected:
	  AnotherMap* map;
	  AStarSearch<SearchNode> search;
	  vector<Cell*> buildPath();
  };
}
