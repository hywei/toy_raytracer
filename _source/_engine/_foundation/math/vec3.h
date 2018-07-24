#ifndef __FOUNDATION_MATH_VEC3_H__
#define __FOUNDATION_MATH_VEC3_H__

#include "_foundation/math/math.h"

namespace raytracer
{
	class Vec3
	{
	public:
		Vec3() : x(0.0f), y(0.0f), z(0.0f)
		{
		}

		explicit Vec3(float a) : x(a), y(a), z(a)
		{
		}

		Vec3(float nx, float ny, float nz) : x(nx), y(ny), z(nz)
		{
		}

		Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z)
		{
		}

		Vec3& operator=(const Vec3& p)
		{
			x = p.x;
			y = p.y;
			z = p.z;
			return *this;
		}

		float& operator[](unsigned int index)
		{
			return reinterpret_cast<float*>(this)[index];
		}

		const float& operator[](unsigned int index) const
		{
			return reinterpret_cast<const float*>(this)[index];
		}

		bool operator==(const Vec3& v) const
		{
			return x == v.x && y == v.y && z == v.z;
		}

		bool operator!=(const Vec3& v) const
		{
			return x != v.x || y != v.y || z != v.z;
		}

		bool isZero() const
		{
			return x == 0.0f && y == 0.0f && z == 0.0f;
		}

		bool isFinite() const
		{
			return RTIsFinite(x) && RTIsFinite(y) && RTIsFinite(z);
		}

		bool isNormalized() const
		{
			const float unitTolerance = 1e-4f;
			return isFinite() && RTAbs(magnitude() - 1) < unitTolerance;
		}

		/**
		\brief returns the squared magnitude
		Avoids calling RTSqrt()!
		*/
		float magnitudeSquared() const
		{
			return x * x + y * y + z * z;
		}

		/**
		\brief returns the magnitude
		*/
		float magnitude() const
		{
			return RTSqrt(magnitudeSquared());
		}

		/**
		\brief negation
		*/
		Vec3 operator-() const
		{
			return Vec3(-x, -y, -z);
		}

		/**
		\brief vector addition
		*/
		Vec3 operator+(const Vec3& v) const
		{
			return Vec3(x + v.x, y + v.y, z + v.z);
		}

		/**
		\brief vector difference
		*/
		Vec3 operator-(const Vec3& v) const
		{
			return Vec3(x - v.x, y - v.y, z - v.z);
		}

		/**
		\brief scalar post-multiplication
		*/
		Vec3 operator*(float f) const
		{
			return Vec3(x * f, y * f, z * f);
		}

		/**
		\brief scalar division
		*/
		Vec3 operator/(float f) const
		{
			f = 1.0f / f;
			return Vec3(x * f, y * f, z * f);
		}

		/**
		\brief vector addition
		*/
		Vec3& operator+=(const Vec3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		/**
		\brief vector difference
		*/
		Vec3& operator-=(const Vec3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		/**
		\brief scalar multiplication
		*/
		Vec3& operator*=(float f)
		{
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}
		/**
		\brief scalar division
		*/
		Vec3& operator/=(float f)
		{
			f = 1.0f / f;
			x *= f;
			y *= f;
			z *= f;
			return *this;
		}

		/**
		\brief returns the scalar product of this and other.
		*/
		float dot(const Vec3& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		/**
		\brief cross product
		*/
		Vec3 cross(const Vec3& v) const
		{
			return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}

		/** return a unit vector */

		Vec3 getNormalized() const
		{
			const float m = magnitudeSquared();
			return m > 0.0f ? *this * RTRecipSqrt(m) : Vec3(0, 0, 0);
		}

		/**
		\brief normalizes the vector in place
		*/
		float normalize()
		{
			const float m = magnitude();
			if (m > 0.0f)
				*this /= m;
			return m;
		}

		/**
		\brief normalizes the vector in place. Does nothing if vector magnitude is under RT_NORMALIZATION_EPSILON.
		Returns vector magnitude if >= RT_NORMALIZATION_EPSILON and 0.0f otherwise.
		*/
		float normalizeSafe()
		{
			const float mag = magnitude();
			if (mag < RT_NORMALIZATION_EPSILON)
				return 0.0f;
			*this *= 1.0f / mag;
			return mag;
		}

		/**
		\brief normalizes the vector in place. Asserts if vector magnitude is under RT_NORMALIZATION_EPSILON.
		returns vector magnitude.
		*/
		float normalizeFast()
		{
			const float mag = magnitude();
			*this *= 1.0f / mag;
			return mag;
		}

		/**
		\brief a[i] * b[i], for all i.
		*/
		Vec3 multiply(const Vec3& a) const
		{
			return Vec3(x * a.x, y * a.y, z * a.z);
		}

		/**
		\brief element-wise minimum
		*/
		Vec3 minimum(const Vec3& v) const
		{
			return Vec3(RTMin(x, v.x), RTMin(y, v.y), RTMin(z, v.z));
		}

		/**
		\brief returns MIN(x, y, z);
		*/
		float minElement() const
		{
			return RTMin(x, RTMin(y, z));
		}

		/**
		\brief element-wise maximum
		*/
		Vec3 maximum(const Vec3& v) const
		{
			return Vec3(RTMax(x, v.x), RTMax(y, v.y), RTMax(z, v.z));
		}

		/**
		\brief returns MAX(x, y, z);
		*/
		float maxElement() const
		{
			return RTMax(x, RTMax(y, z));
		}

		/**
		\brief returns absolute values of components;
		*/
		Vec3 abs() const
		{
			return Vec3(RTAbs(x), RTAbs(y), RTAbs(z));
		}

		float x, y, z;
	};

    inline Vec3 operator*(float f, const Vec3& v)
	{
		return Vec3(f * v.x, f * v.y, f * v.z);
	}

}

#endif
