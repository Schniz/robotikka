#pragma once
#include <vector>
#include "../Managers/ConfigurationManager.h"
#include "../Utils/pngUtil.h"
#include <math.h>
#include "Cell.h"
#include "../lib/lodepng.h"

using namespace std;
using namespace Managers;

class Map
{
public:
	unsigned m_Rows;
	unsigned m_Cols;
	Map(const char* filename);
	Map(unsigned Rows,unsigned Cols);
	~Map();

	void PrintMap(const char* filename);

	inline unsigned getCols() {
		return m_Cols;
	};

	inline unsigned getRows() {
		return m_Rows;
	};

	Cell* getCell(int row, int col) const;

protected:

	vector<vector<Cell*> > m_Cells;
	std::vector<unsigned char> FatGrid;
	std::vector<unsigned char> RegGrid;

private:
	void initMap(const char* filename);
	std::vector<unsigned char> CreatGridFromMap(std::vector<unsigned char> PngMap,unsigned MapHeight,unsigned MapWidth, float GridResolutionCm, float PixelPerCm, unsigned &GridCols, unsigned &GridRows);
};
