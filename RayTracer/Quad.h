#pragma once
#include "Shape.h"

class Quad : public Shape
{
public:
	Quad() : m_Size(0,0), Shape(){}
	Quad(Point3 a_Normal, Point3 a_Origin, Material a_Material, XYSize a_Size) :
		m_Size(a_Size), Shape(a_Normal, a_Origin, a_Material) {}
	~Quad() = default;

	bool IsIntersect(Ray& r) override;
	Point3 GetRandomPoint() const;

private:
	XYSize m_Size;
};