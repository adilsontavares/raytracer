#pragma once

class Size
{
private:

	unsigned int _width;
	unsigned int _height;

public:

	Size()
	{
		_width = 0;
		_height = 0;
	}

	Size(unsigned int width, unsigned int height)
	{
		_width = width;
		_height = height;
	}

	unsigned int getWidth() { return _width; }
	unsigned int getHeight() { return _height; }

	void setWidth(unsigned int width) { _width = width; }
	void setHeight(unsigned int height) { _height = height; }
};