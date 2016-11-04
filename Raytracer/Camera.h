#pragma once

#include "Vector3.h"

class Camera
{
public:

	Vector3 _position;
	Vector3 _direction;
	Vector3 _right;
	Vector3 _down;

	Camera()
	{
		_position = Vector3::zero();
		_direction = Vector3::forward();
		_right = Vector3::zero();
		_down = Vector3::down();
	}

	Camera(const Vector3& position, const Vector3& direction)
		: Camera()
	{
		_position = position;
		_direction = direction;
	}

	Camera(const Vector3& position, const Vector3& direction, const Vector3& right, const Vector3& down)
	{
		_position = position;
		_direction = direction;
		_right = right;
		_down = down;
	}

	const Vector3& getPosition() { return _position; }
	const Vector3& getDirection() { return _direction; }
	const Vector3& getRight() { return _right; }
	const Vector3& getDown() { return _down; }


};

