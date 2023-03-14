#include "Plane.h"

bool Plane::IsIntersect(Ray& r)
{
	float DirectionDot = dot(m_Normal, r.m_Direction);
	float OriginDot = dot(m_Origin - r.m_Origin, m_Normal);
	float Distance = OriginDot / DirectionDot;

	if (Distance >= 0) {
		r.m_Length = Distance;
		return true;
	}
	return false;
}

Point3 Plane::GetRandomPoint() const
{
	return m_Origin;
}