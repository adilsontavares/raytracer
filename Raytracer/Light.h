#pragma once

#include "Vector3.h"
#include "Color.h"

class Light
{
private:

	Vector3 _position;
	Color _color;

public:

	Light()
	{
		_position = Vector3::zero();
		_color = Color(1, 1, 1, 0);
	}

	Light(Vector3 position, Color color)
	{
		_position = position;
		_color = color;
	}

	Vector3 getPosition() { return _position; }
	Color getColor() { return _color; }
};