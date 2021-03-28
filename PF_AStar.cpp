#include "PF_AStar.h"

PF_AStar::PF_AStar()
{
	frontier.insert(std::pair<float, Vector2>(0, Vector2(0, 0)));
	cameFrom[Vector2(0, 0)] = Vector2(0, 0);
	costSoFar[Vector2(0, 0)] = 0;
	lastCheckedCurrent = Vector2(0, 0);

	isFinished = true;
}

PF_AStar::PF_AStar(BoolMap* _map, Vector2 _start, Vector2 _finish)
	: PF_Algorithm(_map, _start, _finish)
{
	frontier.insert(std::pair<float, Vector2>(0, _start));
	cameFrom[_start] = _start;
	costSoFar[_start] = 0;
	lastCheckedCurrent = _start;

	isFinished = _start == _finish;
}

bool PF_AStar::solveStep()
{
	if (frontier.size() > 0 && !isFinished)
	{
		Vector2 current = frontier.begin()->second;
		frontier.erase(frontier.begin());

		lastCheckedCurrent = current;

		if (current == finish)
		{
			isFinished = true;
			return true;
		}

		for (Vector2 neighbour : map->findNeighbours(current))
		{
			float newCost = costSoFar[current] + 1;

			if (newCost < costSoFar[neighbour] || std::find_if(cameFrom.begin(), cameFrom.end(), [neighbour](std::pair<Vector2, Vector2> _element) { return _element.first == neighbour; }) == cameFrom.end())
			{
				frontier.insert(std::pair<float, Vector2>(newCost + Vector2::distance(neighbour, finish), neighbour));

				costSoFar[neighbour] = newCost;
				cameFrom[neighbour] = current;
			}
		}

		return false;
	}
	
	return true;
}

std::vector<Vector2> PF_AStar::solve()
{
	while (!solveStep());

	return getPath();
}

std::vector<Vector2> PF_AStar::getPath()
{
	if (isFinished)
	{
		std::vector<Vector2> path;

		Vector2 cell = finish;
		while ((cell = cameFrom[cell]) != start)
			path.push_back(cell);

		std::reverse(path.begin(), path.end());

		return path;
	}

	return std::vector<Vector2>();
}
