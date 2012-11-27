#include "interrupt.h"

void c_irq_handler() {
	gpio_set(16);
}
