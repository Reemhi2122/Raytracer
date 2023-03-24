#include "RayTracer.h"

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
#define clamp(x, a, b) max(min(x, b), a)

RayTracer::RayTracer()
{
	m_AspectRatio = 16.0f / 16.0f;
	m_ImageWidth = 512;
	m_ImageHeight = static_cast<int>(m_ImageWidth / m_AspectRatio);

	m_ViewportHeight = 2;
	m_ViewportWidth = m_ViewportHeight * m_AspectRatio;
	m_FocalLength = 1.5;

	m_Origin = Point3(0, 0.f, 0.0f);
	m_Horizontal = Vec3(m_ViewportWidth, 0, 0);
	m_Vertical = Vec3(0, m_ViewportHeight, 0);
	m_TopLeftCorner = m_Origin - (m_Horizontal / 2) + (m_Vertical / 2) + Vec3(0, 0, m_FocalLength);
	
	MSAAx = 0;

	m_CurSceneNum = 0;
	ColorBuffers;

	m_CurScene = sceneManager.Scenes[m_CurSceneNum];

	m_XBlockLength = m_ImageWidth / xThread;
	m_YBlockLength = m_ImageHeight / yThread;

	m_Frames = 0;
}

void RayTracer::Initialize()
{
	int AmountOfColorBuffers = xThread * yThread;
	int ColorBufferSize = m_XBlockLength * m_YBlockLength;
	ColorBuffers = new Color*[AmountOfColorBuffers];
	for (int i = 0; i < AmountOfColorBuffers; i++)
		ColorBuffers[i] = new Color[ColorBufferSize];
}

void RayTracer::CreateTexture(SDL_Renderer* a_Renderer, std::clock_t a_Clock, int a_curScene)
{	
	m_Frames++;
	if (a_curScene != 0) {
		int scenes = sceneManager.AmountOfScenes;
		if (m_CurSceneNum + a_curScene >= 0 && m_CurSceneNum + a_curScene < scenes) {
			m_CurSceneNum += a_curScene;
			m_Origin = Point3(0, 0, 0);
			m_CurScene = sceneManager.Scenes[m_CurSceneNum];
		}
	}

	const int amountOfThreadsx = 6;
	const int amountOfThreadsy = 6;

	std::thread renderThreads[amountOfThreadsx * amountOfThreadsy];

	for (int x = 0; x < amountOfThreadsx; x++)
	{
		for (int y = 0; y < amountOfThreadsy; y++)
		{
			renderThreads[amountOfThreadsy * x + y] = std::thread(&RayTracer::Thread, this, ColorBuffers[amountOfThreadsy * x + y], x * m_XBlockLength, y * m_YBlockLength, x * m_XBlockLength + m_XBlockLength, y * m_YBlockLength + m_YBlockLength, a_Clock);
		}
	}

	float div = MSAAx > 1 ? 1 : 1.f / m_Frames;
	for (int a = 0; a < amountOfThreadsx; a++)
	{
		for (int b = 0; b < amountOfThreadsy; b++)
		{
			renderThreads[amountOfThreadsy * a + b].join();
			for (int x = 0; x < m_YBlockLength; x++)
			{
				for (int y = 0; y < m_XBlockLength; y++)
				{
					int curBlock = amountOfThreadsx * a + b;
					int curColor = m_XBlockLength * x + y;

					Color color = (ColorBuffers[curBlock][curColor] * 255) * div;
					SDL_SetRenderDrawColor(a_Renderer, static_cast<Uint8>(color.x), static_cast<Uint8>(color.y), static_cast<Uint8>(color.z), 0);
					SDL_RenderDrawPoint(a_Renderer, ((a * m_XBlockLength) + (y))/* + a * 2*/, ((b * m_YBlockLength) + (x)) /*+ b * 2*/);
				}
			}
		}
	}

	SDL_RenderPresent(a_Renderer);
}

void RayTracer::Thread(Color* a_ColorBuffer, int a_StartPointx, int a_StartPointY, int a_Width, int a_Height, std::clock_t a_Clock)
{
	std::srand(a_Clock);

	int index = 0;
	for (int y = a_StartPointY; y < a_Height; y ++)
	{
		for (int x = a_StartPointx; x < a_Width; x ++)
		{
			if (MSAAx > 1) {
				Color pixelColor;
				for (int AA = 0; AA < MSAAx; AA++)
				{
					float u = (float(x) + m_MSAA_U[AA]) / m_ImageWidth;
					float v = (float(y) + m_MSAA_V[AA]) / m_ImageHeight;

					Vec3 Direction = m_TopLeftCorner + (u * m_Horizontal) - (v * m_Vertical);
					Ray ray = Ray(m_Origin, Normalized(Direction));
					pixelColor += Trace(ray, 0);
				}
				pixelColor /= static_cast<float>(MSAAx);
				a_ColorBuffer[index] = pixelColor;
			}
			else {
				float u = (float(x) + static_cast<float>(std::rand()) / RAND_MAX) / m_ImageWidth;
				float v = (float(y) + static_cast<float>(std::rand()) / RAND_MAX) / m_ImageHeight;

				Vec3 Direction = m_TopLeftCorner + (u * m_Horizontal) - (v * m_Vertical);
				Ray ray = Ray(m_Origin, Normalized(Direction));

				a_ColorBuffer[index] += Trace(ray, 0);
				Color col = Trace(ray, 0);
				index++;
			}
		}
	}
}

void RayTracer::CalculateCameraAngle(int a_MXPos, int a_MYPos, int a_PosX, int a_PosY)
{
	if (a_MXPos + a_MYPos + a_PosX + a_PosY != 0) {
		ResetAccumulator();
		m_Origin += Vec3(static_cast<float>(a_PosX), 0, static_cast<float>(a_PosY));

		float angle = static_cast<float>(-a_MXPos) / 100;
		float anglex = static_cast<float>(-a_MYPos) / 100;
		Matrix3x3 matrixx = Matrix3x3(cos(angle), 0, sin(angle), 0, 1, 0, -sin(angle), 0, cos(angle));
		Matrix3x3 matrixy = Matrix3x3(1, 0, 0, 0, cos(anglex), -sin(anglex), 0, sin(anglex), cos(anglex)); // Didn't use but still here for reference

		m_TopLeftCorner = matrixx * m_TopLeftCorner;
		m_Horizontal = matrixx * m_Horizontal;
		m_Vertical = matrixx * m_Vertical;
	}
}

void RayTracer::ResetAccumulator()
{
	m_Frames = 0;
	for (int x = 0; x < xThread * yThread; x++)
		for (int y = 0; y < m_XBlockLength * m_YBlockLength; y++)
			ColorBuffers[x][y] = Color(0, 0, 0);
}

Color RayTracer::Illumination(Ray& a_Ray, int a_Index, float a_ImpactFactor)
{
	Color IlluminationColor = CalculateColor(a_Ray);
	if (!m_CurScene.GetShape(a_Index)->GetMaterial().GetBlocksShadow()) return IlluminationColor;
	
	Point3 LightOrigin = m_CurScene.GetLight(0)->GetPoint();

	//FirstRay
	Point3 intersectionPoint = a_Ray.PositionAt(a_Ray.m_Length);
	Vec3 normalDir = LightOrigin - intersectionPoint;
	
	//LightAttenuation
	IlluminationColor *= LightAttenuation(normalDir);
	
	//Normalize direction
	normalDir.Normalize();

	//SoftShadow
	IlluminationColor *= GetLightShadow(intersectionPoint, a_Index);

	//ObjectShadow
	IlluminationColor *= Shading(a_Index, intersectionPoint, normalDir);

	IlluminationColor *= a_ImpactFactor;

	IlluminationColor = PhongShading(a_Ray, IlluminationColor, a_Index);
	
	return IlluminationColor;
}

float RayTracer::Shading(int a_Index, Vec3 a_IntersectionPoint, Vec3 a_Direction)
{
	return clamp(dot(m_CurScene.GetShape(a_Index)->GetNormal(a_IntersectionPoint), a_Direction), 0, 1);
}

float RayTracer::GetLightShadow(Vec3 a_IntersectionPoint, int a_Index)
{
	float returnColor = 0;
	Vec3 dir = m_CurScene.GetLight(0)->GetPoint() - a_IntersectionPoint;

	Vec3 hitNormal = m_CurScene.GetShape(a_Index)->GetNormal(a_IntersectionPoint);
	hitNormal.Normalize();
	hitNormal *= 0.001f;

	float dirLength = dir.length();
	dir.Normalize();

	Ray ray2 = Ray(a_IntersectionPoint + hitNormal, dir);
	returnColor += GetIntersectionShadow(ray2, dirLength) && ray2.m_Length < dirLength ? 0 : 1;
	float Transparency = ray2.m_ObjectMaterials.GetTransparency() - 1;
	return Transparency > 0 ? returnColor + Transparency : returnColor;
}

float RayTracer::LightAttenuation(Vec3 a_RayDir)
{
	float Distance = sqrt(dot(a_RayDir, a_RayDir));
	return clamp(m_CurScene.GetLight(0)->GetBrightness() / ((4 * PI) * Distance), 0, 1);
}

Color RayTracer::PhongShading(Ray& a_Ray, Color a_Color, int a_index)
{
	if (!m_CurScene.GetShape(a_index)->GetMaterial().GetIsSpecular())
		return a_Color;

	Point3 LightOrigin = m_CurScene.GetLight(0)->GetPoint();
	Point3 intersectionPoint = a_Ray.PositionAt(a_Ray.m_Length);
	Vec3 normalDir = LightOrigin - intersectionPoint;

	normalDir.Normalize();

	Ray reflectiveray = GetReflectionRay(a_Ray, a_index);
	float sharpness = 80;
	float specular = pow(clamp(dot(reflectiveray.m_Direction, normalDir), 0, 1), sharpness);
	return Vec3(
		clamp(specular + a_Color.x, 0, 1),
		clamp(specular + a_Color.y, 0, 1),
		clamp(specular + a_Color.z, 0, 1));

	return a_Color;
}

Color RayTracer::BeersLaw(Ray a_Ray, Color a_Color, float a_Ior, int a_Index)
{
	Vec3 InterSectionPoint = a_Ray.PositionAt(a_Ray.m_Length);
	Color absorb = Color(1, 1, 1) - a_Color;
	if (dot(a_Ray.m_Direction, m_CurScene.GetShape(a_Index)->GetNormal(InterSectionPoint)) > 0){
		float length = a_Ray.m_Length;
		 Color returnCol = absorb * a_Ior * -length;
		 return Color(expf(returnCol.x), expf(returnCol.y), expf(returnCol.z));
	}
	return a_Color;
}

Color RayTracer::Trace(Ray& a_Ray, int a_FrameNum) {
	int Intersection = GetIntersection(a_Ray);

	if (Intersection >= 0) {
		if (a_FrameNum > m_MaxBounceCount) return CalculateColor(a_Ray);
		
		Vec3 InterSectionPoint = a_Ray.PositionAt(a_Ray.m_Length);
		float Transparency = m_CurScene.GetShape(Intersection)->GetMaterial().GetTransparency();
		if (Transparency > 0) {
			Vec3 RefractionDirection = GetRefraction(a_Ray.m_Direction, m_CurScene.GetShape(Intersection)->GetNormal(InterSectionPoint), Transparency);
			Ray RefractionRay = Ray(InterSectionPoint, Normalized(RefractionDirection));
			Ray ReflectRay = GetReflectionRay(a_Ray, Intersection);
			float fresnel = Fresnel(a_Ray.m_Direction, m_CurScene.GetShape(Intersection)->GetNormal(InterSectionPoint), Transparency);

			Color refractionColor = Trace(RefractionRay, ++a_FrameNum);
			refractionColor = refractionColor * BeersLaw(a_Ray, CalculateColor(a_Ray), Transparency, Intersection);
			refractionColor = refractionColor * (1 - fresnel);

			Color col = refractionColor + (Trace(ReflectRay, ++a_FrameNum) * fresnel);
			Color IllColor = dot(a_Ray.m_Direction, m_CurScene.GetShape(Intersection)->GetNormal(InterSectionPoint)) < 0 ? PhongShading(a_Ray, col, Intersection) : col;
			return IllColor;
		}
		else {
			float reflectiveness = m_CurScene.GetShape(Intersection)->GetMaterial().GetReflectiveness();
			if (reflectiveness > 0) {
				Ray ReflectRay = GetReflectionRay(a_Ray, Intersection);
				float normalColorProcentage = 1 - reflectiveness;
				Color TraceColor = Trace(ReflectRay, ++a_FrameNum) * reflectiveness;
				Color IllColor = Illumination(a_Ray, Intersection, normalColorProcentage);
				return Vec3(clamp(TraceColor.x + IllColor.x, 0, 1), clamp(TraceColor.y + IllColor.y, 0, 1), clamp(TraceColor.z + IllColor.z, 0, 1));
			}
			else {
				return Illumination(a_Ray, Intersection, 1);
			}
		}
	}

	return m_CurScene.GetSkyBoxColor();
}

Color RayTracer::CalculateColor(Ray& a_Ray)
{
	if (a_Ray.m_ObjectMaterials.GetDoubleColor()) {
		float offset = 1.5;
		float px = cos(a_Ray.PositionAt(a_Ray.m_Length).x + offset);
		float pz = sin(a_Ray.PositionAt(a_Ray.m_Length).z);

		if (px < 0 == pz < 0)
			return a_Ray.m_ObjectMaterials.GetDiffuseColor()[0];
		else
			return a_Ray.m_ObjectMaterials.GetDiffuseColor()[1];
	}

	return *a_Ray.m_ObjectMaterials.GetDiffuseColor();
}

Vec3 RayTracer::GetRefraction(const Vec3& a_Direction, const Vec3& a_Normal, const float& a_Ior)
{
	float cosi = clamp(dot(a_Direction, a_Normal), -1, 1);

	float ior1 = 1, ior2 = a_Ior;
	Vec3 n = a_Normal;
	if (cosi < 0) {
		cosi = -cosi; 
	} else { 
		float temp = ior1;
		ior1 = ior2;
		ior2 = temp;
		n = -a_Normal; 
	}

	float eta = ior1 / ior2;
	float TIR = 1 - eta * eta * (1 - cosi * cosi);
	return TIR < 0 ? Vec3() : eta * a_Direction + n * (eta * cosi - sqrtf(TIR));
}

float RayTracer::Fresnel(const Vec3& a_Direction, const Vec3& a_Normal, const float& a_Ior)
{
	float cosi = clamp(dot(a_Direction, a_Normal), -1, 1);
	float ior1 = 1, ior2 = a_Ior;

	if (cosi > 0){
		float SwitchTemp = ior1;
		ior1 = ior2;
		ior2 = SwitchTemp;
	}

	float TIR = ior1/ior2 * sqrtf(1 - cosi * cosi);

	if (TIR >= 1) {
		return 1;
	}
	else {
		float cost = sqrt(1 - TIR * TIR);
		cosi = fabsf(cosi);
		float Rs = ((ior2 * cosi) - (ior1 * cost)) / ((ior2 * cosi) + (ior1 * cost));
		float Rp = ((ior1 * cosi) - (ior2 * cost)) / ((ior1 * cosi) + (ior2 * cost));
		return  (Rs * Rs + Rp * Rp) / 2;
	}
}

Ray RayTracer::GetReflectionRay(Ray& a_Ray, int a_Intersection)
{
	Vec3 intersectionPoint = a_Ray.PositionAt(a_Ray.m_Length);
	Vec3 normal = m_CurScene.GetShape(a_Intersection)->GetNormal(intersectionPoint);
	Vec3 hitNormal = Normalized(normal) * 0.00001f;

	Vec3 ReflectDirection = a_Ray.m_Direction - 2 * dot(a_Ray.m_Direction, 
		m_CurScene.GetShape(a_Intersection)->GetNormal(intersectionPoint)) * m_CurScene.GetShape(a_Intersection)->GetNormal(intersectionPoint);
	return Ray(intersectionPoint + hitNormal, Normalized(ReflectDirection));
}

int RayTracer::GetIntersection(Ray& a_Ray)
{
	int curIntersectionIndex = -1;
	float m_PreviousDistance = static_cast<float>(INT_MAX);
	float length = 0;

	for (int i = 0; i < m_CurScene.GetAmountOfShapes(); i++)
	{
		if (m_CurScene.GetShape(i)->IsIntersect(a_Ray)) {
			if (a_Ray.m_Length < m_PreviousDistance) {
				if (a_Ray.m_Length > 0) {
					m_PreviousDistance = a_Ray.m_Length;
					curIntersectionIndex = i;
					length = a_Ray.m_Length;
				}
			}
		}
	}

	if(curIntersectionIndex > -1) a_Ray.m_ObjectMaterials = m_CurScene.GetShape(curIntersectionIndex)->GetMaterial();
	a_Ray.m_Length = length;
	return curIntersectionIndex;
}

bool RayTracer::GetIntersectionShadow(Ray& a_Ray, float a_LightLength)
{
	for (int i = 0; i < m_CurScene.GetAmountOfShapes(); i++)
	{
		if (!m_CurScene.GetShape(i)->GetMaterial().GetBlocksShadow()) continue;
		if (m_CurScene.GetShape(i)->IsIntersect(a_Ray)) {
			if (a_Ray.m_Length > 0 && a_Ray.m_Length < a_LightLength) {
				return true;
			}
		}
	}
	return false;
}