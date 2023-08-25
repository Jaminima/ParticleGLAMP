#pragma once

#include "Cell.h"
#include "Consts.h"

Cell* world;

unsigned int world_x = w, world_y = h;
unsigned int world_cells = world_x * world_y;
float defaultValue = 0;

void InitWorld() {
	world = new Cell[world_cells];
}