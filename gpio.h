#ifndef _GPIO_H
#define _GPIO_H

#include "common.h"

#define GPIO_MODE  ((uint*)0x20200000)
#define GPIO_SET   ((uint*)0x2020001C)
#define GPIO_CLEAR ((uint*)0x20200028)

static inline void gpio_set_output(uint pin) {
	if(pin >= 10 && pin <= 18) {
		uint* const ptr = GPIO_MODE + 1;
		const uint shift = (pin - 10) << 1;
		const uint mask = ~(3 << shift);
		*ptr = *ptr & mask | (1 << shift);
	}
}

static inline void gpio_set(uint pin) {
	//pin / 16
	const uint offset = pin >> 4;
	//pin % 16
	const uint shift = pin & (16 - 1);
	GPIO_SET[offset] = 1 << shift; 
}

static inline void gpio_clear(uint pin) {
	//pin / 16
	const uint offset = pin >> 4;
	//pin % 16
	const uint shift = pin & (16 - 1);
	GPIO_CLEAR[offset] = 1 << shift; 
}

#endif