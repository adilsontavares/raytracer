#pragma once

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

	void setR(ColorComp r) { _r = r; }
	void setG(ColorComp g) { _g = g; }
	void setB(ColorComp b) { _b = b; }
	void setS(ColorComp s) { _s = s; }
};