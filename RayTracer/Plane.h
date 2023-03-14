#pragma once
#include "Shape.h"

class Plane : public Shape
{
public:
	Plane() : Shape() {}
	Plane(Point3 a_Normal, Point3 a_Origin, Material a_Material) : 
		Shape(a_Normal, a_Origin, a_Material) {}
	~Plane() = default;

	bool IsIntersect(Ray& r) override;
	Point3 GetRandomPoint() const override;
};