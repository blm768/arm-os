#ifndef _MATH_H
#define _MATH_H

//To do: make safer?
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
	uint quotient, remainder;
} UintDivMod;

//Meant only for use with compile-time constants; use the function forms for non-constants.
#define ROUND_DOWN(val, mul) ((val) & ~((mul) - 1))
#define ROUND_UP(val, mul)   (ROUND_DOWN(val, mul) + (((val) & ((mul) - 1)) ? (mul) : 0))

static inline size_t p2_round_down(size_t val, size_t mul) {
	return val & ~(mul - 1);
}

static inline size_t p2_round_up(size_t val, size_t mul) {
	size_t result =  val & ~(mul - 1);
	if(val & mul) {
		result += mul;
	}
	return result;
}

static inline size_t lsr_round_up(size_t val, size_t pow) {
	size_t result = val >> pow;
	if(val & ((1 << pow) - 1)) {
		result += 1;
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
