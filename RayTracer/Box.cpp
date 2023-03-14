#include "Box.h"

Box::Box(Point3 a_Normal, Point3 a_Origin, Material a_Material, Vec3 a_Size) : 
	Shape(a_Normal, a_Origin, a_Material)
{
	Vec3 nor[6] = { Vec3(1.f, 0, 0), Vec3(-1.f, 0, 0), Vec3(0, -1.f, 0), Vec3(0, 1.f, 0), Vec3(0, 0, -1.f), Vec3(0, 0, 1.f)};
	Vec3 pos[6] = { Vec3(a_Size.x, 0, 0), Vec3(-a_Size.x, 0, 0), Vec3(0, -a_Size.y, 0), Vec3(0, a_Size.y, 0), Vec3(0, 0, -a_Size.z), Vec3(0, 0, a_Size.z)};
	XYSize QSize[3] = { XYSize(a_Size.y, a_Size.z), XYSize(a_Size.x, a_Size.z), XYSize(a_Size.x ,a_Size.y) };

	int Quads = 6;
	for (int i = 0; i < Quads; i++)
		m_Quads[i] = Quad(nor[i], m_Origin + pos[i], m_Material, QSize[static_cast<int>(i / 2)]);
}

bool Box::IsIntersect(Ray& r)
{
	float length = static_cast<float>(INT_MAX);
	bool intersection = false;
	int Quads = 6;
	for (int i = 0; i < Quads; i++)
	{
		if (m_Quads[i].IsIntersect(r) && r.m_Length < length) {
			intersection = true;
			length = r.m_Length;
		}
	}

	r.m_Length = length;
	return intersection;
}