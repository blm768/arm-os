#include "console.h"

void write(char* str) {
	char c = *str;
	while(c != '\0') {
		write_char(c);
		++str;
		c = *str;
	}
}

