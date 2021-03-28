#include "PF_AStar_Visualizer.h"

PF_AStar_Visualizer::PF_AStar_Visualizer()
{
	AStarAlgorithm = nullptr;
	map = nullptr;
}

PF_AStar_Visualizer::PF_AStar_Visualizer(PF_Algorithm* _algorithm, sf::IntRect _position, std::map<std::string, sf::Color> _colorPalette)
	: PF_Visualizer(_algorithm)
{
	assert(_algorithm);

	AStarAlgorithm = dynamic_cast<PF_AStar*>(_algorithm);
	map = AStarAlgorithm->getMap();

	colorPalette = _colorPalette;
	if (colorPalette.find("frontier") == colorPalette.end()) colorPalette["frontier"] = sf::Color(0, 0, 0);
	if (colorPalette.find("cameFrom") == colorPalette.end()) colorPalette["cameFrom"] = sf::Color(0, 0, 0);
	if (colorPalette.find("start") == colorPalette.end()) colorPalette["start"] = sf::Color(0, 0, 0);
	if (colorPalette.find("finish") == colorPalette.end()) colorPalette["finish"] = sf::Color(0, 0, 0);
	if (colorPalette.find("current") == colorPalette.end()) colorPalette["current"] = sf::Color(0, 0, 0);
	if (colorPalette.find("wall") == colorPalette.end()) colorPalette["wall"] = sf::Color(0, 0, 0);
	if (colorPalette.find("free") == colorPalette.end()) colorPalette["free"] = sf::Color(0, 0, 0);
	if (colorPalette.find("path") == colorPalette.end()) colorPalette["path"] = sf::Color(0, 0, 0);

	position = _position;

	generateMesh();
	colorMap();
	update();
}

void PF_AStar_Visualizer::generateMesh()
{
	mapMesh.setPrimitiveType(sf::PrimitiveType::Triangles);
	mapMesh.resize(map->width * map->height * 6);

	sf::Vector2f cellSize((float)position.width / (float)map->width, (float)position.height / (float)map->height);

	for (int y = 0; y < map->height; ++y)
		for (int x = 0; x < map->width; ++x)
		{
			int leftTopIndex = (x + y * map->width) * 6;

			mapMesh[leftTopIndex].position = sf::Vector2f(cellSize.x * x + position.left, cellSize.y * y + position.top);
			mapMesh[leftTopIndex + 1].position = sf::Vector2f(cellSize.x * x + cellSize.x + position.left, cellSize.y * y + position.top);
			mapMesh[leftTopIndex + 2].position = sf::Vector2f(cellSize.x * x + position.left, cellSize.y * y + cellSize.y + position.top);

			mapMesh[leftTopIndex + 3].position = sf::Vector2f(cellSize.x * x + cellSize.x + position.left, cellSize.y * y + cellSize.y + position.top);
			mapMesh[leftTopIndex + 4].position = sf::Vector2f(cellSize.x * x + position.left, cellSize.y * y + cellSize.y + position.top);
			mapMesh[leftTopIndex + 5].position = sf::Vector2f(cellSize.x * x + cellSize.x + position.left, cellSize.y * y + position.top);
		}
}

void PF_AStar_Visualizer::colorMap()
{
	for (int y = 0; y < map->height; ++y)
		for (int x = 0; x < map->width; ++x)
			if (map->map[x + y * map->width])
				colorSquare(mapMesh, map->width, Vector2(x, y), colorPalette["free"], true);
			else
				colorSquare(mapMesh, map->width, Vector2(x, y), colorPalette["wall"], true);
}

void PF_AStar_Visualizer::colorStartFinish()
{
	colorSquare(mapMesh, map->width, AStarAlgorithm->getStart(), colorPalette["start"], true);
	colorSquare(mapMesh, map->width, AStarAlgorithm->getFinish(), colorPalette["finish"], true);
}

void PF_AStar_Visualizer::colorFrontier()
{
	for (const std::pair<float, Vector2>& cell : *AStarAlgorithm->getFrontier())
		colorSquare(mapMesh, map->width, cell.second, colorPalette["frontier"], true);
}

void PF_AStar_Visualizer::colorCameFrom()
{
	for (const std::pair<Vector2, Vector2>& cell : *AStarAlgorithm->getCameFrom())
		colorSquare(mapMesh, map->width, cell.first, colorPalette["cameFrom"], true);
}

void PF_AStar_Visualizer::colorPath()
{
	for (Vector2 cell : AStarAlgorithm->getPath())
		colorSquare(mapMesh, map->width, cell, colorPalette["path"], true);
}

void PF_AStar_Visualizer::colorCurrent()
{
	colorSquare(mapMesh, map->width, AStarAlgorithm->getCurrent(), colorPalette["current"], true);
}

void PF_AStar_Visualizer::update()
{
	colorCameFrom();
	colorFrontier();
	colorCurrent();
	colorStartFinish();
	colorPath();
}

void PF_AStar_Visualizer::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(mapMesh, _states);
}
