/*
 * AlternativeMap.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "AnotherMap.h"
#include <stdio.h>
#include "../lib/lodepng.h"
#include "../Managers/ConfigurationManager.h"

using namespace std;

void loadFile(AnotherMap* map, string fileName) {
	unsigned error = lodepng::decode(map->image, map->width, map->height, fileName);
	cout << "error:" << error << ", size: " << map->width << "x" << map->height << endl;
}

void bloatMap(AnotherMap* map, unsigned pxToBloat) {
	unsigned newWidth = pxToBloat * map->width;
	unsigned newHeight = pxToBloat * map->height;
	vector<CellType> grid = vector<CellType>(newWidth * newHeight);
	int i = 0;
	for (unsigned y = 0; y < newHeight; ++y) {
		for (unsigned x = 0; x < newWidth; ++x) {
			grid[x * y] = CellType::TERRAIN;
			i++;
		}
	}
	cout << "initialized " << i << " cells with free terrain." << endl;

	int terrain = 0;
	int bloatedTerrain = 0;
	for (unsigned yIndex = 0; yIndex < map->height; ++yIndex) {
		for (unsigned xIndex = 0; xIndex < map->width; ++xIndex) {
			bool isTerrain = map->image[yIndex * xIndex * 4] == 0;
			if (isTerrain) {
				for (unsigned bloatIndex = 0; bloatIndex < pxToBloat; ++bloatIndex) {
					unsigned cellIndex = yIndex * xIndex + bloatIndex - (pxToBloat / 2);
					if (cellIndex < 0) continue;
					grid[cellIndex] = CellType::BLOATED_WALL;
					bloatedTerrain++;
				}
				bloatedTerrain--;
				terrain++;
				grid[yIndex * xIndex] = CellType::WALL;
			}
		}
	}

	cout << terrain 	   << " of them are actually walls and "
		 << bloatedTerrain << " are walls because of the bloat."
		 << endl;

	// Reduce the footprint.
	map->image.resize(1);
}

unsigned howMuchPxToBloat(float robotRadiusSize, float pngGridResolution) {
	return robotRadiusSize / pngGridResolution;
}

AnotherMap::AnotherMap() {
	Managers::ConfigurationManager* config = Managers::ConfigurationManager::GetInstance();
	this->width = 1;
	this->height = 1;

	loadFile(this, config->getPngMapPath());
	bloatMap(
		this,
		howMuchPxToBloat(
			config->getRobotSize().RadiosSize(),
			config->getPngGridResolution()
		)
	);

	cout << "NOT DEAD! YAY" << endl;
}

AnotherMap::~AnotherMap() {
	// TODO Auto-generated destructor stub
}

