#pragma once

class Matrix3x3
{
public:
	Matrix3x3() : mV{0} {}
	Matrix3x3(float a, float b, float c, float d, float e, float f, float g, float h, float j) : mV{ a, b, c, d, e, f, g, h, j } {};
	~Matrix3x3() = default;

	float& operator()(unsigned int row, unsigned int col) {
		return mV[col + 3 * row];
	}

	float operator[](unsigned int index) const {
		return mV[index];
	}

	Vec3 operator*(const Vec3 v) const {
		Vec3 result;
		result.x = mV[0] * v.x + mV[3] * v.y + mV[6] * v.z;
		result.y = mV[1] * v.x + mV[4] * v.y + mV[7] * v.z;
		result.z = mV[2] * v.x + mV[5] * v.y + mV[8] * v.z;
		return result;
	}

	Matrix3x3 operator*(const float& f) {
		Matrix3x3 result;

		for (int i = 0; i < 9; i++)
			result.mV[i] *= f;

		return result;
	}

	
	Matrix3x3 operator*(const Matrix3x3& m) const {

		Matrix3x3 result;
		result.mV[0] = mV[0] * m[0] + mV[3] * m[1] + mV[6] * m[2];
		result.mV[1] = mV[1] * m[0] + mV[4] * m[1] + mV[7] * m[2];
		result.mV[2] = mV[2] * m[0] + mV[5] * m[1] + mV[8] * m[2];

		result.mV[3] = mV[0] * m[3] + mV[3] * m[4] + mV[6] * m[5];
		result.mV[4] = mV[1] * m[3] + mV[4] * m[4] + mV[7] * m[5];
		result.mV[5] = mV[2] * m[3] + mV[5] * m[4] + mV[8] * m[5];

		result.mV[6] = mV[0] * m[6] + mV[3] * m[7] + mV[6] * m[8];
		result.mV[7] = mV[1] * m[6] + mV[4] * m[7] + mV[7] * m[8];
		result.mV[8] = mV[2] * m[6] + mV[5] * m[7] + mV[8] * m[8];
	
		return result;
	}

	Matrix3x3 operator+(const Matrix3x3 m) const {
		Matrix3x3 result;
		for (int i = 0; i < 9; i++)
			result.mV[i] = mV[i] + m[i];
		return result;
	}

public:
	float mV[9];
};