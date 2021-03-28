#pragma once

#include <deque>
#include <map>
#include <algorithm>

#include "PF_Algorithm.h"
#include "Vector2.h"

class PF_AStar : public PF_Algorithm
{
private:
	std::multimap<float, Vector2> frontier;
	std::map<Vector2, Vector2, Vector2Comparator> cameFrom;
	std::map<Vector2, float, Vector2Comparator> costSoFar;

	Vector2 lastCheckedCurrent;

public:
	PF_AStar();
	PF_AStar(BoolMap* _map, Vector2 _start, Vector2 _finish);

	bool solveStep();
	std::vector<Vector2> solve();

	std::vector<Vector2> getPath();

	Vector2 getCurrent() { return lastCheckedCurrent; };
	std::multimap<float, Vector2>* getFrontier() { return &frontier; }
	std::map<Vector2, Vector2, Vector2Comparator>* getCameFrom() { return &cameFrom; }
	std::map<Vector2, float, Vector2Comparator>* getCostSoFar() { return &costSoFar; }
 };