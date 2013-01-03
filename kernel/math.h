#ifndef _MATH_H
#define _MATH_H

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
	uint quotient, remainder;
} UintDivMod;

//To do: use more efficient algorithm?
static inline UintDivMod uintDivMod(uint a, uint b) {
	UintDivMod div = {0, 0};
	//To do: better error handling?
	if(b == 0) {
		return div;
	}
	size_t i = sizeof(uint) * 8;
	while(i > 0) {
		--i;
		div.remainder <<= 1;
		uint mask = 1 << i;
		div.remainder = (div.remainder & ~0x1) | ((a & mask) >> i);
		if(div.remainder >= b) {
			div.remainder -= b;
			div.quotient |= mask;
		}
	}
	return div;
}

#endif
