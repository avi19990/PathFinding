#include "GraphicUtils.h"

void colorSquare(sf::VertexArray& _mesh, int _width, Vector2 _position, sf::Color _color, bool _checkComplete)
{
	int index = (_position.x + _position.y * _width) * 6;
	if (_checkComplete && _mesh[index].color == _color)
		return;
	_mesh[index].color = _color;
	_mesh[index + 1].color = _color;
	_mesh[index + 2].color = _color;
	_mesh[index + 3].color = _color;
	_mesh[index + 4].color = _color;
	_mesh[index + 5].color = _color;
}
