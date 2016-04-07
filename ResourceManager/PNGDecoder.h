#pragma once

#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys\types.h>
#include <sys\stat.h>

#include <string.h>

struct IHDR{
	unsigned int width;
	unsigned int height;
	unsigned char bit_depth;
	unsigned char color_type;
	unsigned char compress_type;
	unsigned char filter_type;
	unsigned char interlace_type;
};

union CMFnFLG{
	unsigned char c[2];
	unsigned short s;
};

union d2i{
	unsigned char c[4];
	unsigned int i;
};

bool CRC32(unsigned char* buf, unsigned int len);

//bool IHDRChunk(unsigned char* buf, IHDR* ihdr);

bool ChunksAnalyzer(unsigned char* buf, int* pos, IHDR* ihdr,
					unsigned int* width, unsigned int* height, unsigned int** g_buf);