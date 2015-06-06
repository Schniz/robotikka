#pragma once

#include <vector>

using namespace std;

class Cell {
public:
	static const int OCCUPIED = 1;
	static const int FREE = 0;
	static const int WALL = 2;
	static const unsigned NUM_NEIGHBORS = 8;

	double Cell_Cost;

	Cell(unsigned x, unsigned y, double cell_cost = 1.0);
	Cell(const Cell& cell);
	Cell(const Cell* cell);

	~Cell();

	void init(vector<Cell*> neighbors);

	inline bool equalsTo(Cell* cell) {
		return (this->getX() == cell->getX() && this->getY() == cell->getY());
	}

	inline vector<Cell*> getNeighbors() {
		return m_Neighbors;
	};

	inline unsigned getX() {
		return m_X;
	};

	inline unsigned getY() {
		return m_Y;
	};

	inline bool getIsInit() {
		return m_IsInit;
	};

	bool isFree();

protected:
	bool m_IsInit;
	vector<Cell*> m_Neighbors;
	unsigned m_X;
	unsigned m_Y;
};
