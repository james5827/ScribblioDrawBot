#ifndef PNG_READER
#define PNG_READER

#include <stdlib.h>
#include <stdio.h>
#include <png.h>

void read_png_file(char *filename);
int process_png_file(int, int);
void free_png(void);

#endif
