#ifndef _TEXTCONS_H
#define _TEXTCONS_H

#include "common.h"

#include "font.h"
#include "graphics.h"

static inline size_t glyph_index_for_char(char c) {
	if(c < '!') {
		return 0;
	}
	if(c > '~') {
		return '?' - '!' + 1;
	}
	return c - '!' + 1;
}

static inline Bitmap glyph_for_char(char c) {
	Bitmap b = {FONT_WIDTH, FONT_HEIGHT, (color_rgb*)(font_tiles + glyph_index_for_char(c))};
	return b;
}

#endif
