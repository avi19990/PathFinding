#include <assert.h>

#include "BoolMap.h"

BoolMap::BoolMap()
{
	map = nullptr;
	width = height = 0;
}

BoolMap::BoolMap(int _width, int _height)
{
	assert(_width > 0);
	assert(_height > 0);

	width = _width;
	height = _height;

	map = new bool[width * height];
	for (int i = 0; i < width * height; ++i)
		map[i] = true;
}

BoolMap::BoolMap(bool* _map, int _width, int _height)
{
	assert(_map != nullptr);
	assert(_width > 0);
	assert(_height > 0);

	map = _map;
	width = _width;
	height = _height;
}

BoolMap::~BoolMap()
{
	delete[] map;
	map = nullptr;
}

std::vector<Vector2> BoolMap::findNeighbours(Vector2 _cell, std::vector<Vector2> _directions)
{
	assert(_directions.size() > 0);
	assert(_cell.x >= 0 && _cell.x < width);
	assert(_cell.y >= 0 && _cell.y < height);

	std::vector<Vector2> neighbours;

	for (Vector2 direction : _directions)
	{
		if (_cell.x + direction.x >= 0 && _cell.x + direction.x < width && _cell.y + direction.y >= 0 && _cell.y + direction.y < height)
			neighbours.push_back(Vector2(_cell.x + direction.x, _cell.y + direction.y));
	}

	return neighbours;
}