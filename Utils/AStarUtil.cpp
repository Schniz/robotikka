#include "AStarUtil.h"
#include "./AStar/SearchNode.h"
#include <map>

namespace Utils {
  vector<Cell*> AStarUtil::findPath(Cell* start, Cell* destination) {
	  // Set start and destination cells.
	  SearchNode startNode = SearchNode(start->getX(), start->getY());
	  SearchNode destinationNode = SearchNode(destination->getX(), destination->getY());
	  this->search.SetStartAndGoalStates(startNode, destinationNode);

	  // Search until you get to the destination (or you haven't found a path).
	  unsigned int state = this->search.SearchStep(this->map);
	  while (state == AStarSearch<SearchNode>::SEARCH_STATE_SEARCHING) {
		  state = this->search.SearchStep(this->map);
	  }

	  if (state == AStarSearch<SearchNode>::SEARCH_STATE_FAILED) {
		  std::cerr << "Could not find a path. sry for dis.\n";
	  } else if (state == AStarSearch<SearchNode>::SEARCH_STATE_SUCCEEDED) {
		  // Yay.
	  }
  }
}
