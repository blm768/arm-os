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
	send_message(1, (int)&fb);
	int status = recv_message(1);
	if(status == 0) {
		gpio_clear(16);
		*(char*)fb.buffer = 255;
	}
}
