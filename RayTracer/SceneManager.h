#pragma once
#include "Scene.h"
#include "Quad.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Quad.h"
#include "PointLight.h"
#include "AreaLight.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	const int AmountOfScenes = 10;
	const int AmountOfLightshapes = 2;
	Shape** LightShapes;
	Scene* Scenes;
};