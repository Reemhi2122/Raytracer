#pragma once
#include <cmath>

//Vec3 is made from looking at the tutorial but I am writing everything
//myself and I have to understand everything to use it.
class Vec3
{
public:
	Vec3() : x(0), y(0), z(0) {};
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {};
	~Vec3() = default;

	Vec3& operator=(const Vec3& rhs) {
		if (this == &rhs)
			return *this;

		x = rhs.x;
		y = rhs.y;
		z = rhs.z;

		return *this;
	}

	bool operator==(const Vec3& v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	
	bool operator!=(const Vec3& v) const {
		return !(*this == v);
	}

	Vec3 operator-() const { 
		return Vec3(-x, -y, -z); 
	}

	Vec3& operator+=(const Vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}	
	
	Vec3& operator-=(const Vec3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vec3& operator*=(const float t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	Vec3& operator/=(const float t) {
		return *this *= 1.f / t;
	}

	float dot(const Vec3 v) {
		return x * v.x + y * v.y + z * v.z;
	}

	Vec3 Cross(const Vec3 v) {
		return Vec3(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x);
	}

	float length() const {
		return sqrt(length_squared());
	}

	float length_squared() const {
		return x * x + y * y + z * z;
	}

	Vec3 Normalize() {
		return *this /= length();
	}

	Vec3 Clear() {
		x = y = z = 0;
		return *this;
	}

public:
	float x, y, z;
};

using Color = Vec3;
using Point3 = Vec3;

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vec3 operator*(const float& i, const Vec3& v) {
	return Vec3(i * v.x, i * v.y, i * v.z);
}

inline Vec3 operator*(const Vec3& v, const float& i) {
	return i * v;
}

inline Vec3 operator/(const Vec3& v, float t) {
	return (1 / t) * v;
}

inline float dot(const Vec3& v1, const Vec3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec3 Cross(const Vec3& v1, const Vec3 v2) {
	return Vec3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z, 
		v1.x * v2.y - v1.y * v2.x);
}

inline Vec3 Normalized(Vec3& v) {
	return v / v.length();
}