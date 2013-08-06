#ifndef _TEXTCONS_H
#define _TEXTCONS_H

#include "common.h"

#include "font.h"
#include "platform/current/graphics.h"
#include "string.h"

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
	//Cursor position
	uint cx, cy;
} Console;

extern Console console;

static inline bool init_console() {
	//To do: remove magic constants
	console.fb = get_framebuffer(720, 480);
	if(!console.fb.data) {
		return false;
	}
	console.width = console.fb.width / FONT_WIDTH;
	console.height = console.fb.height / FONT_HEIGHT;
	console.cx = 0;
	console.cy = 0;
	return true;
}

static inline void write_char(char c) {
	if(console.fb.data) {
		blit(glyph_for_char(c), console.fb, console.cx * FONT_WIDTH, console.cy * FONT_HEIGHT);
		++console.cx;
		if(console.cx >= console.width) {
			console.cx = 0;
			if(console.cy < console.height - 1) {
				++console.cy;
			}
		}
	}
}

static inline void write_newline() {
	if(console.fb.data) {
		console.cx = 0;
		if(console.cy < console.height - 1) {
			++console.cy;
		} else {
			//Note: this is only guaranteed to work with the version of memcpy in common.h. It could also break if the resolution is extremely low.
			size_t font_row_size = FONT_HEIGHT * console.fb.width;
			memcpy(console.fb.data, console.fb.data + font_row_size, font_row_size * (console.height - 1) * sizeof(color_rgb));
		}
	}
}

void write(char* str);

static inline void writeln(char* str) {
	write(str);
	write_newline();
}

static inline void write_uint(uint value) {
	char buf[16];
	uint_to_str(value, 10, buf);
	write(buf);
}

static inline void write_ptr(void* value) {
	char buf[16];
	//To do: make this independent of word size!
	uint_to_str((uint)value, 16, buf);
	write(buf);
}

static inline void die(char* msg) {
	//To do: more reliable check?
	if(console.width > 0) {
		writeln("Fatal error:");
		writeln(msg);
	}
	while(true) {}
}

#endif
