#include "SceneManager.h"

SceneManager::SceneManager()
{
	LightShapes = new Shape*[AmountOfLightshapes]{
		new Sphere(Point3(0.f, 0.f, 0.f), 0.75f, Material(new  Color(1.f, 1.f, 1.f), false, 0, 0, false, false, false)),
		new Quad(Vec3(0.f, -1.f, 0.f), Point3(0.f, 0.f, 0.f), Material(new Color(1.f, 1.f, 1.f), false, 0, 0, false, false, false), XYSize(1, 1))
	};

	Scenes = new Scene[AmountOfScenes]{

	//Scene 1
	Scene(
		9, new Shape * [9] {
			new Quad(Vec3(-1.f, 0.f, 0.f), Point3(4.f, 0.f, 10.f), Material(new Color(0.f, 1.f, 0.f), false, 0, 0, false, true, true), XYSize(4,4)),
			new Quad(Vec3(1.f, 0.f, 0.f), Point3(-4.f, 0.f, 10.f), Material(new Color(1.f, 0.f, 0.f), false, 0, 0, false, true, true), XYSize(4,4)),
			new Quad(Vec3(0.f, 0.f, -1.f), Point3(0.f, 0.f, 12.f), Material(new Color(1.f, 1.f, 1.f), false, 0, 0, false, true, true), XYSize(4,4)),
			new Quad(Vec3(0.f, -1.f, 0.f), Point3(0.f, 4.f, 10.f), Material(new Color(1.f, 1.f, 1.f), false, 0, 0, false, true, true), XYSize(4,4)),
			new Quad(Vec3(0.f, 1.f, 0.f), Point3(0.f, -4.f, 10.f), Material(new Color(1.f, 1.f, 1.f), false, 0, 0, false, true, true), XYSize(4,4)),
			new Sphere(Point3(2.f, -3.f, 9.f), 1.0f, Material(new Color(0.0f, 0.0f, 0.3f), false, 0.4f, 0, true, true, true)),
			new Box(Vec3(1.f, 0.f, 0.f), Point3(-1.f, -1.5f, 10.f), Material(new Color(0.0f, 0.8f, 0.8f), false, 0.5f, 0, true, true, true), Vec3(1,2.5f,1)),
			new Sphere(Point3(-1.5f, -3.f, 7.f), 1.0f, Material(new Color(0.8f, 0.8f, 0.8f), false, 0, 1.55f, true, true, false)),
			LightShapes[0]
		},
		1, new Light * [1]{
			new AreaLight(Point3(0.f, 3.25f, 9.f), LightShapes[0], 5, 50)
		},
		Color(0.1f, 0.1f, 0.6f)
	),

	//Scene 2
	Scene(
		4, new Shape * [4] {
			new Quad(Vec3(0, 1, 0), Point3(1.5f, -8, 12), Material(new Color[2]{Color(1, 0, 0), Color(1, 1, 0)}, true, 0, 0, false, true, true), XYSize(20.f, 60.f)),
			new Sphere(Point3(1.5f, -2.f, 12.f), 2.f, Material(new Color(1.0f, 1.0f, 0.7f), false, 0.5f, 0.f, true, true, true)),
			new Sphere(Point3(-1.f, 0.f, 8.f), 2.f, Material(new Color(1.f, 1.f, 1.f), false, 0.f, 1.5f, true, true, false)),
			new Sphere(Point3(-1.f, 0.f, 8.f), 1.99f, Material(new Color(1.f, 1.f, 1.f), false, 0.f, 0.66f, true, true, false)),
		},
		1, new Light * [1]{
			new PointLight(Point3(-4.f, 70.f, -40.f), 50000)
		},
		Color(0.03f, 0.64f, 0.81f)
	),

	//Scene 3
	Scene(
		6, new Shape * [6] {
			new Sphere(Point3(4.f, 0.f, 0.f), 1.0f, Material(new Color(0.8f, 0.8f, 0.8f), false, 0.9f, 0.f, true, true, true)),
			new Sphere(Point3(-4.f, 0.f, 0.f), 1.0f, Material(new Color(0.8f, 0.8f, 0.8f), false, 0.9f, 0.f, true, true, true)),
			new Sphere(Point3(0.f, 0.f, 4.f), 1.0f, Material(new Color(0.8f, 0.0f, 0.0f), false, 0.0f, 1.5f, true, true, true)),
			new Sphere(Point3(0.f, 0.f, -4.f), 1.0f, Material(new Color(0.8f, 0.8f, 0.8f), false, 0.9f, 0.f, true, true, true)),
			new Quad(Point3(0.0f, 1.0f, 0.0f), Point3(0,-3,0), Material(new Color[2]{Color(1,1,0), Color(0,0,0)}, true, 0, 0, false, true, true), XYSize(30, 30)),
			LightShapes[1]
		},
		1, new Light * [1]{
			new AreaLight(Point3(0.f, 4.f, 0.f), LightShapes[1], 5, 500)
		},
		Color(0.53f, 0.81f, 0.92f)
	),

	//Scene 4
	Scene(
		2, new Shape * [2] {
			new Plane(Vec3(0.f, 1.f, 0.f), Point3(0, -2, 0), Material(new Color[2]{Color(0,0,0), Color(1,1,1)}, true, 0.f, 0.f, false, true, true)),
			new Sphere(Point3(0, 0.f, 12.f), 2.f, Material(new Color(0.7f, 0.7f, 0.7f), false, 0.6f, 0.f, true, true, true)),
		},
		1, new Light * [1]{
			new PointLight(Point3(7.f, 9.f, 6.f), 50000)
		},
		Color(0,0,0)
	),
	
	//Scene 5
	Scene(
		2, new Shape * [2] {
			new Plane(Vec3(0.f, 1.f, 0.f), Point3(0, -2, 0), Material(new Color[2]{Color(0,0,0), Color(1,1,1)}, true, 0.f, 0.f, false, true, true)),
			new Sphere(Point3(0, 0.f, 12.f), 2.f, Material(new Color(1.f, 0.f, 0.f), false, 0.f, 0.f, false, true, true)),
		},
		1, new Light * [1]{
			new PointLight(Point3(7.f, 9.f, 6.f), 50000)
		},
		Color(0,0,0)
	),

	//Scene 6
	Scene(
		2, new Shape * [2] {
			new Sphere(Point3(0, 0.f, 12.f), 2.f, Material(new Color(1.f, 0.f, 0.f), false, 0.f, 0.f, false, false, false)),
			new Plane(Vec3(0.f, 1.f, 0.f), Point3(0, -2, 0), Material(new Color[2]{Color(0,0,0), Color(1,1,1)}, true, 0.f, 0.f, false, false, false)),
		},
		1, new Light * [1]{
			new PointLight(Point3(7.f, 9.f, 6.f), 50000)
		},
		Color(0,0,0)
	),

	//Scene 7
	Scene(
		1, new Shape * [1] {
			new Plane(Vec3(0.f, 1.f, 0.f), Point3(0, -2, 0), Material(new Color[2]{Color(0,0,0), Color(1,1,1)}, true, 0.f, 0.f, false, false, false)),
		},
		1, new Light * [1]{
			new PointLight(Point3(7.f, 9.f, 6.f), 50000)
		},
		Color(0,0,0)
	),
	Scene(0, NULL, 0, NULL, Color()),
	Scene(0, NULL, 0, NULL, Color()),
	Scene(0, NULL, 0, NULL, Color())
	};
}

SceneManager::~SceneManager()
{
	delete Scenes;

	//for (int i = 0; i < AmountOfLightshapes; i++)
	//	delete LightShapes[i];
	//delete LightShapes;
}