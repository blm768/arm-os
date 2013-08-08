#include "console.h"

void write(char* str) {
	for(char c = *str; c != '\0'; ++str) {
		write_char(*str);
	}
}

