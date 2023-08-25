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

	Vec2 CalculateRepulsion(Particle B) restrict(amp) {
		Vec2 AB = B.position - position;

		float length = AB.length();

		AB.normalise();

		float rep = length < 10 ? 1 / length : 0;

		return AB * rep;
	}

	void BounceParticleBounds() restrict(amp) {
		const float bounceStrength = 0.2;

		if (position.x > w) {
			position.x = w - (velocity.x - (position.x - w));
			velocity.x *= -bounceStrength;
		}

		if (position.x < 0) {
			position.x = velocity.x - position.x;
			velocity.x *= -bounceStrength;
		}

		if (position.y > h) {
			position.y = h - (velocity.y - (position.y - h));
			velocity.y *= -bounceStrength;
		}

		if (position.y < 0) {
			position.y = velocity.y - position.y;
			velocity.y *= -bounceStrength;
		}
	}
};