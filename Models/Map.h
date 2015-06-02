#pragma once

#include <vector>

#include "Cell.h"

using namespace std;

class Map
{
public:
	Map(unsigned rows, unsigned cols);
	Map(const Map& map);
	~Map();

	inline unsigned getCols() {
		return m_Cols;
	};

	inline unsigned getRows() {
		return m_Rows;
	};

	Cell* getCell(int row, int col) const;

protected:
	unsigned m_Rows;
	unsigned m_Cols;
	vector<vector<Cell*> > m_Cells;

private:
	void initMap(unsigned rows, unsigned cols);
};
