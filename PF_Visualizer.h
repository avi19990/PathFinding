#pragma once

#include <assert.h>

#include "SFML/Graphics.hpp"
#include "PF_Algorithm.h"

class PF_Visualizer : public sf::Drawable
{
private:
	PF_Algorithm* algorithm;

public:
	PF_Visualizer()
	{
		algorithm = nullptr;
	}
	PF_Visualizer(PF_Algorithm* _algorithm)
	{
		assert(_algorithm);

		algorithm = _algorithm;
	}

	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const = 0;
};