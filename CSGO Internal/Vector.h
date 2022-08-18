#pragma once
#include <math.h>

#define PI 3.141592653589793238
#define RAD(x) (x*PI)/180

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
		return { x + vec.x, y + vec.y, z + vec.z };
	}

	inline Vector operator-(const Vector& vec)
	{
		return { x - vec.x, y - vec.y, z - vec.z };
	}

	inline Vector operator/(const float f)
	{
		return { x / f, y / f, z / f };
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

	Vector Copy()
	{
		return { x, y, z };
	}

	Vector& Angle()
	{

		float hypot = sqrt((x * x) + (y * y) + (z * z));
		float pitch = -asin(z / hypot) * (180 / PI);
		float yaw = atan2(y, x) * (180 / PI);

		// using the delta structure to prevent having to create a new vector
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

	Vector& Normalize()
	{
		if (x >= 90.f)
			x = 89.f;
		if (x <= -90.f)
			x = -89.f;

		if (y >= 180.f)
			y = 179.f;
		if (y <= -180.f)
			y = -179.f;
		return *this;
	}

	float Distance(const Vector& vec)
	{
		Vector delta = *this - vec;
		return delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
	}

	float Distance2D(const Vector& vec)
	{
		Vector delta = *this - vec;
		return sqrt(delta.x * delta.x + delta.y * delta.y);
	}
};