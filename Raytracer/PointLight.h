#pragma once

#include "LightSource.h"

class PointLight : public LightSource
{
public:

	PointLight() : LightSource() {}
	PointLight(Vector3 position) : LightSource(position) {}
	PointLight(Vector3 position, Color color) : LightSource(position, color) {}
};