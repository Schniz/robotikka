#include "Map.h"

using namespace std;

const unsigned Cell::NUM_NEIGHBORS = 8;

Map::Map(const char* filename) {
	initMap(filename);
}

void Map::initMap(const char* filename)
{
	std::vector<unsigned char> image;
	std::vector<unsigned char> FatImage;
	unsigned width, height;
	unsigned x, y, bX, bY;

	// Get the config
	ConfigurationManager* config = ConfigurationManager::GetInstance();
		//decode
		unsigned error = lodepng::decode(image, width, height, config->getPngMapPath());

		//if there's an error, display it
		if (error)
			std::cout << "decoder error " << error << ": "
					<< lodepng_error_text(error) << std::endl;

		// Calc grid size
		this->m_Cols = ceil(width * config->getPixelPerCm() / config->getPngGridResolution());
		this->m_Rows = ceil(height * config->getPixelPerCm() / config->getPngGridResolution());
		unsigned GridCellSizeInPx = ceil(config->getPngGridResolution() / config->getPixelPerCm());

		// Calc the size of the grid
		FatImage.resize(width * height);
		this->FatGrid.resize(this->m_Rows * this->m_Cols);

		// calc the size of the robot in pic px
		unsigned PxToBlow = ceil(config->getPngGridResolution() / config->getRobotSize().RadiosSize());
		unsigned char color;
		for (y = 0; y < height; y++)
			for (x = 0; x < width; x++) {
				if (image[y * width * 4 + x * 4 + 0]
						|| image[y * width * 4 + x * 4 + 1]
						|| image[y * width * 4 + x * 4 + 2])
					color = 0;

					// add oppstical to the regular grid
					for (bX = std::max(x - PxToBlow,static_cast<unsigned int>(0)); bX < PxToBlow+x; bX++)
						for (bY = std::max(x - PxToBlow,static_cast<unsigned int>(0));bY < PxToBlow+y;bY++)
						{
							FatImage[y * width * 4 + x * 4 + 0] = color;
							FatImage[y * width * 4 + x * 4 + 1] = color;
							FatImage[y * width * 4 + x * 4 + 2] = color;
							FatImage[y * width * 4 + x * 4 + 3] = color;
						}
			}
//	m_Rows = rows;
//	m_Cols = cols;
//
//	//TODO: check if the size is the rows
//	m_Cells.resize(rows);
//
//	// Initialize the cells
//	for (unsigned i = 0; i < rows; i++) {
//		m_Cells[i].resize(cols);
//		for (unsigned j = 0; j < cols; j++) {
//			m_Cells[i][j] = new Cell(j, i);
//		}
//	}
//
//	/* neighbors:
//	 * [0,1,2,
//	 *  3,r,4,
//	 *  5,6,7]*/
//
//	// Initialize the neighbors
//	for (unsigned i = 0; i < rows; i++) {
//		for (unsigned j = 0; j < cols; j++) {
//
//			vector<Cell*> neighbors;
//			neighbors.resize(Cell::NUM_NEIGHBORS);
//
//			// Check top
//			if (i != 0) {
//				if (j != 0) {
//					// Check top left
//					neighbors[0] = m_Cells[i - 1][j - 1];
//				}
//
//				// Check top middle
//				neighbors[1] = m_Cells[i - 1][j];
//
//				if (j < cols - 1) {
//					// Check top right
//					neighbors[2] = m_Cells[i - 1][j + 1];
//				}
//			}
//
//			// Check middle
//			if (j != 0) {
//				// Check middle left
//				neighbors[3] = m_Cells[i][j - 1];
//			}
//
//			if (j < cols - 1) {
//				// Check middle right
//				neighbors[4] = m_Cells[i][j + 1];
//			}
//
//			// Check bottom
//			if (i < rows - 1) {
//				if (j != 0) {
//					// Check bottom left
//					neighbors[5] = m_Cells[i + 1][j - 1];
//				}
//
//				// Check bottom middle
//				neighbors[6] = m_Cells[i + 1][j];
//
//				if (j < cols - 1) {
//					// Check bottom right
//					neighbors[7] = m_Cells[i + 1][j + 1];
//				}
//			}
//
//			m_Cells[i][j]->init(neighbors);
//		}
//	}
}



Map::~Map() {
	// TODO: clear all objects!!!!
}

Cell* Map::getCell(int row, int col) const {
	return m_Cells[row][col];
}

void PrintMap(const char* filename)
{

	}

