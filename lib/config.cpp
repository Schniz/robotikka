#include "config.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct Decleration {
	string name;
	string value;
};

#include <tr1/regex>
#include <regex.h>
#include "log.h"

vector<Decleration> readLines(string fileName) {
	vector<Decleration> lines;
	ifstream fileStream(fileName.c_str());
	if (!fileStream) {
		cout << "WAT";
		return lines;
	}
	string line;
	while (getline(fileStream, line)) {
		Decleration lineDec;
		int colon = line.find(':');
		lineDec.name = line.substr(0, colon);
		lineDec.value = line.substr(colon + 2, line.length() - colon - 3);
		lines.push_back(lineDec);
	}
	return lines;
}

void Config::parse(string fileName) {
	vector<Decleration> decs = readLines(fileName);

	// OMFG its ugly
	for (Decleration dec : decs) {
		if (!dec.name.compare("goal")) {
			int space = dec.value.find(' ');
			unsigned x = atoi(dec.value.substr(0, space).c_str());
			unsigned y = atoi(dec.value.substr(space+1).c_str());
			this->goal[0] = x;
			this->goal[1] = y;
		} else if (!dec.name.compare("map")) {
			this->mapLocation = dec.value;
		} else if (!dec.name.compare("startLocation")) {
			int firstSpace = dec.value.find(' ');
			int secondSpace = dec.value.substr(firstSpace+1).find(' ') + firstSpace + 1;
			unsigned x = atoi(dec.value.substr(0, firstSpace).c_str());
			unsigned y = atoi(dec.value.substr(firstSpace+1, secondSpace).c_str());
			unsigned yaw = atoi(dec.value.substr(secondSpace+1).c_str());
			this->startLocation[0] = x;
			this->startLocation[1] = y;
			this->startLocation[2] = yaw;
		} else if (!dec.name.compare("robotSize")) {
			int space = dec.value.find(' ');
			unsigned width = atoi(dec.value.substr(0, space).c_str());
			unsigned height = atoi(dec.value.substr(space+1).c_str());
			this->robotSize[0] = width;
			this->robotSize[1] = height;
		} else if (!dec.name.compare("MapResolutionCM")) {
			this->mapResolutionCm = atof(dec.value.c_str());
		} else if (!dec.name.compare("GridResolutionCM")) {
			this->gridResolutionCm = atof(dec.value.c_str());
		}
	}

	// Debug it
	cout << "map location: " << this->mapLocation << endl
		 << "start location: " << this->startLocation[0] << " "
		 	 	 	 	 	  << this->startLocation[1] << " "
		 	 	 	 	 	  << this->startLocation[2] << endl
		 << "goal: " << this->goal[0] << " " << this->goal[1] << endl
		 << "robot size: " << this->robotSize[0] << " " << this->robotSize[1] << endl
		 << "map res: " << this->mapResolutionCm << endl
		 << "grid res: " << this->gridResolutionCm << endl
		 ;
}

Config::Config(string fileName) {
	this->mapLocation = string("");
	this->startLocation = new int[3];
	this->goal = new int[2];
	this->robotSize = new int[2];
	this->mapResolutionCm = 1.0;
	this->gridResolutionCm = 1.0;
	this->parse(fileName);
}

Config::~Config() {
	delete[] this->goal;
	delete[] this->startLocation;
	delete[] this->robotSize;
}
