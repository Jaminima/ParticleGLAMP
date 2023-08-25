#pragma once

#include "Particle.h"
#include "Consts.h"

Particle* particles;

float defaultValue = 0;

Vec2 rndVec2() {
	return Vec2(rand() % w, rand() % h);
}

void InitWorld() {
	srand(time(NULL));

	particles = new Particle[totalParticles];

	for (int i = 0; i < totalParticles; i++) {
		particles[i].position = rndVec2();
	}
}