#pragma once
#include "Shape.h"

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define clamp(x, a, b) max(min(x, b), a)

class Sphere : public Shape
{
public:
	Sphere() : m_Radius(1) {}
	Sphere(Point3 a_Origin, float a_Radius, Material a_Material) : 
		m_Radius(a_Radius), Shape(Vec3(0,0,0), a_Origin, a_Material) {}
	~Sphere() = default;

	bool IsIntersect(Ray& r) override;
	Vec3 GetNormal(Point3& a_DifPoint) const override;

	Point3 GetRandomPoint() const override;

private:
	float m_Radius;
};