#pragma once
#include "MathLib.h"

class Material
{
public:
	Material() : m_DiffuseColor(new Color()), m_DoubleColor(false), m_Reflectiveness(0), m_Transparency(0),
		m_IsSpecular(false), m_BlocksShadow(false), m_RecievesLight(false) {}
	Material(Color* a_DiffuseColor, bool a_DoubleColor, float a_Reflectiveness, float a_Transparency, bool a_IsSpecular, bool a_BlocksShadow, bool a_RecievesLight) :
		m_DiffuseColor(a_DiffuseColor), m_DoubleColor(a_DoubleColor), m_Reflectiveness(a_Reflectiveness), m_Transparency(a_Transparency), 
		m_IsSpecular(a_IsSpecular), m_BlocksShadow(a_BlocksShadow), m_RecievesLight(a_RecievesLight) {}
	Material& operator=(const Material& rhs);
	~Material();

	bool GetDoubleColor() const;
	void SetDoubleColor(bool a_DoubleColor);

	Color* GetDiffuseColor() const;
	void SetDiffuseColor(Color* a_DiffuseColor);

	float GetReflectiveness() const;
	void SetReflectiveness(float a_Reflectiveness);

	float GetTransparency() const;
	void SetTransparency(float a_Transparency);

	bool GetIsSpecular() const;
	void SetIsSpecular(bool a_IsSpecular);

	bool GetBlocksShadow() const;
	void SetBlockShadow(bool a_BlockShadow);

	bool GetRecievesLight() const;
	void SetRecieveLight(bool a_RecieveLight);

private:
	bool m_DoubleColor;
	Color* m_DiffuseColor;

	float m_Reflectiveness = 0;
	float m_Transparency = 0;
	
	bool m_IsSpecular = false;
	bool m_BlocksShadow = true;
	bool m_RecievesLight = true;
};

inline bool Material::GetDoubleColor() const
{
	return m_DoubleColor;
}

inline void Material::SetDoubleColor(bool a_DoubleColor)
{
	m_DoubleColor = a_DoubleColor;
}

inline Color* Material::GetDiffuseColor() const
{
	return m_DiffuseColor;
}

inline void Material::SetDiffuseColor(Color* a_DiffuseColor)
{
	m_DiffuseColor = a_DiffuseColor;
}

inline float Material::GetReflectiveness() const
{
	return m_Reflectiveness;
}

inline void Material::SetReflectiveness(float a_Reflectiveness)
{
	m_Reflectiveness = a_Reflectiveness;
}

inline float Material::GetTransparency() const
{
	return m_Transparency;
}

inline void Material::SetTransparency(float a_Transparency)
{
	m_Transparency = a_Transparency;
}

inline bool Material::GetIsSpecular() const
{
	return m_IsSpecular;
}

inline void Material::SetIsSpecular(bool a_IsSpecular)
{
	m_IsSpecular = a_IsSpecular;
}

inline bool Material::GetBlocksShadow() const
{
	return m_BlocksShadow;
}

inline void Material::SetBlockShadow(bool a_BlockShadow)
{
	m_BlocksShadow = a_BlockShadow;
}

inline bool Material::GetRecievesLight() const
{
	return m_RecievesLight;
}

inline void Material::SetRecieveLight(bool a_RecieveLight)
{
	m_RecievesLight = a_RecieveLight;
}
