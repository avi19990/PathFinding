#pragma once

#include <vector>
#include <assert.h>
#include <string>

#include "BoolMap.h"
#include "Vector2.h"

class PF_Algorithm
{
protected:
	BoolMap* map;
	Vector2 start, finish;

	bool isFinished;

public:
	PF_Algorithm()
	{
		map = nullptr;

		start = finish = Vector2(0, 0);
		isFinished = false;
	}

	PF_Algorithm(BoolMap* _map, Vector2 _start, Vector2 _finish)
	{
		assert(_map);
		assert(_start.x >= 0 && _start.x < _map->width);
		assert(_start.y >= 0 && _start.y < _map->height);
		assert(_finish.x >= 0 && _finish.x < _map->width);
		assert(_finish.y >= 0 && _finish.y < _map->height);

		map = _map;
		start = _start;
		finish = _finish;
		isFinished = false;
	}

	BoolMap* getMap() { return map; }
	Vector2 getStart() { return start; }
	Vector2 getFinish() { return finish; }
	bool getIsFinished() { return isFinished; }

	virtual bool solveStep() = 0;
	virtual std::vector<Vector2> solve() = 0;
	virtual std::vector<Vector2> getPath() = 0;
};