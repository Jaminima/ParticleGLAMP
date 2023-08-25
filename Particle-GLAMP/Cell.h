#pragma once
#include "vec2.h"

class Cell {
public:
	Vec2 velocity = Vec2(0,0);
	float weight = 1;

	Cell() restrict(amp, cpu) {
	}
};