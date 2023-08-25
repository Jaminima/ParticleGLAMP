#pragma once

#include "Particle.h"
#include "Consts.h"

Particle* particles;

float defaultValue = 0;

Vec2 rndPos() {
	return Vec2(rand() % w, rand() % h);
}

Vec2 rndVel() {
	return Vec2(
		(rand() % 1000) / 500.0f - 1, 
		(rand() % 1000) / 500.0f - 1
	);
}

void InitWorld() {
	srand(time(NULL));

	particles = new Particle[totalParticles];

	for (int i = 0; i < totalParticles; i++) {
		particles[i].position = rndPos();
		particles[i].velocity = rndVel();
	}
}