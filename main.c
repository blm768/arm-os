#include "graphics.h"

FramebufferInfo fb = {
	1024, 768,
	1024, 768,
	0, 24,
	0, 0};
	
extern void error();

void main() {
	send_message(1, (int)&fb);
	*(char*)fb.buffer = 255;
	int status = recv_message(1);
	while(1) {}
}