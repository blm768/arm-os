#ifndef _FONT_H
#define _FONT_H

#include "common.h"
#include "graphics.h"

#define FONT_WIDTH 16
#define FONT_HEIGHT 16

typedef ubyte FontTile[FONT_HEIGHT * FONT_WIDTH * sizeof(color_rgb)];

extern FontTile font_tiles[];

#endif
