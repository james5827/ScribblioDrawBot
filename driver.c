#include "driver.h"

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

	.palette = {
		{ // white
			.color = {
				.red = 255,
				.green = 255,
				.blue = 255,
			},
			.pos = {
				.x = 300,
				.y = 1035,
			},
		},
		{ // light grey
			.color = {
				.red = 193,
				.green = 193,
				.blue = 193,
			},
			.pos = {
				.x = 324,
				.y = 1035,
			},
		},
		{ // light red
			.color = {
				.red = 239,
				.green = 19,
				.blue = 11,
			},
			.pos = {
				.x = 348,
				.y = 1035,
			},
		},
		{ // light orange
			.color = {
				.red = 255,
				.green = 113,
				.blue = 0,
			},
			.pos = {
				.x = 372,
				.y = 1035,
			},
		},
		{ // light yellow
			.color = {
				.red = 255,
				.green = 228,
				.blue = 0,
			},
			.pos = {
				.x = 396,
				.y = 1035,
			},
		},
		{ // light green
			.color = {
				.red = 0,
				.green = 204,
				.blue = 0,
			},
			.pos = {
				.x = 420,
				.y = 1035,
			},
		},
		{ // light blue
			.color = {
				.red = 0,
				.green = 178,
				.blue = 255,
			},
			.pos = {
				.x = 444,
				.y = 1035,
			},
		},
		{ // light navy blue
			.color = {
				.red = 35,
				.green = 31,
				.blue = 211,
			},
			.pos = {
				.x = 468,
				.y = 1035,
			},
		},
		{ // light purple
			.color = {
				.red = 163,
				.green = 0,
				.blue = 186,
			},
			.pos = {
				.x = 492,
				.y = 1035,
			},
		},
		{ // light pink
			.color = {
				.red = 211,
				.green = 124,
				.blue = 170,
			},
			.pos = {
				.x = 516,
				.y = 1035,
			},
		},
		{ // light brown
			.color = {
				.red = 160,
				.green = 82,
				.blue = 45,
			},
			.pos = {
				.x = 540,
				.y = 1035,
			},
		},
		{ // black
			.color = {
				.red = 0,
				.green = 0,
				.blue = 0,
			},
			.pos = {
				.x = 300,
				.y = 1059,
			},
		},
		{ // dark grey
			.color = {
				.red = 76,
				.green = 76,
				.blue = 76,
			},
			.pos = {
				.x = 324,
				.y = 1059,
			},
		},
		{ // dark red
			.color = {
				.red = 116,
				.green = 11,
				.blue = 7,
			},
			.pos = {
				.x = 348,
				.y = 1059,
			},
		},
		{ // dark orange
			.color = {
				.red = 194,
				.green = 56,
				.blue = 0,
			},
			.pos = {
				.x = 372,
				.y = 1059,
			},
		},
		{ // dark yellow
			.color = {
				.red = 232,
				.green = 162,
				.blue = 0,
			},
			.pos = {
				.x = 396,
				.y = 1059,
			},
		},
		{ // dark green
			.color = {
				.red = 0,
				.green = 85,
				.blue = 16,
			},
			.pos = {
				.x = 420,
				.y = 1059,
			},
		},
		{ // dark blue
			.color = {
				.red = 0,
				.green = 86,
				.blue = 158,
			},
			.pos = {
				.x = 444,
				.y = 1059,
			},
		},
		{ // dark navy blue
			.color = {
				.red = 14,
				.green = 8,
				.blue = 101,
			},
			.pos = {
				.x = 468,
				.y = 1059,
			},
		},
		{ // dark purple
			.color = {
				.red = 85,
				.green = 0,
				.blue = 105,
			},
			.pos = {
				.x = 492,
				.y = 1059,
			},
		},
		{ // dark pink
			.color = {
				.red = 167,
				.green = 85,
				.blue = 116,
			},
			.pos = {
				.x = 516,
				.y = 1059,
			},
		},
		{ // dark brown
			.color = {
				.red = 99,
				.green = 48,
				.blue = 13,
			},
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

	struct color png_col; 
	int pix_x = 0;
	int pix_y = 0;

	bool clicked = false;
	while (drawer.pos.y < drawer.end.y) {
		while (drawer.pos.x < drawer.end.x) {

			if (process_png_file(pix_x, pix_y, &png_col)) {

				int closest_color = find_closest_color(png_col);

				if (drawer.current_color != closest_color) {
					drawer.current_color = closest_color; 
					if (clicked) {
						release();
						clicked = 0;
					}

					move_mouse(drawer.palette[drawer.current_color].pos.x, drawer.palette[drawer.current_color].pos.y);
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
			

			pix_x += 2;
			drawer.pos.x += 2;
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

int find_closest_color(struct color png_col)
{
	int ret = 0;

	double min_diff= sqrt((double)
				(
						(((png_col.red - drawer.palette[0].color.red) * (png_col.red - drawer.palette[0].color.red)) * 2) +
						(((png_col.green - drawer.palette[0].color.green) * (png_col.green - drawer.palette[0].color.green)) * 4) +
						(((png_col.blue - drawer.palette[0].color.blue) * (png_col.blue - drawer.palette[0].color.blue)) * 3)
				)
			);
	double tmp_diff;
	for (int i = 1; i < TOT_COLORS; i++) {
		tmp_diff = sqrt((double)
					(
						(((png_col.red - drawer.palette[i].color.red) * (png_col.red - drawer.palette[i].color.red)) * 2) +
						(((png_col.green - drawer.palette[i].color.green) * (png_col.green - drawer.palette[i].color.green)) * 4) +
						(((png_col.blue - drawer.palette[i].color.blue) * (png_col.blue - drawer.palette[i].color.blue)) * 3)
					)
				);

		if (tmp_diff < min_diff) {
			min_diff = tmp_diff;
			ret = i;
		}
	}

	return ret;
}
