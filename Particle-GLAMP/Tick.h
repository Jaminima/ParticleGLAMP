#pragma once
#include <amp.h>

#include "World.h"
#include <stdlib.h>

unsigned int step = 0;

void InitTick() {
}

bool inWorldRange(unsigned int idx, unsigned int world_cells) restrict(amp, cpu) {
	return idx < world_cells&& idx >= 0;
}

inline bool isInRange(int i, int lim) restrict(amp) {
	return i < lim && i >= 0;
}

time_t tickTime = 0;

void DoTick() {
	time_t newTickTime = clock();

	float dt = (newTickTime - tickTime) / 1000.0f;
	Vec2 gravity(0,-9.81*dt);

	array_view<Particle, 1> _Particles(totalParticles, particles);
	array_view<Color, 2> _frame(w, h, Frame);

	Color bgColor(0, 0, 0);

	parallel_for_each(_frame.extent,
		[=](index<2>idx) restrict(amp) {
			_frame[idx].SetColor(bgColor);
		}
	);

	parallel_for_each(_Particles.extent,
		[=](index<1> idx) restrict(amp) {
			auto A = _Particles[idx];

			Vec2 repulsion;
			int collisions = 0;

			for (int i = 0; i < _Particles.extent[0]; i++) {
				if (i == idx[0])
					continue;

				auto B = _Particles[i];

				auto rep = A.CalculateRepulsion(B) * -dt;

				repulsion += rep;
			}

			A.velocity += repulsion + gravity;
			A.position += A.velocity;

			A.BounceParticleBounds();
			
			_Particles[idx] = A;
			_frame[A.position.roundToIndex()].SetColor(A.colour);
		}
	);

	_Particles.synchronize(access_type_read_write);
	_frame.synchronize(access_type_read_write);
}