#pragma once

#include "Vector3.h"

typedef float ColorComp;
typedef unsigned char ColorRawComp;

class Color
{
private:

	ColorComp _r;
	ColorComp _g;
	ColorComp _b;
	ColorComp _s;

	ColorRawComp CompToRaw(ColorComp comp) { return (ColorRawComp)(comp * 255.0); }

public:

	Color()
	{
		_r = 0;
		_g = 0;
		_b = 0;
		_s = 0;
	}

	Color(ColorComp r, ColorComp g, ColorComp b)
	{
		_r = r;
		_g = g;
		_b = b;
		_s = 0;
	}

	Color(ColorComp r, ColorComp g, ColorComp b, ColorComp s)
	{
		_r = r;
		_g = g;
		_b = b;
		_s = s;
	}

	static Color white()
	{
		return Color(1, 1, 1, 0);
	}

	static Color black()
	{
		return Color(0, 0, 0, 0);
	}

	static Color gray()
	{
		return Color(0.5, 0.5, 0.5, 0);
	}

	ColorComp getR() { return _r; }
	ColorComp getG() { return _g; }
	ColorComp getB() { return _b; }
	ColorComp getS() { return _s; }

	ColorRawComp getRawR() { return CompToRaw(_r); }
	ColorRawComp getRawG() { return CompToRaw(_g); }
	ColorRawComp getRawB() { return CompToRaw(_b); }
	ColorRawComp getRawS() { return CompToRaw(_s); }

	double brightness()
	{
		return (_r + _g + _b) / 3.0;
	}

	Color operator+(const Color& color)
	{
		return this->add(color);
	}

	Color operator*(const Color& color)
	{
		return this->mult(color);
	}

	Color operator*(const double& scalar)
	{
		return Color(
			_r * scalar,
			_g * scalar,
			_b * scalar,
			_s
		);
	}

	Color add(const Color& color)
	{
		return Color(
			_r + color._r,
			_g + color._g,
			_b + color._b,
			_s
		);
	}

	Color mult(const Color& color)
	{
		return Color(
			_r * color._r,
			_g * color._g,
			_b * color._b,
			_s
		);
	}

	Color avg(const Color& color)
	{
		return Color(
			(_r + color._r) * 0.5,
			(_g + color._g) * 0.5,
			(_b + color._b) * 0.5,
			_s
		);
	}

	Color clipping()
	{
		ColorComp all = _r + _g + _b;
		ColorComp excess = all - 3;

		Color color(*this);

		/*if (excess > 0)
		{
			color.setR(_r + excess * (_r / all));
			color.setG(_g + excess * (_g / all));
			color.setB(_b + excess * (_b / all));
		}

		if (color.getR() > 1)
			color.setR(1);
		else if (color.getR() < 0)
			color.setR(0);

		if (color.getG() > 1)
			color.setG(1);
		else if (color.getG() < 0)
			color.setG(0);

		if (color.getB() > 1)
			color.setB(1);
		else if (color.getB() < 0)
			color.setB(0);*/

		return color;
	}

	void setR(ColorComp r) { _r = r; }
	void setG(ColorComp g) { _g = g; }
	void setB(ColorComp b) { _b = b; }
	void setS(ColorComp s) { _s = s; }
};