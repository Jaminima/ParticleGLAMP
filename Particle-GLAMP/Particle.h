#pragma once
#include "vec2.h"

class Particle {
public:
	Vec2 position = Vec2(0, 0);
	Vec2 velocity = Vec2(0, 0);

	Color colour = Color(255, 255, 255);

	float weight = 1;

	Particle() restrict(amp, cpu) {
	}
};