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

enum class CellType : unsigned char {
	TERRAIN,
	BLOATED_WALL,
	WALL
};

class AnotherMap {
public:
	AnotherMap();
	virtual ~AnotherMap();
	unsigned int height;
	unsigned int width;
	vector<unsigned char> image;
	vector<Cell*> grid;
};

#endif /* ALTERNATIVEMAP_H_ */
