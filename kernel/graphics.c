#include "graphics.h"
#include "math.h"

Bitmap get_framebuffer(size_t width, size_t height) {
	FramebufferInfo fb = {
		width, height,
		width, height,
		0, 24,
		0, 0,
		NULL, 0};
	send_message(1, (uint)(&fb) + 0x40000000);
	uint status = recv_message(1);
	Bitmap bmp = {
		width,
		height,
		NULL};
	if(status == 0) {
		//while(!fb.buffer) {}
		bmp.data = fb.buffer - 0x40000000;
	}
	return bmp;
}

void blit(Bitmap src, Bitmap dest, uint x, uint y) {
	uint wmin = MIN(src.width, (uint)(dest.width - x));
	uint hmin = MIN(src.height, (uint)(dest.height - y));
	
	for(size_t i = 0; i < hmin; ++i) {
		byte_copy(dest.data + (x + (y + i) * dest.width), src.data + (i * src.width), wmin * sizeof(color_rgb));
	}
}
