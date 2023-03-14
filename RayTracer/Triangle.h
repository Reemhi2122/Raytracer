#pragma once
#include "Shape.h"
class Triangle : public Shape
{
	Triangle() {}
	Triangle(Material a_Material) :
		Shape(Vec3(0, 0, 0), Vec3(0,0,0), a_Material) {}
	~Triangle() = default;

	bool IsIntersect(Ray & r) override;

private:
	Vec3 v0, v1, v2;
};

