#include "Decoder.h"

#include <io.h>
#include <fcntl.h>
#include <share.h>
#include <sys\types.h>
#include <sys\stat.h>

bool BMPDecoder(const char* filename, ImageData** data){
	if((*data) == 0x00){return false;}

	int fadr = 0;
	
	_sopen_s(&fadr, filename, O_RDONLY | O_BINARY, _SH_DENYWR , _S_IREAD);

	if(fadr == 0xFFFFFFFF){return false;}

	unsigned char* buf = new unsigned char[54];

	_read(fadr, buf, 54);

	if(buf[0] != 'B' || buf[1] != 'M'){
		delete [] buf;
		buf = 0x00;
		return false;
	}

	union d2i{
		unsigned char c[4];
		unsigned int i;
	}temp;

	temp.i = 0x0;
	temp.c[0] = buf[18];
	temp.c[1] = buf[19];
	temp.c[2] = buf[20];
	temp.c[3] = buf[21];

	(*data)->width = temp.i;

	temp.i = 0x0;
	temp.c[0] = buf[22];
	temp.c[1] = buf[23];
	temp.c[2] = buf[24];
	temp.c[3] = buf[25];

	(*data)->height = temp.i;

	if((*data)->buf != 0x00){
		delete [] (*data)->buf;
		(*data)->buf = 0x00;
	}

	(*data)->buf = new unsigned int[(*data)->width * (*data)->height];

	temp.i = 0x0;
	temp.c[0] = buf[34];
	temp.c[1] = buf[35];
	temp.c[2] = buf[36];
	temp.c[3] = buf[37];

	delete [] buf;
	buf = new unsigned char[temp.i];

	_read(fadr, buf, temp.i);

	_close(fadr);

	int index = ((*data)->width*3)%4;
	index = ((*data)->width*3) + ((index == 0)?0:(4-index));

	for(int y = ((*data)->height-1) ; y >= 0 ; --y){
		for(int x = 0 ; x < (*data)->width ; ++x){
			temp.i = 0x00;

			temp.c[3] = 0xFF; //a
			temp.c[0] = buf[((-y+((*data)->height-1))*index)+(x*3)+2]; //r
			temp.c[1] = buf[((-y+((*data)->height-1))*index)+(x*3)+1]; //g
			temp.c[2] = buf[((-y+((*data)->height-1))*index)+(x*3)]; //b
			
			(*data)->buf[(y*(*data)->width)+x] = temp.i;
		}
	}

	delete [] buf;

	return true;
}