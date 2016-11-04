#pragma once

#include "Vector3.h"
#include "Color.h"

class LightSource
{
protected:

	Vector3 _position;
	Color _color;

	LightSource()
	{
		_position = Vector3::zero();
		_color = Color::white();
	}

	LightSource(Vector3 position)
		: LightSource()
	{
		_position = position;
	}

	LightSource(Vector3 position, Color color)
	{
		_position = position;
		_color = color;
	}

public:

	Vector3 getPosition() { return _position; }
	Color getColor() { return _color; }
};