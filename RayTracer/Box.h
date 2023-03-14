#pragma once
#include "Shape.h"
#include "Quad.h"

class Box : public Shape
{
	public:
		Box() : Shape() {}
		Box(Point3 a_Normal, Point3 a_Origin, Material a_Material, Vec3 a_Size);
		~Box() = default;

		bool IsIntersect(Ray& r) override;
		Vec3 GetNormal(Point3& a_DifPoint) const override;
		Point3 GetRandomPoint() const override;

	private:
		Quad m_Quads[6];
};

inline Vec3 Box::GetNormal(Point3& a_DifPoint) const {
	for (int i = 0; i < 6; i++)
	{
		Vec3 Origin = m_Quads[i].GetOrigin();
		Vec3 direction = Origin - a_DifPoint;
		direction.Normalize();

		float epsilon = 0.000001f;
		if (direction.x < epsilon && direction.x > -epsilon || direction.y < epsilon && direction.y > -epsilon || direction.z < epsilon && direction.z > -epsilon)
			return m_Quads[i].GetNormal(a_DifPoint);
	}
	return Vec3(0, 0, 0);
}

inline Point3 Box::GetRandomPoint() const
{
	return m_Origin;
}