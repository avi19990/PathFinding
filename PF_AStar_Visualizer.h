#pragma once

#include <assert.h>

#include "PF_Visualizer.h"
#include "PF_AStar.h"
#include "PF_Algorithm.h"
#include "BoolMap.h"
#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include "GraphicUtils.h"

class PF_AStar_Visualizer : public PF_Visualizer
{
private:
	PF_AStar* AStarAlgorithm;
	BoolMap* map;

	sf::VertexArray mapMesh;
	sf::IntRect position;

	std::map<std::string, sf::Color> colorPalette;

	void generateMesh();

	void colorMap();
	void colorStartFinish();
	void colorFrontier();
	void colorCameFrom();
	void colorPath();
	void colorCurrent();

public:
	PF_AStar_Visualizer();
	PF_AStar_Visualizer(PF_Algorithm* _algorithm, sf::IntRect _position, std::map<std::string, sf::Color> _colorPalette);

	void update();
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
};