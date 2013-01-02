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

typedef struct {
	Bitmap fb;
	uint width, height;
} Console;

extern Console console;

static inline void init_console() {
	//To do: remove magic constants
	console.fb = get_framebuffer(720, 480);
	console.width = console.fb.width / FONT_WIDTH;
	console.height = console.fb.height / FONT_HEIGHT;
}

#endif
