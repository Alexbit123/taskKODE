#pragma once

#include <string>

struct Coordinate {
	double x, y;
};

struct Object {
	std::string name;
	Coordinate coord;
	std::string type_object;
	time_t time;
};
