#ifndef _STRING_H
#define _STRING_H

#include "common.h"

//Much like strncpy, but the terminating null is always included
//The destination buffer should contain space for at least len + 1 characters.
void string_copy(char* dest, char* src, size_t len);

char digit_to_char(uint digit);

void uint_to_str(uint value, uint base, char* buf);

#endif
