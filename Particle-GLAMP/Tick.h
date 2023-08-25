#pragma once
#include <amp.h>

#include "World.h"
#include <stdlib.h>

unsigned int step = 0;

void InitTick() {
	srand(time(NULL));

	for (int i = 0; i < world_x * world_y; i++) {
		
	}
}

bool inWorldRange(unsigned int idx, unsigned int world_cells) restrict(amp, cpu) {
	return idx < world_cells&& idx >= 0;
}

inline bool isInRange(int i, int lim) restrict(amp) {
	return i < lim && i >= 0;
}

void DoTick() {
	//NX, NY
	const unsigned int wx = world_x;
	const unsigned int wy = world_y;
	const unsigned int wc = world_cells;

	//X, Y
	array_view<Cell, 2> _XY(wy, wx, world);

	//View
	array_view<Color, 2> _frame(w, h, Frame);

	parallel_for_each(_frame.extent,
		[=](index<2> idx) restrict(amp) {
			_frame[idx] = Color(255, 255, 255);
		}
	);

	_frame.synchronize(access_type_write);
}