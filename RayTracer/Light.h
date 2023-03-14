#pragma once
#include "MathLib.h"

class Light
{
public:
	Light() : m_Origin(0.f,0.f,0.f), m_Brightness(0.5f) {}
	Light(Point3 a_Origin, float a_Brightness) : m_Origin(a_Origin), m_Brightness(a_Brightness) {}
	~Light() = default;

	Point3 GetOrigin() const;
	float GetBrightness() const;

	virtual Point3 GetPoint();

protected:
	Point3 m_Origin;
	float m_Brightness;
};

inline Point3 Light::GetOrigin() const
{
	return m_Origin;
}

inline float Light::GetBrightness() const
{
	return m_Brightness;
}

inline Point3 Light::GetPoint()
{
	return m_Origin;
}

