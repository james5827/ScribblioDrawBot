#ifndef PNG_READER
#define PNG_READER

#include <stdlib.h>
#include <stdio.h>
#include <png.h>
#include <stdbool.h>
#include "driver.h"

void read_png_file(char *filename);
bool process_png_file(int, int, struct color *png_col);
void free_png(void);

#endif
