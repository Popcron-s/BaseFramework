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

inline unsigned int bit_shift(unsigned char* buf, int* buf_pos, bool* bit, int* bit_pos, int shift){
	if(shift > 32){return 0;}
	unsigned int value = 0;
	for(int i = 0 ; i<shift ; ++i){
		if(*bit_pos == 8){
			for(int j = 0 ; j<8 ; ++j){
				bit[j] = ((buf[*buf_pos])>>j)&1;
			}
			++(*buf_pos);
			(*bit_pos) = 0;
		}
		//value <<= 1;
		value |= bit[*bit_pos]<<i;
		++(*bit_pos);
	}/*
	char str[256] = {};
	wsprintfA(str, "%d", value);
	::MessageBoxA(NULL, str, "PNG", MB_OK);*/
	return value;
}

bool IDATChunk(unsigned char* buf, unsigned int buf_len, IHDR* ihdr, CMFnFLG* cnf, unsigned char* ud_buf, unsigned int* ud_pos){
	if(ud_buf == 0x00){return false;}
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

	bool bit[8] = {};
	int bit_pos = 8;

#define BIT_SHIFT(shift) bit_shift(buf, &i, bit, &bit_pos, shift)
	
	unsigned int st_pos = *ud_pos;
	while(1){

		bool last = false;

		if(BIT_SHIFT(1)){
			last = true;
		}
		
		switch(BIT_SHIFT(2)){
		case 0:
			{
				bit_pos = 8;
				if(buf_len < (i+8)){break;}
				int len = (buf[i+1])<<8 | (buf[i]);
				int nlen = ((buf[i+3])<<8 | (buf[i+2]))^0xFFFF;
				char str[256] = "";
				wsprintfA(str, "%d / %d", len, nlen);
				//::MessageBoxA(NULL,str,"",MB_OK);
				if( len != nlen ){
					::MessageBoxA(NULL,"","",MB_OK);
					return false;
				}
				i += 4;
				for(int j = 0 ; j<len && i<(buf_len-8) ; ++j, ++i, ++(*ud_pos)){
					ud_buf[*ud_pos] = buf[i];
				}
			}
			break;
		case 1:
			::MessageBoxA(NULL, "Fixed Huffman", "PNG", MB_OK);
			break;
		case 2:
			//Inflate(buf, (unsigned int*)&i, ud_buf, ud_pos);
			{
				::MessageBoxA(NULL, "Dynamic Huffman", "PNG", MB_OK);
				int HLIT = BIT_SHIFT(5) + 257;
				int HDIST = BIT_SHIFT(5) + 1;
				int HCLEN = BIT_SHIFT(4) + 4;

				unsigned char* CodeLength = new unsigned char[19];
				memset(CodeLength, 0x00, sizeof(unsigned char)*19);
				for(int clen = 0 ; clen<HCLEN ; ++clen){
					switch(clen){
					case  0: CodeLength[16] = BIT_SHIFT(3); break;
					case  1: CodeLength[17] = BIT_SHIFT(3); break;
					case  2: CodeLength[18] = BIT_SHIFT(3); break;
					case  3: CodeLength[ 0] = BIT_SHIFT(3); break;
					case  4: CodeLength[ 8] = BIT_SHIFT(3); break;
					case  5: CodeLength[ 7] = BIT_SHIFT(3); break;
					case  6: CodeLength[ 9] = BIT_SHIFT(3); break;
					case  7: CodeLength[ 6] = BIT_SHIFT(3); break;
					case  8: CodeLength[10] = BIT_SHIFT(3); break;
					case  9: CodeLength[ 5] = BIT_SHIFT(3); break;
					case 10: CodeLength[11] = BIT_SHIFT(3); break;
					case 11: CodeLength[ 4] = BIT_SHIFT(3); break;
					case 12: CodeLength[12] = BIT_SHIFT(3); break;
					case 13: CodeLength[ 3] = BIT_SHIFT(3); break;
					case 14: CodeLength[13] = BIT_SHIFT(3); break;
					case 15: CodeLength[ 2] = BIT_SHIFT(3); break;
					case 16: CodeLength[14] = BIT_SHIFT(3); break;
					case 17: CodeLength[ 1] = BIT_SHIFT(3); break;
					case 18: CodeLength[15] = BIT_SHIFT(3); break;
					}
					char str[256] = "";
					wsprintfA(str, "%d : %d", clen, CodeLength[i]);
					::MessageBoxA(NULL,str,"",MB_OK);
				}
				
				CodeLength[0] = 0;
				unsigned char* next_code = new unsigned char[17];
				for(int bits = 1, code = 0; bits <= 16; ++bits){
					code = (code + CodeLength[bits-1]) << 1;
					next_code[bits] = code;
				}
				unsigned int* code = new unsigned int[288];
				for(int n = 0 ; n<19 ; ++n){
					int len = CodeLength[n];
					if(len!=0){
						code[n] = next_code[len];
						++next_code[len];
					}
				}

				delete [] CodeLength;
				delete [] next_code;
				delete [] code;
			}
			break;
		case 3:
			::MessageBoxA(NULL, "Error", "PNG", MB_OK);
			break;
		}

		if(last){break;}
	}/*
	if(!Adler32(ud_buf, st_pos, (*ud_pos)-st_pos, 
		(buf[buf_len-8]<<24) | (buf[buf_len-7]<<16) | (buf[buf_len-6]<<8) | buf[buf_len-5])){
		return false;
	}*/

	return CRC32(buf, buf_len);
}

bool DrawGraphic(unsigned int* g_buf, unsigned char* ud_buf, unsigned int* palette, unsigned int size, unsigned int width, unsigned char color_type){
	switch(color_type){
	case 0:
		break;
	case 2:{
		int pos = 0;
		int i = 0;
		while(1){
			unsigned char filter = ud_buf[i];
			++i;

			switch(filter){
			case 0:
				for(int j = 0 ; j<width ; ++j){
					g_buf[pos] = (0xFF<<24) | (ud_buf[i+2]<<16) | (ud_buf[i+1]<<8) | ud_buf[i];
					i+=3;
					++pos;
				}
				break;
			case 1:
				g_buf[pos]  = (ud_buf[i  ] & 0xFF);
				g_buf[pos] |= (ud_buf[i+1] & 0xFF)<<8;
				g_buf[pos] |= (ud_buf[i+2] & 0xFF)<<16;
				g_buf[pos] |= 0xFF<<24;
				i+=3;
				++pos;
				for(int j = 1 ; j<width ; ++j){
					g_buf[pos]  = ((ud_buf[i  ] + (g_buf[pos-1]     & 0xFF)) & 0xFF);
					g_buf[pos] |= ((ud_buf[i+1] + (g_buf[pos-1]>>8  & 0xFF)) & 0xFF)<<8;
					g_buf[pos] |= ((ud_buf[i+2] + (g_buf[pos-1]>>16 & 0xFF)) & 0xFF)<<16;
					g_buf[pos] |= 0xFF<<24;
					i+=3;
					++pos;
				}
				break;
			case 2:
				if(pos < width){break;}
				for(int j = 0 ; j<width ; ++j){
					g_buf[pos]  = ((ud_buf[i  ] + (g_buf[pos-width]     & 0xFF)) & 0xFF);
					g_buf[pos] |= ((ud_buf[i+1] + (g_buf[pos-width]>>8  & 0xFF)) & 0xFF)<<8;
					g_buf[pos] |= ((ud_buf[i+2] + (g_buf[pos-width]>>16 & 0xFF)) & 0xFF)<<16;
					g_buf[pos] |= 0xFF<<24;
					i+=3;
					++pos;
				}
				break;
			case 3:
				if(pos < width){break;}
				g_buf[pos] = 0;
				for(int n = 0 ; n<3 ; ++n){
					unsigned char b = (g_buf[pos-width]>>(8*n) & 0xFF);
					g_buf[pos] |= (((ud_buf[i+n])+(b/2)) & 0xFF)<<(8*n);
				}
				g_buf[pos] |= 0xFF<<24;
				i+=3;
				++pos;
				for(int j = 1 ; j<width ; ++j){
					g_buf[pos] = 0;
					for(int n = 0 ; n<3 ; ++n){
						unsigned char a = (g_buf[pos-1]>>(8*n) & 0xFF);
						unsigned char b = (g_buf[pos-width]>>(8*n) & 0xFF);
						g_buf[pos] |= (((ud_buf[i+n])+((a+b)/2)) & 0xFF)<<(8*n);
					}
					g_buf[pos] |= 0xFF<<24;
					i+=3;
					++pos;
				}
				break;
			case 4:
				if(pos < width){break;}
				g_buf[pos] = 0;
				for(int n = 0 ; n<3 ; ++n){
					int a = 0;
					int b = (g_buf[pos-width]>>(8*n) & 0xFF);
					int c = 0;
					int p = a+b-c;
					int pa = abs(p-a), pb = abs(p-b), pc = abs(p-c);
					int pr = n;
					if(pa<=pb && pa<=pc){pr = a;}
					else if(pb<=pc){pr = b;}
					else{pr = c;}

					unsigned char t_buf = ud_buf[i]+pr;
					g_buf[pos] |= t_buf<<(8*n);
					++i;
				}
				g_buf[pos] |= 0xFF<<24;
				++pos;
				for(int j = 1 ; j<width ; ++j){
					g_buf[pos] = 0;
					for(int n = 0 ; n<3 ; ++n){
						int a = (g_buf[pos-1]>>(8*n) & 0xFF);
						int b = (g_buf[pos-width]>>(8*n) & 0xFF);
						int c = (g_buf[pos-width-1]>>(8*n) & 0xFF);
						int p = a+b-c;
						int pa = abs(p-a), pb = abs(p-b), pc = abs(p-c);
						int pr = n;
						if(pa<=pb && pa<=pc){pr = a;}
						else if(pb<=pc){pr = b;}
						else{pr = c;}

						unsigned char t_buf = ud_buf[i]+pr;
						g_buf[pos] |= t_buf<<(8*n);
						++i;
					}
					g_buf[pos] |= 0xFF<<24;
					++pos;
				}
				break;
			default:
				::MessageBoxA(NULL, "Error","Filter",MB_OK);
				break;
			}
			if(pos>=size){break;}
		}
	}
		break;
	case 3:
		if(palette == 0x00){return false;;}
		for(unsigned int i = 0 ; i<size ; ++i){
			g_buf[i] = palette[ud_buf[i]];
		}
		break;
	case 4:
		break;
	case 6:{
		int pos = 0;
		int i = 0;
		while(1){
			unsigned char filter = ud_buf[i];
			++i;

			switch(filter){
			case 0:
				for(int j = 0 ; j<width ; ++j){
					g_buf[pos] = (ud_buf[i+3]<<24) | (ud_buf[i+2]<<16) | (ud_buf[i+1]<<8) | ud_buf[i];
					i+=4;
					++pos;
				}
				break;
			case 1:
				g_buf[pos]  = (ud_buf[i  ] & 0xFF);
				g_buf[pos] |= (ud_buf[i+1] & 0xFF)<<8;
				g_buf[pos] |= (ud_buf[i+2] & 0xFF)<<16;
				g_buf[pos] |= (ud_buf[i+3] & 0xFF)<<24;
				i+=4;
				++pos;
				for(int j = 1 ; j<width ; ++j){
					g_buf[pos]  = ((ud_buf[i  ] + (g_buf[pos-1]     & 0xFF)) & 0xFF);
					g_buf[pos] |= ((ud_buf[i+1] + (g_buf[pos-1]>>8  & 0xFF)) & 0xFF)<<8;
					g_buf[pos] |= ((ud_buf[i+2] + (g_buf[pos-1]>>16 & 0xFF)) & 0xFF)<<16;
					g_buf[pos] |= ((ud_buf[i+3] + (g_buf[pos-1]>>24 & 0xFF)) & 0xFF)<<24;
					i+=4;
					++pos;
				}
				break;
			case 2:
				if(pos < width){break;}
				for(int j = 0 ; j<width ; ++j){
					g_buf[pos]  = ((ud_buf[i  ] + (g_buf[pos-width]     & 0xFF)) & 0xFF);
					g_buf[pos] |= ((ud_buf[i+1] + (g_buf[pos-width]>>8  & 0xFF)) & 0xFF)<<8;
					g_buf[pos] |= ((ud_buf[i+2] + (g_buf[pos-width]>>16 & 0xFF)) & 0xFF)<<16;
					g_buf[pos] |= ((ud_buf[i+3] + (g_buf[pos-width]>>24 & 0xFF)) & 0xFF)<<24;
					i+=4;
					++pos;
				}
				break;
			case 3:
				if(pos < width){break;}
				g_buf[pos] = 0;
				for(int n = 0 ; n<4 ; ++n){
					unsigned char b = (g_buf[pos-width]>>(8*n) & 0xFF);
					g_buf[pos] |= (((ud_buf[i+n])+(b/2)) & 0xFF)<<(8*n);
				}
				i+=4;
				++pos;
				for(int j = 1 ; j<width ; ++j){
					g_buf[pos] = 0;
					for(int n = 0 ; n<4 ; ++n){
						unsigned char a = (g_buf[pos-1]>>(8*n) & 0xFF);
						unsigned char b = (g_buf[pos-width]>>(8*n) & 0xFF);
						g_buf[pos] |= (((ud_buf[i+n])+((a+b)/2)) & 0xFF)<<(8*n);
					}
					i+=4;
					++pos;
				}
				break;
			case 4:
				if(pos < width){break;}
				g_buf[pos] = 0;
				for(int n = 0 ; n<4 ; ++n){
					int a = 0;
					int b = (g_buf[pos-width]>>(8*n) & 0xFF);
					int c = 0;
					int p = a+b-c;
					int pa = abs(p-a), pb = abs(p-b), pc = abs(p-c);
					int pr = n;
					if(pa<=pb && pa<=pc){pr = a;}
					else if(pb<=pc){pr = b;}
					else{pr = c;}

					unsigned char t_buf = ud_buf[i]+pr;
					g_buf[pos] |= t_buf<<(8*n);
					++i;
				}
				++pos;
				for(int j = 1 ; j<width ; ++j){
					g_buf[pos] = 0;
					for(int n = 0 ; n<4 ; ++n){
						int a = (g_buf[pos-1]>>(8*n) & 0xFF);
						int b = (g_buf[pos-width]>>(8*n) & 0xFF);
						int c = (g_buf[pos-width-1]>>(8*n) & 0xFF);
						int p = a+b-c;
						int pa = abs(p-a), pb = abs(p-b), pc = abs(p-c);
						int pr = n;
						if(pa<=pb && pa<=pc){pr = a;}
						else if(pb<=pc){pr = b;}
						else{pr = c;}

						unsigned char t_buf = ud_buf[i]+pr;
						g_buf[pos] |= t_buf<<(8*n);
						++i;
					}
					++pos;
				}
				break;
			default:
				::MessageBoxA(NULL, "Error","Filter",MB_OK);
				break;
			}
			if(pos>=size){break;}
		}
		}
		break;
	}
	return true;
}

bool ChunksAnalyzer(unsigned char* buf, int* pos, IHDR* ihdr, unsigned int** palette, unsigned int* plt_size,
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
			unsigned int ud_pos = 0;
			unsigned char* ud_buf = 0x00;	//uncomp_data -> ud
			ud_buf = new unsigned char[((*width)+1)*(*height)*4];
			memset(ud_buf, 0x00, sizeof(unsigned char)*(*width)*(*height)*4);
			while(1){
				b = IDATChunk(t_buf, 12+len.i, ihdr, &cnf, ud_buf, &ud_pos);
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
					// graphic buffer reading
					DrawGraphic(*g_buf, ud_buf, *palette, (*width)*(*height), *width, ihdr->color_type);
					break;
				}
			}

			//if(ud_buf != 0x00){delete [] ud_buf;}
		}
		break;
	case ChunkNametoUINT('I','E','N','D'):
		b = CRC32(t_buf, 12+len.i);
		break;
	case ChunkNametoUINT('P','L','T','E'):
		if(*palette != 0x00){delete [] (*palette); *palette = 0x00;}
		if(len.i%3 != 0){b = false; break;}
		*palette = new unsigned int[len.i/3];
		for(int i = 0 ; i<(len.i/3) ; ++i){
			d2i color = {};
			color.c[3] = 0xFF;
			color.c[0] = t_buf[8+(i*3)];
			color.c[1] = t_buf[8+(i*3)+1];
			color.c[2] = t_buf[8+(i*3)+2];
			(*palette)[i] = color.i;
		}
		b = CRC32(t_buf, 12+len.i);
		break;
	case ChunkNametoUINT('t','R','N','S'):
		switch(ihdr->color_type){
		case 0:
			break;
		case 2:
			break;
		case 3:
			if(*palette == 0x00){break;}
			for(int i = 0 ; i<(len.i-12) ; ++i){
				(*palette)[i] &= (t_buf[8+i]<<24);
			}
			break;
		}
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
