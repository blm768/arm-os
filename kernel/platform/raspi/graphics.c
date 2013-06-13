#include "graphics.h"
#include "math.h"
#include "memory.h"

#define V_OFFSET 10

Bitmap get_framebuffer(size_t width, size_t height) {
	FramebufferInfo fb = {
		width - 2 * V_OFFSET, height - 2 * V_OFFSET,
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
		bmp.data = phys_to_virt(fb.buffer);
	}
	return bmp;
}

void blit(Bitmap src, Bitmap dest, uint x, uint y) {
	uint wmin = MIN(src.width, (uint)(dest.width - x));
	uint hmin = MIN(src.height, (uint)(dest.height - y));
	
	for(size_t i = 0; i < hmin; ++i) {
		//To do: use memcpy?
		byte_copy(dest.data + (x + (y + i) * dest.width), src.data + (i * src.width), wmin * sizeof(color_rgb));
	}
}
