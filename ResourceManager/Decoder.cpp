#include "Decoder.h"

#include <io.h>
#include <memory.h>

bool Decode(const char* filename, _BaseType** data){
	if(_access_s(filename, 4) != 0){
		return false;
	}

	TEXT type = filename;
	type = type.Search(".", 'r');

	if(type == ".BMP"){
		if((*data) != 0x00){
			delete data;
			data = 0x00;
		}
		(*data) = new ImageData;
		memset((*data), 0x00, sizeof(ImageData));
		if(!BMPDecoder(filename, (ImageData**)data)){
			delete (*data);
			(*data) = 0x00;
			return false;
		}
		(*data)->type = "IMAGE";
	}
	else if(type == ".PNG"){
		if((*data) != 0x00){
			delete data;
			data = 0x00;
		}
		(*data) = new ImageData;
		memset((*data), 0x00, sizeof(ImageData));
		if(!PNGDecoder(filename, (ImageData**)data)){
			delete (*data);
			(*data) = 0x00;
			return false;
		}
		(*data)->type = "IMAGE";
	}
	else{
		return false;
	}

	return true;
}