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

	virtual Vector3 getNormalAt(Vector3 point)
	{
		return Vector3::zero();
	}

	virtual double intersection(Ray ray)
	{
		return 0;
	}
};