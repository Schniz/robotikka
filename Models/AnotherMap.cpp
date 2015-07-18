/*
 * AlternativeMap.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "AnotherMap.h"
#include "Cell.h"
#include <stdio.h>
#include "../lib/lodepng.h"
#include "../Managers/ConfigurationManager.h"

using namespace std;

void saveFile(AnotherMap* map, string fileName) {
	int gridSquare = map->gridHeight * map->gridWidth;
	unsigned char* image = new unsigned char[gridSquare * 4];
	for (int i = 0; i < gridSquare; i++) {
		CellType type = map->grid[i]->Cell_Cost;
		char color =
				type == CellType::TERRAIN ?
						(255) : (type == CellType::BLOATED_WALL ? (128) : (0));
		image[i * 4] = color;
		image[i * 4 + 1] = color;
		image[i * 4 + 2] = color;
		image[i * 4 + 3] = 255;
	}
	lodepng::encode(fileName, image, map->gridWidth, map->gridHeight);
	delete image;
}

void loadFile(AnotherMap* map, string fileName) {
	cout << "Loading file '" << fileName << "'..." << endl;
	unsigned error = lodepng::decode(map->image, map->width, map->height,
			fileName);
	cout << "error:" << error << ", size: " << map->width << "x" << map->height
			<< endl;
}

void bloatMap(AnotherMap* map, unsigned pxToBloat) {
	unsigned newWidth = map->gridWidth = map->width; //map->gridWidth = pxToBloat * map->width;
	unsigned newHeight = map->gridHeight = map->height; //map->gridHeight = pxToBloat * map->height;
	map->grid = vector<Cell*>(map->width * map->height);
	int i = 0;
	for (unsigned y = 0; y < newHeight; ++y) {
		for (unsigned x = 0; x < newWidth; ++x) {
			bool isWall = map->image[(y * map->width + x) * 4] == 0;
			map->grid[y * newWidth + x] = new Cell(x, y,
					isWall ? CellType::WALL : CellType::TERRAIN);
			i++;
		}
	}

	for (unsigned y = 0; y < newHeight; ++y) {
		for (unsigned x = 0; x < newWidth; ++x) {
			if (map->getCell(x,y)->Cell_Cost != CellType::WALL) {
				continue;
			}
			for (unsigned bloatY = 0; bloatY <= pxToBloat; ++bloatY) {
				for (unsigned bloatX = 0; bloatX <= pxToBloat; ++bloatX) {
					Cell* cell = map->getCell(
						x + bloatX - pxToBloat / 2,
						y + bloatY - pxToBloat / 2
					);
					if (cell != NULL && cell->Cell_Cost != CellType::WALL) {
						cell->Cell_Cost = CellType::BLOATED_WALL;
					}
				}
			}
		}
	}

	// Reduce the footprint.
	map->image.resize(1);
}

unsigned howMuchPxToBloat(float robotRadiusSize, float pngGridResolution) {
	return robotRadiusSize / pngGridResolution;
}

AnotherMap::AnotherMap() {
	Managers::ConfigurationManager* config =
			Managers::ConfigurationManager::GetInstance();
	this->width = 1;
	this->height = 1;
	this->gridWidth = 1;
	this->gridHeight = 1;

	loadFile(this, config->getPngMapPath());
	bloatMap(this,
			howMuchPxToBloat(config->getRobotSize().RadiosSize(),
					config->getPngGridResolution()));
	saveFile(this, "/tmp/holyfuck.png");

	cout << "NOT DEAD! YAY" << endl;
}

Cell* AnotherMap::getCell(unsigned x, unsigned y) {
	if (x < 0 || y < 0 || x >= this->gridWidth || y >= this->gridHeight) {
		return NULL;
	}
	return this->grid[y * this->gridWidth + x];
}

AnotherMap::~AnotherMap() {
	// TODO Auto-generated destructor stub
	for (Cell* cell : this->grid) {
		delete cell;
	}
}

