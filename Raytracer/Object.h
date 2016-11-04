#pragma once

#include "Color.h"
#include "Ray.h"

class Object
{
protected:

	Color _color;

	Object()
	{
		_color = Color::black();
	}

public:

	enum
	{
		NoIntersection = -1
	};

	Color getColor() { return _color; }

	virtual double intersection(Ray ray)
	{
		return 0;
	}
};