#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Math/Vector2.h"
#include "Vec3.h"

//TEST_CASE("Testing Vector2 functionality")
//{
//	SUBCASE("Construction")
//	{
//		/// Default constructor
//		const Vector2 v0;
//		CHECK(v0.x == 0.0f);
//		CHECK(v0.y == 0.0f);
//
//		/// Constructor from components
//		const Vector2 v1(9.1f, -3.0f);
//		CHECK(v1.x == 9.1f);
//		CHECK(v1.y == -3.0f);
//
//		/// Constructor from components
//		const Vector2 v2(4.3f);
//		CHECK(v2.x == 4.3f);
//		CHECK(v2.y == 4.3f);
//
//		/// Copy construction
//		Vector2 v3(v2);
//		CHECK(v2.x == v3.x);
//		CHECK(v2.y == v3.y);
//
//		/// Zero all the components of the vector
//		v3.Clear();
//		CHECK(v0.x == v3.x);
//		CHECK(v0.y == v3.y);
//	}
//
//	SUBCASE("Mathematical operators")
//	{
//		const Vector2 v0(2.3f, 3.7f);
//		const Vector2 v1(-6.6f, 1.2f);
//		const float factor = 3.5f;
//		Vector2 v2;
//
//		/// Returns the value of the given vector added to this.
//		v2 = v0 + v1;
//		CHECK(v2.x == v0.x + v1.x);
//		CHECK(v2.y == v0.y + v1.y);
//
//		/// Returns the value of the given vector subtracted from this.
//		v2 = v0 - v1;
//		CHECK(v2.x == v0.x - v1.x);
//		CHECK(v2.y == v0.y - v1.y);
//
//		SUBCASE("Vector and scalar multiplication.")
//		{
//			/// Returns a copy of this vector scaled the given value.
//			v2 = v1 * factor;
//			CHECK(v2.x == v1.x * factor);
//			CHECK(v2.y == v1.y * factor);
//
//			/// Returns a new vector being the result of a float value multiplied on right hand side with a vector
//			v2 = factor * v0;
//			CHECK(v2.x == v0.x * factor);
//			CHECK(v2.y == v0.y * factor);
//		}
//
//		/// Returns a copy of this vector scaled the given value.
//		v2 = v0 / factor;
//		CHECK(v2.x == v0.x / factor);
//		CHECK(v2.y == v0.y / factor);
//
//		SUBCASE("Dot product calculation.")
//		{
//			/// Calculates and returns the dot product of this vector with the given vector.
//			const float dot = v0 * v1;
//			CHECK(-10.74f == dot);
//
//			const float calculatedDot = v0.Dot(v1);
//			CHECK(dot == calculatedDot);
//		}
//
//		/// Adds the given vector to this.
//		SUBCASE("Adds the given vector to this.")
//		{
//			Vector2 v3(3.0f, -4.0f);
//			v3 += v0;
//			CHECK(v3.x == v0.x + 3.0f);
//			CHECK(v3.y == v0.y + -4.0f);
//		}
//
//		/// Subtracts the given vector from this
//		SUBCASE("Subtracts the given vector from this.")
//		{
//			Vector2 v3(3.0f, -4.0f);
//			v3 -= v1;
//			CHECK(v3.x == 3.0f - v1.x);
//			CHECK(v3.y == -4.0f - v1.y);
//		}
//
//		/// Multiplies this vector by the given scalar
//		SUBCASE("Multiplies this vector by the given scalar.")
//		{
//			Vector2 v3(3.0f, -4.0f);
//			v3 *= factor;
//			CHECK(v3.x == 3.0f * factor);
//			CHECK(v3.y == -4.0f * factor);
//		}
//	}
//
//	SUBCASE("Logical operators")
//	{
//		/// Checks if the two vectors have identical components
//		const float x = 2.93f;
//		const float y = 4.39f;
//		Vector2 v0(x, y);
//		Vector2 v1(x, y);
//		Vector2 v2(y, x);
//
//		CHECK(v0 == v1);
//		CHECK(v2 != v0);
//	}
//
//	SUBCASE("Length operations")
//	{
//		Vector2 v0(3.0f, 4.0f);
//
//		/// Gets the magnitude of this vector
//		const float vectorLenght = v0.Magnitude();
//		CHECK(vectorLenght == 5.0f);
//
//		/// Gets the squared magnitude of this vector
//		const float vectorLenghtSq = v0.SquareMagnitude();
//		CHECK(vectorLenghtSq == 25.0f);
//
//		/// Limits the size of the vector to the given maximum
//		v0.Trim(2.5f);
//		CHECK(2.5f == v0.Magnitude());
//
//		/// Returns the normalised version of a vector
//		Vector2 v1 = v0;
//		Vector2 v2 = v1.Unit();
//		CHECK(v1 == v0);
//		CHECK(1.0f == v2.Magnitude());
//			
//		/// Turns a non-zero vector into a vector of unit length
//		v0.Normalize();
//		CHECK(1.0f == v0.Magnitude());
//	}
//}

TEST_CASE("Testing Vector3 functionality")
{
	SUBCASE("Construction")
	{
		/// The default constructor creates a zero vector.
		const Vec3 v0 = Vec3();
		CHECK(v0.x == 0);
		CHECK(v0.y == 0);
		CHECK(v0.z == 0);

		/// Creates a vector with the given components
		const Vec3 v1 = Vec3(34.5f, 4.4f, 53.5f);
		CHECK(v1.x == 34.5f);
		CHECK(v1.y == 4.4f);
		CHECK(v1.z == 53.5f);

		/// Copy construction
		Vec3 v2(v1);
		CHECK(v2.x == v1.x);
		CHECK(v2.y == v1.y);
		CHECK(v2.y == v1.y);

		/// Zero all the components of the vector
		v2.Clear();
		CHECK(v2.x == 0);
		CHECK(v2.y == 0);
		CHECK(v2.z == 0);
	}

	SUBCASE("Mathematical operators")
	{
		const Vec3 v0(2.3f, 3.7f, 4.4f);
		const Vec3 v1(-6.6f, 1.2f, 3.3f);
		const float factor = 3.5f;
		Vec3 v2;

		/// Returns the value of the given vector added to this
		v2 = v0 + v1;
		CHECK(v2.x == v0.x + v1.x);
		CHECK(v2.y == v0.y + v1.y);
		CHECK(v2.z == v0.z + v1.z);

		/// Returns the value of the given vector subtracted from this
		v2 = v0 - v1;
		CHECK(v2.x == v0.x - v1.x);
		CHECK(v2.y == v0.y - v1.y);
		CHECK(v2.z == v0.z - v1.z);

		/// Returns a copy of this vector scaled the given value
		v2 = v1 * factor;
		CHECK(v2.x == v1.x * factor);
		CHECK(v2.y == v1.y * factor);
		CHECK(v2.z == v1.z * factor);

		/// Returns a copy of this vector scaled the inverse of the value
		v2 = factor * v0;
		CHECK(v2.x == v0.x * factor);
		CHECK(v2.y == v0.y * factor);
		CHECK(v2.z == v0.z * factor);

		/// Returns a copy of this vector scaled the given value.
		v2 = v0 / factor;
		CHECK(v2.x == (1 / factor) * v0.x);
		CHECK(v2.y == (1 / factor) * v0.y);
		CHECK(v2.z == (1 / factor) * v0.z);

		/// Returns the negative this vector
		v2 = -v1;
		CHECK(v2.x == -v1.x);
		CHECK(v2.y == -v1.y);
		CHECK(v2.z == -v1.z);

		/// Adds the given vector to this
		Vec3 v3(3.0f, -4.0f, 23.f);
		v3 += v0;
		CHECK(v3.x == v0.x + 3.0f);
		CHECK(v3.y == v0.y + -4.0f);
		CHECK(v3.z == v0.z + 23.0f);

		/// Subtracts the given vector from this
		Vec3 v4(3.0f, -4.0f, 45.0f);
		v4 -= v1;
		CHECK(v4.x == 3.0f - v1.x);
		CHECK(v4.y == -4.0f - v1.y);
		CHECK(v4.z == 45.0f - v1.z);

		/// Multiplies this vector by the given scalar
		Vec3 v5(3.0f, -4.0f, 4.5f);
		v5 *= factor;
		CHECK(v5.x == 3.0f * factor);
		CHECK(v5.y == -4.0f * factor);
		CHECK(v5.z == 4.5f * factor);

		///Divide this vector by the given scalar
		Vec3 v6(5.0f, -4.0f, 4.5f);
		v6 /= factor;
		CHECK(v6.x == (1 / factor) * 5.0f);
		CHECK(v6.y == (1 / factor) * -4.0f);
		CHECK(v6.z == (1 / factor) * 4.5f);

		SUBCASE("Vector products")
		{
			/// Calculates and returns the dot product of this vector with the given vector.
			Vec3 v0(1,5,4), v1(5,8,6);
			const float d = dot(v0, v1);
			CHECK(69 == d);

			const float calculatedDot = v0.dot(v1);
			CHECK(d == calculatedDot);

			/// Calculates and returns the cross product of this vector with the given vector.
			const Vec3 cross = Cross(v0, v1);
			CHECK(Vec3(-2, 14, -17) == cross);

			const Vec3 calculatedCross = v0.Cross(v1);
			CHECK(Vec3(-2, 14, -17) == calculatedCross);
		}

		SUBCASE("Length operations")
		{
			Vec3 v0(3.0f, 4.0f, 4.0f);

			///  Gets the magnitude of this vector
			const float length = v0.length();
			CHECK(length == 6.4031242f);

			/// Gets the squared magnitude of this vector
			const float srLength = v0.length_squared();
			CHECK(srLength == 41);

			/// Turns a non-zero vector into a vector of unit length
			v0.Normalize();
			CHECK(v0.length() == 1.0f);

			/// Returns the normalised version of a vector
			Vec3 v2 = Normalized(v0);
			CHECK(v2 == v0);
			CHECK(1.0f == v2.length());
		}
	}

	SUBCASE("Logical operations")
	{
		/// Checks if the two vectors have identical components
		/// Checks if the two vectors have non-identical components
		const float x = 2.93f;
		const float y = 4.39f;
		const float z = 6.44f;
		Vec3 v0(x, y, z);
		Vec3 v1(x, y, z);
		Vec3 v2(y, x, z);

		CHECK(v0 == v1);
		CHECK(v2 != v0);
	}
}

//TEST_CASE("Testing Matrix33 functionality")
//{
//	SUBCASE("Construction")
//	{
//		/// Construct a new matrix from explicit values
//		/// Construct a new identity matrix
//
//		/// Creates an identity matrix
//		/// Creates a translation matrix
//		/// Creates a scale matrix
//		/// Creates a uniform scale matrix
//
//		/// Creates a rotation matrix around an arbitrary axis (angle in radians)
//		/// Creates a rotation matrix around the x axis (angle in radians)
//		/// Creates a rotation matrix around the y axis (angle in radians)
//		/// Creates a rotation matrix around the z axis (angle in radians)
//	}
//
//	SUBCASE("Mathematical operations")
//	{
//		/// Matrix addition
//		/// Matrix subtraction
//		/// Matrix multiplication
//
//		SUBCASE("Inversion")
//		{
//			/// Get the determinant of this matrix
//			/// Inverts this matrix
//			/// Transposes this matrix
//		}
//	}
//
//	/// Get the x axis 
//	/// Get the y axis 
//	/// Get the z axis 
//}
//
//TEST_CASE("Testing Matrix44 functionality")
//{
//	SUBCASE("Construction")
//	{
//		/// Construct a new matrix from explicit values
//		/// Construct a new identity matrix
//
//		/// Creates an identity matrix
//		/// Creates a translation matrix
//		/// Creates a scale matrix
//		/// Creates a uniform scale matrix
//
//		/// Creates a rotation matrix around an arbitrary axis (angle in radians)
//		/// Creates a rotation matrix around the x axis (angle in radians)
//		/// Creates a rotation matrix around the y axis (angle in radians)
//		/// Creates a rotation matrix around the z axis (angle in radians)
//		/// Creates an orthographic projection matrix
//		/// Creates a frustum projection matrix
//		/// Creates a perspective projection matrix from camera settings
//		/// Creates a look at matrix, usually a view matrix  
//	}
//
//	SUBCASE("Mathematical operations")
//	{
//		/// Matrix addition
//		/// Matrix subtraction
//		/// Matrix multiplication
//
//		SUBCASE("Inversion")
//		{
//			/// Get the determinant of this matrix
//			/// Inverts this matrix
//			/// Transposes this matrix
//		}
//	}
//
//	SUBCASE("Transformation")
//	{
//		/// Transform the given vector by this matrix.
//		/// Transform the direction vector of this matrix
//	}
//
//	/// Retrieve translation part of the matrix
//	/// Set the translation of the matrix
//	/// Get the x orientation axis 
//	/// Get the y orientation axis 
//	/// Get the z orientation axis 
//
//	/// Sets the orientation of the matrix to the orthogonal basis vector
//}
