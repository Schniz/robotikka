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

char* colorFor(CellType type) {
	char r,g,b;
	switch (type) {
		case(CellType::TERRAIN):
			r = g = b = 255;
			break;
		case(CellType::WALL):
			r = g = b = 0;
			break;
		case(CellType::BLOATED_WALL):
			r = g = b = 100;
			break;
		case(CellType::PATH):
			r = 0;
			g = 140;
			b = 40;
			break;
		case (CellType::START):
			r = 0;
			g = 40;
			b = 140;
			break;
		case (CellType::DESTINATION):
			r = 140;
			g = 40;
			b = 0;
			break;
	}
	char* c = new char[3];
	c[0] = r;
	c[1] = g;
	c[2] = b;
	return c;
}

void saveFile(AnotherMap* map, string fileName) {
	int gridSquare = map->gridHeight * map->gridWidth;
	unsigned char* image = new unsigned char[gridSquare * 4];
	for (int i = 0; i < gridSquare; i++) {
		CellType type = map->grid[i]->Cell_Cost;
		char* rgb = colorFor(type);
		image[i * 4] = rgb[0];
		image[i * 4 + 1] = rgb[1];
		image[i * 4 + 2] = rgb[2];
		image[i * 4 + 3] = 255;
		delete[] rgb;
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
	return robotRadiusSize / pngGridResolution * 2;
}

AnotherMap::AnotherMap(string fileName, float radiusSize, double gridResolution) {
	this->width = 1;
	this->height = 1;
	this->gridWidth = 1;
	this->gridHeight = 1;

	loadFile(this, fileName);
	bloatMap(
		this,
		howMuchPxToBloat(radiusSize, gridResolution)
	);
	saveFile(this, "/tmp/holyfuck.png");

	cout << "NOT DEAD! YAY" << endl;
}

Cell* AnotherMap::getCell(unsigned x, unsigned y) {
	if (x < 0 || y < 0 || x >= this->gridWidth || y >= this->gridHeight) {
		return NULL;
	}
	return this->grid[y * this->gridWidth + x];
}

void AnotherMap::saveToFile(string fileName) {
	return saveFile(this, fileName);
}

AnotherMap::~AnotherMap() {
	// TODO Auto-generated destructor stub
	for (Cell* cell : this->grid) {
		delete cell;
	}
}

