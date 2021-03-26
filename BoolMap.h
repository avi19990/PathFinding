#pragma once

#include <vector>

#include "Vector2.h"

class BoolMap
{
public:
	bool* map;
	int width, height;

	BoolMap();
	BoolMap(int _width, int _height);
	BoolMap(bool* _map, int _width, int _height);
	~BoolMap();

	std::vector<Vector2> findNeighbours(Vector2 _cell, std::vector<Vector2> _directions = { Vector2(0, -1), Vector2(1, -1), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1), Vector2(-1, 1), Vector2(-1, 0), Vector2(-1, -1) });
};