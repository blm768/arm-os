#include "string.h"

char digit_to_char(uint digit, uint base) {
	if(base <= 10) {
		return '0' + digit;
	} else if(base == 16) {
		return (digit < 10) ? ('0' + digit) : ('A' + (digit - 10));
	} else {
		return '?';
	}
}
