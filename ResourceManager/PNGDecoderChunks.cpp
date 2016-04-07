#include "PNGDecoder.h"

#define ChunkNametoUINT(s1, s2, s3, s4) ((s1<<24) | (s2<<16) | (s3<<8) | (s4))

bool IHDRChunk(unsigned char* buf, unsigned int buf_len, IHDR* ihdr){
	d2i temp = {};

	temp.c[3] = buf[8]; temp.c[2] = buf[9]; temp.c[1] = buf[10]; temp.c[0] = buf[11];
	ihdr->width = temp.i;

	temp.c[3] = buf[12]; temp.c[2] = buf[13]; temp.c[1] = buf[14]; temp.c[0] = buf[15];
	ihdr->height= temp.i;

	ihdr->bit_depth      = buf[16];
	ihdr->color_type     = buf[17];
	ihdr->compress_type  = buf[18];
	ihdr->filter_type    = buf[19];
	ihdr->interlace_type = buf[20];

	return CRC32(buf, buf_len);
}

#include <Windows.h>

bool Adler32(unsigned char* buf, unsigned int st_pos, unsigned int buf_len, unsigned int check_value){
	unsigned int a = 1;
	unsigned int b = 0;

	unsigned int adler = 0;

	for(int i = st_pos ; i<buf_len ; ++i){
		a = (a+buf[i]) % 65521;
		b = (a+b) % 65521;
	}

	adler = (b<<16) + a;

	if(adler != check_value){
		char str[256] = "";
		wsprintfA(str, "%08X\n%08X\n%08X\n%08X", adler, check_value, a, b);
		::MessageBoxA(NULL, str, "adler32 error", MB_OK);
		return false;
	}
	
	return true;
}

bool IDATChunk(unsigned char* buf, unsigned int buf_len, IHDR* ihdr, CMFnFLG* cnf, unsigned int** g_buf, unsigned int* g_pos){
	if((*g_buf) == 0x00){return false;}
	if(ihdr == 0x00){return false;}

	int i = 8;
	
	if((*cnf).s == 0){
		(*cnf).c[1] = buf[8];
		(*cnf).c[0] = buf[9];
		if(((*cnf).s%31) != 0){
			::MessageBoxA(NULL, "no equel compress header", "PNG error", MB_OK);
			return false;
		}
		i += 2;
	}

	if(((*cnf).c[0] & 32) != 0){
		i += 4;
	}

	unsigned int st_pos = *g_pos;

	bool bit[8] = {};

	//for(int j = 7 ; j>=0 ; --j){
	for(int j = 0 ; j<8 ; ++j){
		bit[j] = ((buf[i])>>j)&1;
	}

	if(bit[0] == 0){
		::MessageBoxA(NULL, "Last Block", "PNG", MB_OK);
	}
	else{
		::MessageBoxA(NULL, "Block", "PNG", MB_OK);
	}
	
	switch(bit[2]<<1 | bit[1]){
	case 0:
		{
			i += 4;
			d2i color = {};
			for( ; i<(buf_len-8) ; i+=1, ++(*g_pos)){
				color.c[3] = 0xFF;
				color.c[2] = buf[i];
				color.c[1] = buf[i];
				color.c[0] = buf[i];
				(*g_buf)[*g_pos] = color.i;
				if(*g_pos >= ihdr->width * ihdr->height){
					break;
				}
				if((*g_pos)%ihdr->width == (ihdr->width-1)){
					i += (ihdr->width%4 == 0)?0:4-(ihdr->width%4);
				}
			}
		}
		break;
	case 1:
		::MessageBoxA(NULL, "Fixed Huffman", "PNG", MB_OK);
		break;
	case 2:
		::MessageBoxA(NULL, "Dynamic Huffman", "PNG", MB_OK);
		break;
	case 3:
		::MessageBoxA(NULL, "Error", "PNG", MB_OK);
		break;
	}
	
	/*if(!Adler32((*g_buf), st_pos, (*g_pos)-st_pos, 
		(buf[buf_len-8]<<24) | (buf[buf_len-7]<<16) | (buf[buf_len-6]<<8) | buf[buf_len-5])){
		return false;
	}*/

	return CRC32(buf, buf_len);
}

bool ChunksAnalyzer(unsigned char* buf, int* pos, IHDR* ihdr,
					unsigned int* width, unsigned int* height, unsigned int** g_buf){
	
	d2i len = {};
	
	len.c[3] = buf[(*pos)-4];
	len.c[2] = buf[(*pos)-3];
	len.c[1] = buf[(*pos)-2];
	len.c[0] = buf[(*pos)-1];

	d2i chunk = {};

	chunk.c[3] = buf[(*pos)];
	chunk.c[2] = buf[(*pos)+1];
	chunk.c[1] = buf[(*pos)+2];
	chunk.c[0] = buf[(*pos)+3];

	unsigned char* t_buf = new unsigned char[12+len.i];
	for(int i = 0 ; i<(12+len.i) ; ++i){
		t_buf[i] = buf[((*pos)-4)+i];
	}
	bool b = false;
	switch(chunk.i){
	case ChunkNametoUINT('I','H','D','R'):
		b = IHDRChunk(t_buf, 12+len.i, ihdr);
		if(b){
			*width = ihdr->width;
			*height = ihdr->height;
			if((*g_buf) != 0x00){
				delete [] (*g_buf);
				(*g_buf) = 0x00;
			}
			*g_buf = new unsigned int[(*width)*(*height)];
			memset((*g_buf), 0xCD, sizeof(unsigned int)*(*width)*(*height));
		}
		break;
	case ChunkNametoUINT('I','D','A','T'):
		{
			CMFnFLG cnf = {};
			unsigned int g_pos = 0;
			while(1){
				b = IDATChunk(t_buf, 12+len.i, ihdr, &cnf, g_buf, &g_pos);
				if(b == false){break;}
				chunk.c[3] = buf[(*pos)+len.i+12];
				chunk.c[2] = buf[(*pos)+len.i+12+1];
				chunk.c[1] = buf[(*pos)+len.i+12+2];
				chunk.c[0] = buf[(*pos)+len.i+12+3];
				if(chunk.i == ChunkNametoUINT('I','D','A','T')){
					delete [] t_buf;
					(*pos) += (len.i+12);

					len.c[3] = buf[(*pos)-4];
					len.c[2] = buf[(*pos)-3];
					len.c[1] = buf[(*pos)-2];
					len.c[0] = buf[(*pos)-1];

					t_buf = new unsigned char[12+len.i];
					for(int i = 0 ; i<(12+len.i) ; ++i){
						t_buf[i] = buf[((*pos)-4)+i];
					}
				}
				else{
					break;
				}
			}
		}
		break;
	case ChunkNametoUINT('I','E','N','D'):
		b = CRC32(t_buf, 12+len.i);
		break;
	default:
		b = CRC32(t_buf, 12+len.i);
		break;
	}
	
	delete [] t_buf;
	
	if(!b){
		return false;
	}

	(*pos) += (len.i+8);
	return true;
}
