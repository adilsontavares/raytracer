#pragma once

#include "Size.h"
#include "Color.h"

#include <stdio.h>
#include <cassert>
#include <fstream>

class Bitmap
{
private:

	Size _size;
	Color *_colors;

	void allocColors()
	{
		_colors = new Color[_size.getWidth() * _size.getHeight()];
	}

	void freeColors()
	{
		delete _colors;
	}

public:

	Bitmap(Size size)
	{
		assert(size.getWidth() > 0 && size.getHeight() > 0);
		
		_size = size;
		allocColors();
	}

	~Bitmap()
	{
		freeColors();
	}

	bool exists(unsigned int x, unsigned int y)
	{
		return x >= 0 && x < _size.getWidth() && y >= 0 && y < _size.getHeight();
	}

	void setPixel(unsigned int x, unsigned int y, Color color)
	{
		if (!exists(x, y))
			return;

		_colors[x + y * _size.getWidth()] = color;
	}

	bool save(const char *path)
	{
		FILE *file;
		
		const int dpi = 32;

		const unsigned int width = _size.getWidth();
		const unsigned int height = _size.getHeight();

		const unsigned int k = width * height;
		int s = 4 * k;
		int fileSize = 54 + s;

		double factor = 39.375;
		int m = static_cast<int>(factor);
		int ppm = dpi * m;

		unsigned char fileHeader[14] = { 'B', 'M', 0, 0, 0, 0,  0, 0, 0, 0,  54, 0, 0, 0 };
		unsigned char infoHeader[40] = { 40, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 24, 0 };

		fileHeader[2] = (unsigned char)(fileSize);
		fileHeader[3] = (unsigned char)(fileSize >> 8);
		fileHeader[4] = (unsigned char)(fileSize >> 16);
		fileHeader[5] = (unsigned char)(fileSize >> 24);

		infoHeader[4] = (unsigned char)(width);
		infoHeader[5] = (unsigned char)(width >> 8);
		infoHeader[6] = (unsigned char)(width >> 16);
		infoHeader[7] = (unsigned char)(width >> 24);

		infoHeader[8]  = (unsigned char)(height);
		infoHeader[9]  = (unsigned char)(height >> 8);
		infoHeader[10] = (unsigned char)(height >> 16);
		infoHeader[11] = (unsigned char)(height >> 24);

		infoHeader[21] = (unsigned char)(s);
		infoHeader[22] = (unsigned char)(s >> 8);
		infoHeader[23] = (unsigned char)(s >> 16);
		infoHeader[24] = (unsigned char)(s >> 24);

		infoHeader[25] = (unsigned char)(ppm);
		infoHeader[26] = (unsigned char)(ppm >> 8);
		infoHeader[27] = (unsigned char)(ppm >> 16);
		infoHeader[28] = (unsigned char)(ppm >> 24);

		infoHeader[29] = (unsigned char)(ppm);
		infoHeader[30] = (unsigned char)(ppm >> 8);
		infoHeader[31] = (unsigned char)(ppm >> 16);
		infoHeader[32] = (unsigned char)(ppm >> 24);

		file = fopen(path, "wb");
		if (!file)
			return false;

		fwrite(fileHeader, 1, 14, file);
		fwrite(infoHeader, 1, 40, file);

		ColorRawComp color[3];
		Color pixel;

		for (unsigned int i = 0; i < k; ++i)
		{
			pixel = _colors[i];

			color[0] = pixel.getRawB();
			color[1] = pixel.getRawG();
			color[2] = pixel.getRawR();

			fwrite(color, 1, 3, file);
		}

		fclose(file);

		return true;
	}
};

