#include "driver.h"

struct coords{
	unsigned int x;
	unsigned int y;
};

struct color {
	unsigned int total;
	struct coords pos;
};

struct draw {
	struct coords start;
	struct coords end;

	struct coords pos;

	struct color colors[TOT_COLORS];
	unsigned int current_color;
};

static struct draw drawer = {
	.start = {
		.x = 223,
		.y = 441,
	},

	.end = {
		.x = 990,
		.y = 1016,
	},

	.pos = {
		.x = 224,
		.y = 442,
	},

	.colors = {
		{ // white
			.total = 765,
			.pos = {
				.x = 300,
				.y = 1035,
			},
		},
		{ // light grey
			.total = 580,
			.pos = {
				.x = 324,
				.y = 1035,
			},
		},
		{ // light red
			.total = 267,
			.pos = {
				.x = 348,
				.y = 1035,
			},
		},
		{ // light orange
			.total = 367,
			.pos = {
				.x = 372,
				.y = 1035,
			},
		},
		{ // light yellow
			.total = 479,
			.pos = {
				.x = 396,
				.y = 1035,
			},
		},
		{ // light green
			.total = 203,
			.pos = {
				.x = 420,
				.y = 1035,
			},
		},
		{ // light blue
			.total = 430,
			.pos = {
				.x = 444,
				.y = 1035,
			},
		},
		{ // light navy blue
			.total = 272,
			.pos = {
				.x = 468,
				.y = 1035,
			},
		},
		{ // light purple
			.total = 344,
			.pos = {
				.x = 492,
				.y = 1035,
			},
		},
		{ // light pink
			.total = 498,
			.pos = {
				.x = 516,
				.y = 1035,
			},
		},
		{ // light brown
			.total = 285,
			.pos = {
				.x = 540,
				.y = 1035,
			},
		},
		{ // black
			.total = 0,
			.pos = {
				.x = 300,
				.y = 1059,
			},
		},
		{ // dark grey
			.total = 226,
			.pos = {
				.x = 324,
				.y = 1059,
			},
		},
		{ // dark red
			.total = 130,
			.pos = {
				.x = 348,
				.y = 1059,
			},
		},
		{ // dark orange
			.total = 245,
			.pos = {
				.x = 372,
				.y = 1059,
			},
		},
		{ // dark yellow
			.total = 392,
			.pos = {
				.x = 396,
				.y = 1059,
			},
		},
		{ // dark green
			.total = 99,
			.pos = {
				.x = 420,
				.y = 1059,
			},
		},
		{ // dark blue
			.total = 237,
			.pos = {
				.x = 444,
				.y = 1059,
			},
		},
		{ // dark navy blue
			.total = 121,
			.pos = {
				.x = 468,
				.y = 1059,
			},
		},
		{ // dark purple
			.total = 191,
			.pos = {
				.x = 492,
				.y = 1059,
			},
		},
		{ // dark pink
			.total = 364,
			.pos = {
				.x = 516,
				.y = 1059,
			},
		},
		{ // dark brown
			.total = 158,
			.pos = {
				.x = 540,
				.y = 1059,
			},
		},
	},
	.current_color = -1,
};

int main(void)
{
	init_mousehook();
	read_png_file("chair.png");

	int png_col; int pix_x = 0;
	int pix_y = 0;
	int clicked = 0;
	while (drawer.pos.y < drawer.end.y) {

		while (drawer.pos.x < drawer.end.x) {

			png_col = process_png_file(pix_x, pix_y);

			if (png_col != -1) {
				png_col /= 9;

				png_col = cmp_colors(png_col);

				if (drawer.current_color != png_col) {
					drawer.current_color = png_col;

					if (clicked) {
						release();
						clicked = 0;
					}

					move_mouse(drawer.colors[drawer.current_color].pos.x, drawer.colors[drawer.current_color].pos.y);
					click();
					release();

					move_mouse(drawer.pos.x, drawer.pos.y);
					click();
					clicked = 1;

				} else {
					move_mouse(drawer.pos.x, drawer.pos.y);
				}
			} else {
				if (clicked) {
					release();
					clicked = 0;
				}
				drawer.current_color = -1;
			}
			

			pix_x += 3;
			drawer.pos.x += 3;
		}

		if (clicked) {
			release();
			clicked = 0;
		}

		pix_x = 0;
		pix_y += 2;
		drawer.pos.x = 224;
		drawer.pos.y += 2;
	}

	free_png();
	destroy_mousehook();
	return 0;
}

int cmp_colors(int color)
{
	int ret = 0;
	int min_diff = abs(color - drawer.colors[0].total);
	int tmp_diff;

	for (int i = 1; i < TOT_COLORS; i++) {
		tmp_diff = abs(color - drawer.colors[i].total);
		if (tmp_diff < min_diff) {
			min_diff = tmp_diff;
			ret = i;
		}
	}

	return ret;
}
