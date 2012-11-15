#include "gpio.h"

void gpio_set_output(uint pin) {
	if(pin >= 10 && pin <= 18) {
		uint* const ptr = GPIO_MODE + 1;
		const uint shift = (pin - 10) * 3;
		const uint mask = ~(0b111 << shift);
		*ptr = (*ptr & mask) | (1 << shift);
	}
}

void gpio_set(uint pin) {
	//pin / 32
	const uint offset = pin >> 5;
	//pin % 32
	const uint shift = pin & (32 - 1);
	GPIO_SET[offset] = 1 << shift;
}

void gpio_clear(uint pin) {
	//pin / 16
	const uint offset = pin >> 4;
	//pin % 16
	const uint shift = pin & (16 - 1);
	GPIO_CLEAR[offset] = 1 << shift; 
}
