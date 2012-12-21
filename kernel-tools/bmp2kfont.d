/+
	Converts BMP files to a font tile header
	
	This code is very rough and should be used with caution.
+/

import std.c.stdlib;
import std.stdio;

void usage_error() {
	stderr.writeln("Usage: bmp2kfont file [width height]");
	exit(1);
}

void format_enforce(bool pred) {
	if(!pred) {
		stderr.writeln("Invalid or unsupported file format");
		exit(1);
	}
}

align(2) struct BmpHeader {
	align(2):
	char[2] type;
	uint size;
	ushort[2] reserved;
	uint dataOffset;
	
	void validate() {
		format_enforce(type == "BM");
	}
}

struct DibHeader {
	align(2):
	uint size;
	uint width;
	uint height;
	ushort colorPlanes;
	ushort bpp;
	uint compression;
	uint dataSize;
	uint hres;
	uint vres;
	uint paletteColors;
	uint importantColors;
	
	void validate() {
		format_enforce(size >= 40);
		format_enforce(bpp == 24 || bpp == 32);
		format_enforce(compression == 0);
		format_enforce(paletteColors == 0);
	}
}

T rawRead(T)(File f) {
	T value;
	f.rawRead((&value)[0 .. 1]);
	return value;
}

T rawReadAndReset(T)(File f) {
	auto pos = f.tell();
	rawRead!T(f);
	f.seek(pos);
}

alias ubyte[3] Pixel;

int main(string[] args) {
	if(args.length < 2) {
		usage_error();
	}
	string filename = args[1];
	auto f = File(filename);
	auto bmpHeader = rawRead!BmpHeader(f);
	bmpHeader.validate();
	auto dibHeader = rawRead!DibHeader(f);
	writeln(f.tell());
	writeln(BmpHeader.sizeof);
	writeln(dibHeader);
	dibHeader.validate();
	f.seek(dibHeader.size - DibHeader.sizeof, SEEK_CUR);
	writeln(f.tell());
	writeln(bmpHeader.dataOffset);
	size_t pixelSize = (dibHeader.bpp == 24) ? 3 : 4;
	ubyte[] data = new ubyte[dibHeader.dataSize];
	f.rawRead(data);
	const width = dibHeader.width;
	const height = dibHeader.height;
	//Row width is rounded up to a multiple of 4.
	size_t rowSize = width * pixelSize;
	if(rowSize & 0x3) {
		rowSize += 1;
	}
	rowSize &= ~0x3;
	auto pixels = new Pixel[][height];
	writeln(pixels.length);
	for(size_t i = 0; i < height; ++i) {
		Pixel[] row = pixels[height - 1 - i] = new Pixel[width];
		for(size_t j = 0; j < width; ++j) {
			size_t offset = i * rowSize + j * pixelSize;
			row[j][] = data[offset .. offset + pixelSize];
		}
	}
	writeln(pixels);
	return 0;
}
