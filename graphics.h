#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "common.h"

typedef ubyte color_rgb[3];
typedef ubyte color_rgba[4];

typedef struct {
	int width, height;
	int vWidth, vHeight;
	volatile int pitch;
	int depth;
	int x, y;
	volatile color_rgb* buffer;
	uint size;
} __attribute__((__aligned__(16))) FramebufferInfo;

typedef struct {
	uint box: 4;
	uint code: 28;
} Message;

#define MAIL_RECV   (*(volatile Message*)0x2000B880)
#define MAIL_SEND   (*(volatile uint*)0x2000B8A0)
#define MAIL_STATUS (*(volatile uint*)0x2000B898)

static inline volatile int get_send_status() {
	return MAIL_STATUS & (1 << 31);
};

static inline void send_message(int mBox, int msg) {
	while(get_send_status()) {}
	MAIL_SEND = mBox | msg;
}

static inline volatile int get_recv_status() {
	return MAIL_STATUS & (1 << 29);
}

static inline volatile Message recv_message(int mBox) {
	while(get_recv_status()) {}
	//To do: check that this is the right mailbox.
	Message msg = MAIL_RECV;
	while(msg.box != mBox) {
		while(get_recv_status()) {}
		msg = MAIL_RECV;
	}
	return MAIL_RECV;
}

#endif
