#pragma once
#include <SDL.h>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include "MathLib.h"
#include "Ray.h"

#include "SceneManager.h"

class RayTracer
{
public:
	RayTracer();
	~RayTracer() = default;

	void Initialize();
	void CreateTexture(SDL_Renderer* a_Renderer, std::clock_t a_Clock, int a_curScene);
	void Thread(Color* a_ColorBuffer, int a_StartPointx, int a_StartPointY, int a_Width, int a_Height, std::clock_t a_Clock);

	void CalculateCameraAngle(int a_MXPOS, int a_MYPos, int a_PosX, int a_PosY);
	void ResetAccumulator();

	Color Trace(Ray& a_Ray, int a_FrameNum);
	Color CalculateColor(Ray& a_Ray);
	Color Illumination(Ray& ray, int a_Index, float a_ImpactFactor);

	int GetIntersection(Ray& a_Ray);
	bool GetIntersectionShadow(Ray& a_Ray, float a_LightLength);

	float Shading(int a_Index, Vec3 a_IntersectionPoint, Vec3 a_Direction);
	float GetLightShadow(Vec3 a_IntersectionPoint, int a_Index);
	float LightAttenuation(Vec3 a_RayDir);
	Color PhongShading(Ray& a_Ray, Color a_Color, int a_index);
	Color BeersLaw(Ray a_Ray, Color a_Color, float a_Ior, int a_Index);

	Vec3 GetRefraction(const Vec3& a_Direction, const Vec3& a_Normal, const float& a_Ior);
	float Fresnel(const Vec3& a_Direction, const Vec3& a_Normal, const float& a_Ior);
	Ray GetReflectionRay(Ray& a_Ray, int a_Intersection);


private:
	float m_AspectRatio;
	int m_ImageWidth;
	int m_ImageHeight;

	float m_ViewportHeight;
	float m_ViewportWidth;
	float m_FocalLength;

	Point3 m_Origin;
	Vec3 m_Horizontal;
	Vec3 m_Vertical;
	Vec3 m_TopLeftCorner;

	const float m_MSAA_U[4]{ 0.4f, 0.1f, -0.1f, -0.4f };
	const float m_MSAA_V[4]{ -0.1f, 0.4f, -0.4f, 0.1f };
	int MSAAx = 0;

	const int m_MaxBounceCount = 5;
	int m_CurSceneNum = 0;
	Color** ColorBuffers;

	SceneManager sceneManager;
	Scene m_CurScene;

	int m_XBlockLength;
	int m_YBlockLength;

	const int xThread = 6;
	const int yThread = 6;
	int m_Frames;
};