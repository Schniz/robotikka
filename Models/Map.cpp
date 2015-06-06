#include "Map.h"
#include <float.h>

using namespace std;

Map::Map(unsigned rows, unsigned cols) {
	initMap(rows, cols);
}

void Map::initMap(unsigned rows, unsigned cols) {

	m_Rows = rows;
	m_Cols = cols;

	//TODO: check if the size is the rows
	m_Cells.resize(rows);

	// Initialize the cells
	for (unsigned i = 0; i < rows; i++) {
		m_Cells[i].resize(cols);
		for (unsigned j = 0; j < cols; j++) {
			m_Cells[i][j] = new Cell(j, i);
		}
	}

	/* neighbors:
	 * [0,1,2,
	 *  3,r,4,
	 *  5,6,7]*/

	// Initialize the neighbors
	for (unsigned i = 0; i < rows; i++) {
		for (unsigned j = 0; j < cols; j++) {

			vector<Cell*> neighbors;
			neighbors.resize(Cell::NUM_NEIGHBORS);

			// Check top
			if (i != 0) {
				if (j != 0) {
					// Check top left
					neighbors[0] = m_Cells[i - 1][j - 1];
				}

				// Check top middle
				neighbors[1] = m_Cells[i - 1][j];

				if (j < cols - 1) {
					// Check top right
					neighbors[2] = m_Cells[i - 1][j + 1];
				}
			}

			// Check middle
			if (j != 0) {
				// Check middle left
				neighbors[3] = m_Cells[i][j - 1];
			}

			if (j < cols - 1) {
				// Check middle right
				neighbors[4] = m_Cells[i][j + 1];
			}

			// Check bottom
			if (i < rows - 1) {
				if (j != 0) {
					// Check bottom left
					neighbors[5] = m_Cells[i + 1][j - 1];
				}

				// Check bottom middle
				neighbors[6] = m_Cells[i + 1][j];

				if (j < cols - 1) {
					// Check bottom right
					neighbors[7] = m_Cells[i + 1][j + 1];
				}
			}

			m_Cells[i][j]->init(neighbors);
		}
	}
}

Map::Map(const Map& map) :
		m_Rows(map.m_Rows), m_Cols(map.m_Cols) {
	initMap(map.m_Rows, map.m_Cols);

	for (unsigned row = 0; row < map.m_Rows; row++) {
		for (unsigned col = 0; col < map.m_Cols; col++) {
			m_Cells[row][col] = new Cell(getCell(row, col));
		}
	}
}

Map::~Map() {
	// TODO: clear all objects!!!!
}

Cell* Map::getCell(int row, int col) const {
	return m_Cells[row][col];
}

