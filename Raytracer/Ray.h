#pragma once

#include "Vector3.h"

class Ray
{
private:

	Vector3 _origin;
	Vector3 _direction;

public:

	Ray()
	{
		_origin = Vector3::zero();
		_direction = Vector3::right();
	}

	Ray(Vector3 origin, Vector3 direction)
	{
		_origin = origin;
		_direction = direction;
	}

	Vector3 getOrigin() { return _origin; }
	Vector3 getDirection() { return _direction; }

	void setOrigin(const Vector3& origin) { _origin = origin; }
	void setDirection(const Vector3& direction) { _origin = direction; }
};