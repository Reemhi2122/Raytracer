#pragma once
#include "Shape.h"
#include "Light.h"

class Scene
{
public:
	Scene() : m_AmountOfShapes(0), m_Shapes(NULL), m_AmountOfLights(0), m_Lights(NULL), m_SkyBoxColor(0,0,0) {}
	Scene(int a_AmountOfShapes, Shape** a_Shapes, int a_AmountOfLights, Light** a_Lights, Color a_SkyBoxColor) :
		m_AmountOfShapes(a_AmountOfShapes), m_Shapes(a_Shapes), m_AmountOfLights(a_AmountOfLights), m_Lights(a_Lights),
		m_SkyBoxColor(a_SkyBoxColor){}
	~Scene() = default;

	int GetAmountOfShapes() const;
	Shape* GetShape(int a_Index) const;
	int GetAmountOfLights() const;
	Light* GetLight(int a_Index) const;
	Color GetSkyBoxColor() const;

private:
	int m_AmountOfShapes = 0;
	Shape** m_Shapes;
	int m_AmountOfLights = 0;
	Light** m_Lights;
	Color m_SkyBoxColor;
};

inline int Scene::GetAmountOfShapes() const
{
	return m_AmountOfShapes;
}

inline Shape* Scene::GetShape(int a_Index) const
{
	return m_Shapes[a_Index];
}

inline int Scene::GetAmountOfLights() const
{
	return m_AmountOfLights;
}

inline Light* Scene::GetLight(int a_Index) const
{
	return m_Lights[a_Index];;
}

inline Color Scene::GetSkyBoxColor() const
{
	return m_SkyBoxColor;
}