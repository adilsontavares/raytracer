#pragma once

#include <math.h>

class Vector3
{
private:

	double _x;
	double _y;
	double _z;

public:

	Vector3()
	{
		_x = 0;
		_y = 0;
		_z = 0;
	}

	Vector3(double value)
	{
		_x = value;
		_y = value;
		_z = value;
	}

	Vector3(double x, double y, double z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	double getX() { return _x; }
	double getY() { return _y; }
	double getZ() { return _z; }

	void setX(double x) { _x = x; }
	void setY(double y) { _y = y; }
	void setZ(double z) { _z = z; }
	
	void set(double x, double y, double z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	static Vector3 zero()
	{
		return Vector3(0, 0, 0);
	}

	static Vector3 right()
	{
		return Vector3(1, 0, 0);
	}

	static Vector3 left()
	{
		return Vector3(-1, 0, 0);
	}

	static Vector3 up()
	{
		return Vector3(0, 1, 0);
	}

	static Vector3 down()
	{
		return Vector3(0, -1, 0);
	}

	static Vector3 forward()
	{
		return Vector3(0, 0, 1);
	}

	static Vector3 back()
	{
		return Vector3(0, 0, -1);
	}

	Vector3 Vector3::operator*(const double& scalar)
	{
		return this->mult(scalar);
	}

	Vector3 Vector3::operator+(const Vector3& vec)
	{
		return this->add(vec);
	}

	Vector3 Vector3::operator-(const Vector3& vec)
	{
		return this->sub(vec);
	}

	Vector3 Vector3::operator-()
	{
		return this->negative();
	}

	double magnitude()
	{
		return sqrt(_x * _x + _y * _y + _z * _z);
	}

	Vector3 normalized()
	{
		return (*this) * (1.0 / magnitude());
	}

	Vector3 negative()
	{
		return Vector3(-_x, -_y, -_z);
	}

	double dot(const Vector3& vec)
	{
		return 
			_x * vec._x + 
			_y * vec._y + 
			_z * vec._z;
	}

	Vector3 cross(const Vector3& vec)
	{
		return Vector3(
			_y * vec._z - _z * vec._y, 
			_z * vec._x - _x * vec._z, 
			_x * vec._y - _y * vec._x
		);
	}

	Vector3 add(const Vector3& vec)
	{
		return Vector3(
			_x + vec._x, 
			_y + vec._y, 
			_z + vec._z
		);
	}

	Vector3 sub(const Vector3& vec)
	{
		return Vector3(_x - vec._x, 
			_y - vec._y, 
			_z - vec._z
		);
	}

	Vector3 mult(const double& scalar)
	{
		return Vector3(
			_x * scalar, 
			_y * scalar,
			_z * scalar
		);
	}
};
