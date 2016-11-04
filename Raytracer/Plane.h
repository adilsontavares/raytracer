#pragma once

#include "Object.h"
#include "Vector3.h"

class Plane : public Object
{
private:

	Vector3 _normal;
	double _distance;

public:

	Plane()
		: Object()
	{
		_normal = Vector3::right();
		_distance = 0;
	}

	Plane(Vector3 normal, double distance)
		: Plane()
	{
		_normal = normal;
		_distance = distance;
	}

	Plane(Vector3 normal, double distance, Color color)
		: Object()
	{
		_normal = normal;
		_distance = distance;
		_color = color;
	}

	Vector3 getNormal() { return _normal; }
	double getDistance() { return _distance; }
	
	Vector3 getNormalAt(Vector3 point)
	{
		return _normal;
	}

	virtual double intersection(Ray ray)
	{
		Vector3 direction = ray.getDirection();

		double a = direction.dot(_normal);

		if (a == 0) // ray is parallel to the plane
		{
			return Object::NoIntersection;
		}
		else
		{
			double b = _normal.dot(ray.getOrigin() - (_normal * _distance));
			return -1 * (b / a);
		}
	}
};