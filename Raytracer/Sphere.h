#pragma once

#include "Vector3.h"
#include "Color.h"
#include "Object.h"

class Sphere : public Object
{
private:

	Vector3 _center;
	double _radius;

public:

	Sphere()
		: Object()
	{
		_center = Vector3::zero();
		_radius = 1;
	}

	Sphere(Vector3 center, double radius)
		: Sphere()
	{
		_center = center;
		_radius = radius;
	}

	Sphere(Vector3 center, double radius, Color color)
		: Object()
	{
		_center = center;
		_radius = radius;
		_color = color;
	}

	Vector3 getNormalAt(Vector3 point)
	{
		Vector3 normal = (point - _center).normalized();
		return normal;
	}

	virtual double intersection(Ray ray)
	{
		Vector3 origin = ray.getOrigin();
		Vector3 direction = ray.getDirection();

		double a = 1;
		double b =
			(2 * (origin.getX() - _center.getX()) * direction.getX()) +
			(2 * (origin.getY() - _center.getY()) * direction.getY()) +
			(2 * (origin.getZ() - _center.getZ()) * direction.getZ());

		double c =
			pow(origin.getX() - _center.getX(), 2) +
			pow(origin.getY() - _center.getY(), 2) +
			pow(origin.getZ() - _center.getZ(), 2) -
			(_radius * _radius);

		double discriminant = b * b - 4 * c;

		if (discriminant > 0) // the ray intersects the sphere
		{
			double root1 = ((-1 * b - sqrt(discriminant)) / 2.0) - 0.000001;

			if (root1 > 0) // the first root is the smallest positive root
				return root1;

			double root2 = ((sqrt(discriminant) - b) / 2.0) - 0.000001;
			return root2;
		}

		// the ray missed the sphere
		return -1;
	}
};