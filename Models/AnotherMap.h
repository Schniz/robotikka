/*
 * AlternativeMap.h
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#ifndef ALTERNATIVEMAP_H_
#define ALTERNATIVEMAP_H_
#pragma once

#include <stdio.h>
#include "Cell.h"
#include <string>
#include "../Models/Size.h"

using namespace std;

class AnotherMap {
public:
	AnotherMap(string fileName, float radiusSize, double gridResolution);
	virtual ~AnotherMap();
	Cell* getCell(unsigned x, unsigned y);
	void saveToFile(string fileName);
	unsigned int height;
	unsigned int width;
	unsigned int gridWidth;
	unsigned int gridHeight;
	vector<unsigned char> image;
	vector<Cell*> grid;
};

#endif /* ALTERNATIVEMAP_H_ */
