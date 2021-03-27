#include "PF_BFS.h"

PF_BFS::PF_BFS()
{
	frontier.push_back(Vector2(0, 0));
	cameFrom[Vector2(0, 0)] = Vector2(0, 0);
	lastCheckedCurrent = Vector2(0, 0);

	isFinished = true;
}

PF_BFS::PF_BFS(BoolMap* _map, Vector2 _start, Vector2 _finish)
	: PF_Algorithm(_map, _start, _finish)
{
	frontier.push_back(_start);
	cameFrom[_start] = _start;
	lastCheckedCurrent = _start;

	isFinished = _start == _finish;
}

bool PF_BFS::solveStep()
{
	if (frontier.size() > 0 && !isFinished)
	{
		Vector2 current = frontier.front();
		frontier.pop_front();

		lastCheckedCurrent = current;

		for (Vector2 neighbour : map->findNeighbours(current))
		{
			if (std::find_if(cameFrom.begin(), cameFrom.end(), [neighbour](std::pair<Vector2, Vector2> _element) { return _element.first == neighbour; }) == cameFrom.end())
			{
				frontier.push_back(neighbour);
				cameFrom[neighbour] = current;
			}

			if (neighbour == finish)
			{
				isFinished = true;
				return true;
			}
		}
	}
	else
		return true;
}

std::vector<Vector2> PF_BFS::solve()
{
	while (!solveStep());

	return getPath();
}

std::vector<Vector2> PF_BFS::getPath()
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