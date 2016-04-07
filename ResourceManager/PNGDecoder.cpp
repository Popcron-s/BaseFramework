#include "Decoder.h"
#include "PNGDecoder.h"

bool PNGDecoder(const char* filename, ImageData** data){
	if((*data) == 0x00){return false;}

	int fadr = 0;
	
	_sopen_s(&fadr, filename, O_RDONLY | O_BINARY, _SH_DENYWR , _S_IREAD);

	if(fadr == 0xFFFFFFFF){return false;}

	long file_len = _filelength(fadr);

	unsigned char* buf = new unsigned char[file_len];

	_read(fadr, buf, file_len);
	//89 50 4E 47 0D 0A 1A 0A 
	if(buf[0] != 0x89 || buf[1] != 0x50 || buf[2] != 0x4E || buf[3] != 0x47 || 
	   buf[4] != 0x0D || buf[5] != 0x0A || buf[6] != 0x1A || buf[7] != 0x0A ){
		delete [] buf;
		buf = 0x00;
		return false;
	}

	IHDR ihdr;
	memset(&ihdr, 0x00, sizeof(IHDR));
	
	for(int i = 8 ; i < (file_len-3) ; ++i){
		const char ctype[5] = {buf[i], buf[i+1], buf[i+2], buf[i+3], 0x00};
		TEXT type = ctype;
			
		//Critical chunks
		if(type == "IHDR" || type == "PLTE" || 
		   type == "IDAT" || type == "IEND" || 
		//Ancillary chunks
		//Transparency Info.
		   type == "tRNS" || 
		//Color Space Info.
		   type == "cHRM" || type == "gAMA" || type == "iCCP" || 
		   type == "sBIT" || type == "sRGB" || 
		//Text Info.
		   type == "iTXt" || type == "tEXt" || type == "zTXt" || 
		//etc... Info.
		   type == "bkGD" || type == "hIST" || type == "pHYs" || 
		   type == "sPLT" || 
		//Time Info
		   type == "tTME"){
				if(!ChunksAnalyzer(buf, &i, &ihdr,
					&((*data)->width), &((*data)->height), &((*data)->buf))){
					delete [] buf;
					return false;
				}
		}
	}

	delete [] buf;

	_close(fadr);

	return true;
}
