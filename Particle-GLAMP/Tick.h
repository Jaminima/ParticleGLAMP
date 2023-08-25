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

Vec2 CalculateRepulsion(Particle A, Particle B) restrict(amp) {
	Vec2 AB = B.position - A.position;

	float length = AB.length();

	AB.normalise();

	float rep = 1 / length;

	return AB * rep;
}

void DoTick() {
	//NX, NY

	//X, Y
	array_view<Particle, 1> _Particles(totalParticles, particles);

	//View
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

			for (int i = 0; i < _Particles.extent[0]; i++) {
				if (i == idx[0])
					continue;

				auto B = _Particles[i];

				auto rep = CalculateRepulsion(A, B);

				repulsion += rep;
			}

			A.velocity += repulsion;
			A.position += A.velocity;
			
			_Particles[idx] = A;
			_frame[A.position.roundToIndex()].SetColor(A.colour);
		}
	);

	_Particles.synchronize(access_type_read_write);
	_frame.synchronize(access_type_read_write);
}