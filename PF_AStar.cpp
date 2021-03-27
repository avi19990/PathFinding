#include "PF_AStar.h"

PF_AStar::PF_AStar()
{
	frontier.push_back(Vector2(0, 0));
	cameFrom[Vector2(0, 0)] = Vector2(0, 0);
	costSoFar[Vector2(0, 0)] = 0;
	lastCheckedCurrent = Vector2(0, 0);

	isFinished = true;
}

PF_AStar::PF_AStar(BoolMap* _map, Vector2 _start, Vector2 _finish)
	: PF_Algorithm(_map, _start, _finish)
{
	frontier.push_back(_start);
	cameFrom[_start] = _start;
	costSoFar[_start] = 0;
	lastCheckedCurrent = _start;

	isFinished = _start == _finish;
}

bool PF_AStar::solveStep()
{
	if (frontier.size() > 0 && !isFinished)
	{
		Vector2 current = frontier.front();
		frontier.pop_front();

		lastCheckedCurrent = current;

		if (current == finish)
		{
			isFinished = true;
			return true;
		}

		for (Vector2 neighbour : map->findNeighbours(current))
		{
			float newCost = costSoFar[current] + 1;

			if (std::find_if(cameFrom.begin(), cameFrom.end(), [neighbour](std::pair<Vector2, Vector2> _element) { return _element.first == neighbour; }) == cameFrom.end() || newCost < costSoFar[neighbour])
			{
				costSoFar[neighbour] = newCost;
				frontier.push_back(neighbour);
				std::sort(frontier.begin(), frontier.end(), [this](Vector2 _first, Vector2 _second) { return (Vector2::distance(_first, finish) + costSoFar[_first]) < (Vector2::distance(_second, finish) + costSoFar[_second]); });
				cameFrom[neighbour] = current;
			}
		}

		return false;
	}
	else
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
