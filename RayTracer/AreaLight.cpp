#include "AreaLight.h"

AreaLight::AreaLight(Point3 a_Origin, Shape* a_Shape, float a_Size, float a_Brightness) : Light(a_Origin, a_Brightness)
{
	m_LightShape = a_Shape;
	m_LightShape->SetOrigin(a_Origin);
	m_LightShape->GetMaterial().SetBlockShadow(false);
	m_LightShape->GetMaterial().SetRecieveLight(false);

	m_Origin = a_Origin;
	m_Size = a_Size;
	m_Brightness = a_Brightness;
}

Point3 AreaLight::GetPoint()
{
	return m_LightShape->GetRandomPoint();
}