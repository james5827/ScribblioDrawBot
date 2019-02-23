#ifndef DRIVER
#define DRIVER
#define TOT_COLORS 22

struct coords{
	unsigned int x;
	unsigned int y;
};

struct color {
	unsigned int red;
	unsigned int green;
	unsigned int blue;
};

struct color_tile {
	struct color color;
	struct coords pos;
};

struct draw {
	struct coords start;
	struct coords end;

	struct coords pos;

	struct color_tile palette[TOT_COLORS];
	unsigned int current_color;
};

#include "mousehook.h"
#include "png_reader.h"
#include <stdbool.h>
#include <math.h>



int find_closest_color(struct color png_col);
#endif
