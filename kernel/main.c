#include "common.h"

#include "atags.h"
#include "gpio.h"
#include "textcons.h"
#include "interrupt.h"
#include "timer.h"

//To do: peripheral read/write barriers!
	
void kmain(uint r0, uint system_type, AtagHeader* atags) {
	gpio_set_output(16);
	gpio_set(16);
	//process_atags(atags);
	//interrupt_init();
	//enable_irqs();
	//enable_irq(cpu_timer);
	Bitmap fb = get_framebuffer(720, 480);
	if(fb.data) {
		color_rgb* buffer = fb.data;
		for(size_t x = 0; x < fb.width; ++x) {
			for(size_t y = 0; y < fb.height; ++y) {
				color_rgb* ptr = buffer + (y * fb.width + x);
				(*ptr)[0] = 255;
				(*ptr)[1] = 255;
				(*ptr)[2] = 255;
			}
		}
		size_t a = 3;
		if(fb.height == 480)
			gpio_clear(16);
		blit(glyph_for_char('A'), fb, 80, 80);
	}
}
