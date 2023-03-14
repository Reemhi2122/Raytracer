#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight() : Light() {}
	PointLight(Point3 a_Origin, float a_Brightness) : Light(a_Origin, a_Brightness) {}
	~PointLight() = default;
};