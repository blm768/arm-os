#include "gpio.h"

void gpio_set_output(uint pin) {
	const uint offset = pin / 10;
	const uint shift = (pin - 10 * offset) * 3;
	const uint mask = ~(0b111 << shift);
	uint* const ptr = GPIO_MODE + offset;
	*ptr = (*ptr & mask) | (1 << shift);
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
	const uint offset = pin >> 5;
	//pin % 16
	const uint shift = pin & (32 - 1);
	GPIO_CLEAR[offset] = 1 << shift;
}
