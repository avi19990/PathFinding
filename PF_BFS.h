#pragma once

#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <utility>
#include <string>

#include "PF_Algorithm.h"
#include "Vector2.h"

class PF_BFS : public PF_Algorithm
{
private:
	std::deque<Vector2> frontier;
	std::map<Vector2, Vector2, Vector2Comparator> cameFrom;

	Vector2 lastCheckedCurrent;

public:
	PF_BFS();
	PF_BFS(BoolMap* _map, Vector2 _start, Vector2 _finish);

	bool solveStep();
	std::vector<Vector2> solve();

	Vector2 getCurrent() { return lastCheckedCurrent; };
	std::vector<Vector2> getPath();
	std::deque<Vector2>* getFrontier() { return &frontier; }
	std::map<Vector2, Vector2, Vector2Comparator>* getCameFrom() { return &cameFrom; }
};