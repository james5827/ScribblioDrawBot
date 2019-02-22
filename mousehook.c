#include "mousehook.h"

static Display *dpy;
static Window root;

void init_mousehook(void)
{
    	dpy = XOpenDisplay(NULL);
    	root = XDefaultRootWindow(dpy);
}

void destroy_mousehook(void)
{
	XCloseDisplay(dpy);
}

void get_coords(int *x, int *y)
{
	XEvent event;
    	int button;
    	XGrabPointer(dpy, root, False, ButtonPressMask, 
	GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

    	XSelectInput(dpy, root, ButtonPressMask) ;

	XNextEvent(dpy, &event);
	switch (event.type){
	case ButtonPress:
		switch (event.xbutton.button) {
		default:
		*x = event.xbutton.x;
		*y = event.xbutton.y;
		button=Button1;
		break;
		}
		break;
	    default:
		break;
	}

	if(button == Button1)
		printf("click at %d %d \n", *x, *y);
}

void move_mouse(int x, int y)
{
    	XWarpPointer(dpy, None, root, 0, 0, 0, 0, x, y);
	XFlush(dpy);
	usleep(100);
}

void click() 
{
	XEvent event;
	memset(&event, 0, sizeof(event));
	event.xbutton.button = Button1;
	event.xbutton.same_screen = True;
	event.xbutton.subwindow = DefaultRootWindow(dpy);

	while (event.xbutton.subwindow) {
	      event.xbutton.window = event.xbutton.subwindow;

	      XQueryPointer(dpy, event.xbutton.window,
		     &event.xbutton.root, &event.xbutton.subwindow,
		     &event.xbutton.x_root, &event.xbutton.y_root,
		     &event.xbutton.x, &event.xbutton.y,
		     &event.xbutton.state);
	}

	  event.type = ButtonPress;
	  if (XSendEvent(dpy, PointerWindow, True, ButtonPressMask, &event) == 0)
	    fprintf(stderr, "Error to send the event!\n");

	  XFlush(dpy);
	  usleep(3000);
}

void release()
{
	XEvent event;
	memset(&event, 0, sizeof(event));
	event.xbutton.button = Button1;
	event.xbutton.same_screen = True;
	event.xbutton.subwindow = DefaultRootWindow(dpy);

	while (event.xbutton.subwindow) {
	      event.xbutton.window = event.xbutton.subwindow;

	      XQueryPointer(dpy, event.xbutton.window,
		     &event.xbutton.root, &event.xbutton.subwindow,
		     &event.xbutton.x_root, &event.xbutton.y_root,
		     &event.xbutton.x, &event.xbutton.y,
		     &event.xbutton.state);
	}
	  event.type = ButtonRelease;
	  if (XSendEvent(dpy, PointerWindow, True, ButtonReleaseMask, &event) == 0)
	    fprintf (stderr, "Error to send the event!\n");

	  XFlush (dpy);
	  usleep(10000);
}
