#pragma once

#include <X11/Xlib.h>

#define VERSION "v0.1"

enum state {
	SLEEPING, IDLE,
	N, S, E, W,
	NW, NE, SW, SE,
	TALKING, HAPPY,
};

struct pet {
	Window window;
	Bool chasing;
	Bool frozen;
	enum state state;
	char*  name;
	char*  message;
	int    x;
	int    y;
} pet;

struct mouse {
	int    x;
	int    y;
} mouse;

struct bind {
	KeySym sym;
	unsigned long mask;
} bind;
