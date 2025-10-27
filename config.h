#pragma once

#include <X11/Xutil.h>

#include "xpet.h"

#define PET_SMOOTH  200    /* smoothening factor for window movement */
#define PET_REFRESH 32     /* ms between movement updates (16ms=60fps) */

struct bind bindings[] = {
	{XK_f, Mod1Mask},      /* call */
	{XK_q, Mod1Mask},      /* quit */
};
