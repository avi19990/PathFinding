#pragma once

#include <math.h>

class Vector2
{
public:
	int x, y;

	Vector2()
	{
		x = y = 0;
	}

	Vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	static double distance(Vector2 _first, Vector2 _second)
	{
		return sqrt(abs(_first.x - _second.x) * abs(_first.x - _second.x) + abs(_first.y - _second.y) * abs(_first.y - _second.y));
	}

	static int manhattanDistance(Vector2 _first, Vector2 _second)
	{
		return abs(_first.x - _second.x) + abs(_first.y - _second.y);
	}

	bool operator==(const Vector2& _second) const
	{
		return x == _second.x && y == _second.y;
	}

	bool operator!=(const Vector2& _second) const
	{
		return x != _second.x || y != _second.y;
	}
};

struct Vector2Comparator
{
	bool operator()(const Vector2& _first, const Vector2& _second) const
	{
		if (_first.y < _second.y)
			return true;
		else
			if (_first.y == _second.y)
				if (_first.x < _second.x)
					return true;

		return false;
	}
};