#include "Sphere.h"

bool Sphere::IsIntersect(Ray& a_Ray)
{
	float distance = dot(m_Origin - a_Ray.m_Origin, a_Ray.m_Direction);
	Vec3 hitPoint = a_Ray.PositionAt(distance);
	float middleIntersection = (m_Origin - hitPoint).length();

	if (middleIntersection < m_Radius) {
		float x = sqrtf((m_Radius * m_Radius) - (middleIntersection * middleIntersection));
		float firstHitDistance = distance - x;
		float SecondHitDistance = distance + x;

		float epsilon = 0.0002f;
		if (firstHitDistance > epsilon) {
			a_Ray.m_Length = firstHitDistance;
			a_Ray.m_ObjectMaterials = m_Material;
			return true;
		}
		else if (SecondHitDistance > epsilon) {
			a_Ray.m_Length = SecondHitDistance;
			return true;
		}
	}
	return false;
}

Vec3 Sphere::GetNormal(Point3& a_DifPoint) const
{
	Vec3 normal = a_DifPoint - m_Origin;
	return Normalized(normal);
}

Point3 Sphere::GetRandomPoint() const
{
	float diameter = m_Radius + m_Radius;
	Point3 beginPoint(-m_Radius, -m_Radius, -m_Radius);
	float randOne = (static_cast<float>(std::rand()) / RAND_MAX) * diameter;
	float randTwo = (static_cast<float>(std::rand()) / RAND_MAX) * diameter;
	float randThree = (static_cast<float>(std::rand()) / RAND_MAX) * diameter;
	Point3 point = Point3(beginPoint.x + randOne, beginPoint.y + randTwo, beginPoint.z + randThree);
	point.Normalize();
	return m_Origin + (point * m_Radius);
}
