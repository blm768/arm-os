#ifndef _PLATFORM_CONSOLE_H
#define _PLATFORM_CONSOLE_H

#include "common.h"

#include "string.h"

#define SERIAL_BASE io_base

static inline bool init_console() {
	return true;
}

static inline void write_char(char c) {
	
}

static inline void write_newline() {
	
}

#endif
