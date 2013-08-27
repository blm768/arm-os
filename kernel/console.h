#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "platform/current/console.h"

void write(char* str);

static inline void writeln(char* str) {
	write(str);
	write_newline();
}

static inline void write_uint(size_t value) {
	//TODO: make this independent of word size!
	char buf[16];
	uint_to_str(value, 10, buf);
	write(buf);
}

static inline void write_ptr(void* value) {
	//TODO: make this independent of word size!
	//TODO: add leading zeroes.
	char buf[16];
	uint_to_str((size_t)value, 16, buf);
	write(buf);
}

static inline void die(char* msg) {
	//To do: check if console is initialized.
	writeln("Fatal error:");
	writeln(msg);
	while(true) {}
}

#endif

