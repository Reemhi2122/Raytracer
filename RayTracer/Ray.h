#pragma once
#include "Mathlib.h"
#include "Material.h"

class Ray
{
public:
	Ray() = default;
	Ray(const Point3& origin, const Vec3& direction) 
		: m_Origin(origin), m_Direction(direction), m_Length(0), m_ObjectMaterials(NULL, false, 0, 0, false, false, false) {};
	Ray& operator=(const Ray& rhs);

	Vec3 m_Origin;
	Vec3 m_Direction;
	float m_Length;
	Material m_ObjectMaterials;

	Vec3 PositionAt(float a_T);
};

inline Ray& Ray::operator=(const Ray& rhs)
{
	if (this == &rhs)
		return *this;

	m_Origin = rhs.m_Origin;
	m_Direction = rhs.m_Direction;
	m_Length = rhs.m_Length;
	m_ObjectMaterials = rhs.m_ObjectMaterials;

	return *this;
}

inline Vec3 Ray::PositionAt(float a_T) {
	return m_Origin + (a_T * m_Direction);
}