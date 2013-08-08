#ifndef _PLATFORM_CONSOLE_H
#define _PLATFORM_CONSOLE_H

#include "common.h"

#include "cpu/current/memdef.h"
#include "string.h"

#define SERIAL_BASE IO_BASE
#define SERIAL_OUT (*(char*)(SERIAL_BASE))
#define SERIAL_FLAGS (*(ulong*)(SERIAL_BASE + 0x18))
#define SERIAL_BUFFER_FULL (1 << 5)

static inline bool init_console() {
	return true;
}

static inline void write_char(char c) {
	//Wait for the serial buffer to clear.	
	while(SERIAL_FLAGS & SERIAL_BUFFER_FULL) {}
	//Write the character
	SERIAL_OUT = c;
}

static inline void write_newline() {
	write_char('\n');	
}

#endif
