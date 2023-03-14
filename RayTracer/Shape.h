#pragma once
#include <mutex>
#include "MathLib.h"
#include "Material.h"
#include "Ray.h"

class Shape
{
public:
	Shape() : m_Normal(0,0,0), m_Origin(0,0,0), m_Material(new Color(0,0,0), false, 0, 0, 0, true, true) {}
	Shape(Vec3 a_Normal, Point3 a_Origin, Material a_Material) :
		m_Normal(a_Normal), m_Origin(a_Origin), m_Material(a_Material) {}
	~Shape() = default;

	virtual bool IsIntersect(Ray& r) = 0;

	virtual void SetColor(Color* a_Color);
	virtual Color* GetColor() const;
	virtual void SetOrigin(Point3 a_Origin);
	virtual Point3 GetOrigin() const;
	virtual void SetNormal(Point3 a_Normal);
	virtual Vec3 GetNormal(Point3& a_DifPoint) const;
	virtual Point3 GetRandomPoint() const = 0;

	Material GetMaterial() const;

protected:
	Vec3 m_Normal;
	Point3 m_Origin;
	Material m_Material;
};

inline void Shape::SetColor(Color* a_Color) {
	m_Material.SetDiffuseColor(a_Color);
}

inline Color* Shape::GetColor() const {
	return m_Material.GetDiffuseColor();
}

inline void Shape::SetOrigin(Point3 a_Origin) {
	m_Origin = a_Origin;
}

inline Point3 Shape::GetOrigin() const {
	return m_Origin;
}

inline void Shape::SetNormal(Point3 a_Normal) {
	m_Normal = a_Normal;
}

inline Vec3 Shape::GetNormal(Point3&) const {
	return m_Normal;
}

inline Material Shape::GetMaterial() const
{
	return m_Material;
}

struct XYSize {
	XYSize(float a_SizeX, float a_SizeY) {
		m_SizeX = a_SizeX;
		m_SizeY = a_SizeY;
	}

	float m_SizeX;
	float m_SizeY;
};