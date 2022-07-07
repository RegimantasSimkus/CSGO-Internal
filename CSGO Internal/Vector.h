#pragma once
#include <math.h>

#define PI 3.141592653589793238
#define RAD(x) x*(180/PI)

class Vector
{
public:
	float x, y, z;

	Vector(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	Vector()
	{
		x = y = z = 0;
	}

	inline float operator[](int i) const
	{
		return ((float*)this)[i];
	}

	inline float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	inline Vector operator+(const Vector& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	bool IsZero()
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}
	
	Vector& Zero()
	{
		x = y = z = 0;
		return *this;
	}

	Vector& Sub(const Vector& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector& Angle()
	{
		float hypot = sqrt((x * x) + (y * y) + (z * z));

		float pitch = -asin(z / hypot) * (180.f / PI);
		float yaw = atan2(y, x) * (180.f / PI);

		x = pitch;
		y = yaw;
		z = 0;

		return *this;
	}

	Vector& Add(const Vector& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
};