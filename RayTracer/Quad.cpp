#include "Quad.h"

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define clamp(x, a, b) max(min(x, b), a)

bool Quad::IsIntersect(Ray& r)
{
	float DirectionDot = dot(m_Normal, r.m_Direction);
	float OriginDot = dot(m_Origin - r.m_Origin, m_Normal);
	float Distance = OriginDot / DirectionDot;

	Vec3 point = r.PositionAt(Distance);
	Vec3 pDirection = point - m_Origin;
	Vec3 rightVec;

	if (m_Normal.x == 0)
		rightVec = Vec3(1, 0, 0);
	else 
		rightVec = Vec3(0, 1, 0);

	Vec3 forwardVec = Cross(m_Normal, rightVec);
	float xpos = dot(pDirection, rightVec);
	float ypos = dot(pDirection, forwardVec);

	if (xpos > m_Size.m_SizeX || xpos < -m_Size.m_SizeX ||
		ypos > m_Size.m_SizeY || ypos < -m_Size.m_SizeY) return false;
	if (Distance >= 0) {
		r.m_Length = Distance;
		return true;
	}
	return false;
}

Point3 Quad::GetRandomPoint() const
{
	float randOne = ((static_cast<float>(std::rand()) / RAND_MAX) - 0.5f) * m_Size.m_SizeX;
	float randTwo = ((static_cast<float>(std::rand()) / RAND_MAX) - 0.5f) * m_Size.m_SizeY;
	return Vec3(m_Origin.x + randOne, m_Origin.y, m_Origin.z + randTwo);
}