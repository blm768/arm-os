#include <stddef.h>

#include "platform/current/memdef.h"

#define SERIAL_BASE IO_BASE
#define SERIAL_OUT (*(char*)(SERIAL_BASE))
#define SERIAL_FLAGS (*(uint64_t*)(SERIAL_BASE + 0x18))
#define SERIAL_BUFFER_FULL (1 << 5)

void write_char(char c) {
	//Wait for the serial buffer to clear.	
	while(SERIAL_FLAGS & SERIAL_BUFFER_FULL) {}
	//Write the character
	SERIAL_OUT = c;
}

void write(char* str) {
	char c = *str;
	while(c != '\0') {
		write_char(c);
		++str;
		c = *str;
	}
}

int driver_main(int argc, char** argv) {
	write("Testing!");
	return 0;
}

