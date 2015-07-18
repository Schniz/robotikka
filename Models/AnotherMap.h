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

using namespace std;

class AnotherMap {
public:
	AnotherMap();
	virtual ~AnotherMap();
	Cell* getCell(unsigned x, unsigned y);
	unsigned int height;
	unsigned int width;
	unsigned int gridWidth;
	unsigned int gridHeight;
	vector<unsigned char> image;
	vector<Cell*> grid;
};

#endif /* ALTERNATIVEMAP_H_ */
