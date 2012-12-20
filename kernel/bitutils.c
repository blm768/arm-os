#include "bitutils.h"

/*
 *	Sets the nth bit of the memory pointed to by p, first clearing the word that contains that bit
 */
void clear_word_and_set_bit(uint* p, uint n) {
	uint offset = n >> 5;
	uint shift = n % 32;
	*(p + offset) = 1 << shift;
}