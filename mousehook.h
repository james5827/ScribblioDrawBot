#ifndef MOUSE_HOOK
#define MOUSE_HOOK

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init_mousehook(void);
void destroy_mousehook(void);
void get_coords(int *, int *);
void click();
void move_mouse(int, int);
void release();

#endif
