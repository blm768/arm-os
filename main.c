#include "gpio.h"

/*FramebufferInfo fb = {
	1024, 768,
	1024, 768,
	0, 24,
	0, 0};
*/

void kmain() {
	/*send_message(1, (int)&fb);
	int status = recv_message(1);
	*(char*)fb.buffer = 255;
	error();*/
	gpio_set_output(16);
	gpio_set(16);
	error(20);
	while(1) {}
}