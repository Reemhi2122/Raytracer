#include "Material.h"

Material& Material::operator=(const Material& rhs)
{
	if (this == &rhs)
		return *this;

	m_DoubleColor = rhs.m_DoubleColor;
	m_DiffuseColor = rhs.m_DiffuseColor;

	m_Reflectiveness = rhs.m_Reflectiveness;
	m_Transparency = rhs.m_Transparency;

	m_IsSpecular = rhs.m_IsSpecular;
	m_BlocksShadow = rhs.m_BlocksShadow;
	m_RecievesLight = rhs.m_RecievesLight;

	return *this;
}

Material::~Material()
{}