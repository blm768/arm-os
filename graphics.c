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
		NULL,
		width,
		height};
	if(status == 0) {
		while(!fb.buffer) {}
		bmp.data = fb.buffer - 0x40000000;
	}
	return bmp;
}

void blit(Bitmap src, Bitmap dest, uint x, uint y) {
	uint wmin = MIN(src.width, (dest.width - x));
	uint hmin = MIN(src.height, (dest.height - y));
	
	for(size_t i = 0; i < hmin; ++i) {
		for(size_t j = 0; j < wmin; ++j) {
			dest.data[x + j + i * dest.width] = src.data[j + i * src.width];
		}
	}
}
