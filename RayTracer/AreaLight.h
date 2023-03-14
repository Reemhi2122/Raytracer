#pragma once
#include "Light.h"
#include "Shape.h"
#include "Quad.h"

class AreaLight : public Light
{
public:
	AreaLight() : m_LightShape(new Quad()), m_Size(0), Light() {}
	AreaLight(Point3 a_Origin, Shape* a_Shape, float a_Size, float a_Brightness);
	~AreaLight() = default;

	virtual Point3 GetPoint() override;

	Shape* GetShape() const;
	float GetSize() const;

private:
	Shape* m_LightShape;
	float m_Size;
};

inline Shape* AreaLight::GetShape() const {
	return m_LightShape;
}

inline float AreaLight::GetSize() const
{
	return m_Size;
}