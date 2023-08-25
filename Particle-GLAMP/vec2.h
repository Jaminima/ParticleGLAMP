#pragma once
#pragma once
#include <iostream>
#include <amp.h>
#include <amp_math.h>
#include <iostream>
using namespace concurrency;
using namespace fast_math;

class Vec2
{
public:

	union
	{
		struct
		{
			float x, y;
		};

		float Data[2];
	};

	Vec2() restrict(amp, cpu)
	{
		x = 0;
		y = 0;
	}

	Vec2(float x, float y) restrict(amp, cpu)
	{
		this->x = x;
		this->y = y;
	}

	Vec2 operator-(Vec2 V)restrict(amp, cpu)
	{
		Vec2 N(x - V.x, y - V.y);
		return N;
	}

	Vec2 operator+(Vec2 V)restrict(amp, cpu)
	{
		Vec2 N(x + V.x, y + V.y);
		return N;
	}

	void operator+=(Vec2 V)restrict(amp, cpu)
	{
		x += V.x;
		y += V.y;
	}

	Vec2 operator*(int M)restrict(amp, cpu)
	{
		Vec2 N(x * M, y * M);

		return N;
	}

	Vec2 operator*(float M)restrict(amp, cpu)
	{
		Vec2 N(x * M, y * M);

		return N;
	}

	Vec2 operator/(Vec2 V)restrict(amp, cpu)
	{
		Vec2 N(x / V.x, y / V.y);
		return N;
	}

	Vec2 operator*(Vec2 V)restrict(amp, cpu)
	{
		Vec2 N(V.x * x, V.y * y);
		return N;
	}

	float dot(Vec2 V)restrict(amp, cpu)
	{
		return V.x * x + V.y * y;
	}

	index<2> roundToIndex() restrict(amp, cpu) {
		return index<2>(
			(int)roundf(y),
			(int)roundf(x)
		);
	}

	//Vec2 cross(Vec2 V)restrict(amp, cpu)
	//{
	//	/*Vec2 N(
	//		y * V.z - z * V.y,
	//		z * V.x - x * V.z,
	//		x * V.y - y * V.x);
	//	return N;*/
	//}

	void normalise()restrict(amp, cpu)
	{
		float n = sqrt(x * x + y * y);
		x /= n;
		y /= n;
	}

	float length()restrict(amp, cpu) {
		return sqrt(x * x + y * y);
	}

	float norm2() restrict(amp, cpu) { return dot(*this); }
	float norm() restrict(amp, cpu) { return sqrt(norm2()); }
};
