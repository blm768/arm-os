#ifndef _MATH_H
#define _MATH_H

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
	uint quotient, remainder;
} UintDivMod;

static inline size_t round_down(size_t val, size_t mul) {
	return val & (~mul);
}

static inline size_t round_up(size_t val, size_t mul) {
	size_t result =  val & (~mul);
	if(val & mul) {
		result += mul;
	}
	return result;
}

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
