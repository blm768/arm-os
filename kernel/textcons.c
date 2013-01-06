#include "textcons.h"

Console console;

void write(char* str) {
	size_t i = 0;
	char c = str[0];
	while(c != '\0') {
		if(c == '\n') {
			write_newline();
		} else {
			write_char(c);
		}
		++i;
		c = str[i];
	}
}
