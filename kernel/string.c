#include "string.h"

#include "math.h"

void string_copy(char* dest, char* src, size_t len) {
	size_t i = 0;
	while(i < len) {
		char c = src[i];
		dest[i] = c;
		if(c == '\0') {
			return;
		}
		++i;
	}
	dest[i] = '\0';
}

char digit_to_char(uint digit) {
	return (digit < 10) ? ('0' + digit) : ('A' + (digit - 10));
}

void uint_to_str(uint value, uint base, char* buf) {
	if(value == 0) {
		string_copy(buf, "0", 1);
		return;
	}
	
	//To do: adjust size?
	char buf2[16];
	
	size_t len = 0;
	while(value > 0) {
		UintDivMod div = uintDivMod(value, base);
		buf2[len] = digit_to_char(div.remainder);
		++len;
		value = div.quotient;
	}
	
	for(size_t i = 0; i < len; ++i) {
		buf[i] = buf2[len - 1 - i];
	}
	buf[len] = '\0';
}

