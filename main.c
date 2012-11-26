#include "gpio.h"
#include "graphics.h"
#include "interrupt.h"
#include "timer.h"

FramebufferInfo fb = {
	1024, 768,
	1024, 768,
	0, 24,
	0, 0};


void kmain() {
	irq_init();
	gpio_set_output(16);
	gpio_clear(16);
	send_message(1, (int)(&fb + 0x40000000));
	int status = recv_message(1).code;
	if(status == 0) {
		gpio_set(16);
		while(!fb.buffer) {}
		gpio_clear(16);
		for(size_t x = 0; x < fb.width; ++x) {
			for(size_t y = 0; y < fb.height; ++y) {
				color_rgb* ptr = (color_rgb*)fb.buffer + (y * fb.width + x);
				(*ptr)[0] = y;
				(*ptr)[1] = y;
				(*ptr)[2] = y;
			}
		}
	}
}
