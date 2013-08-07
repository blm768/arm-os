#ifndef _CONSOLE_H
#define _CONSOLE_H

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

