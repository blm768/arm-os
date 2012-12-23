/+
	Converts BMP files to a font tile header
	
	This code is very rough and should be used with caution.
+/

import std.c.stdlib;
import std.conv;
import std.stdio;
import std.string;

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
	size_t tileWidth, tileHeight;
	if(args.length == 4) {
		tileWidth = args[2].to!size_t;
		tileHeight = args[3].to!size_t;
	} else {
		tileWidth = tileHeight = 8;
	}
	auto f = File(filename);
	auto bmpHeader = rawRead!BmpHeader(f);
	bmpHeader.validate();
	auto dibHeader = rawRead!DibHeader(f);
	dibHeader.validate();
	f.seek(dibHeader.size - DibHeader.sizeof, SEEK_CUR);
	size_t pixelSize = (dibHeader.bpp == 24) ? 3 : 4;
	ubyte[] data = new ubyte[dibHeader.dataSize];
	f.rawRead(data);
	const width = dibHeader.width;
	const height = dibHeader.height;
	//Row width is rounded up to a multiple of 4.
	size_t rowSize = width * pixelSize;                                                            
	if(rowSize & 0x3) {
		rowSize += 4;
	}
	rowSize &= ~0x3;
	auto pixels = new Pixel[][height];
	for(size_t i = 0; i < height; ++i) {
		Pixel[] row = pixels[height - 1 - i] = new Pixel[width];
		for(size_t j = 0; j < width; ++j) {
			size_t offset = i * rowSize + j * pixelSize;
			row[j][] = data[offset .. offset + pixelSize].reverse;
		}
	}
	
	size_t xTiles = width / tileWidth;
	size_t yTiles = height / tileHeight;
	
	File f2 = File("font.c", "w");
	f2.write(
`#include "font.h"

FontTile font_tiles[] = {
`);
	for(size_t ty = 0; ty < yTiles; ++ty) {
		const yStart = ty * tileHeight;
		for(size_t tx = 0; tx < xTiles; ++tx) {
			const xStart = tx * tileWidth;
			f2.writeln("\t{");
			for(size_t y = yStart; y < yStart + tileHeight; ++y) {
				auto row = pixels[y][xStart .. xStart + tileWidth];
				f2.write("\t\t");
				foreach(Pixel p; row) {
					foreach(ubyte v; p) {
						f2.write(v, ",");
					}
				}
				f2.writeln();
			}
			f2.writeln("\t},");
		}
	}
	f2.writeln(`};`);
	return 0;
}
