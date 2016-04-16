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

	//palete
	unsigned int* palette = 0x00;
	unsigned int plt_size = 0;
	//fixed huffman code
	
	for(int i = 8 ; i < (file_len-3) ; ++i){
		const char ctype[5] = {buf[i], buf[i+1], buf[i+2], buf[i+3], 0x00};
		//TEXT type = ctype;
			
		//Critical chunks
		if((SizeCompare(ctype,"IHDR") == 0) || (SizeCompare(ctype,"PLTE") == 0) || 
		   (SizeCompare(ctype,"IDAT") == 0) || (SizeCompare(ctype,"IEND") == 0) || 
		//Ancillary chunks
		//Transparency Info.
			(SizeCompare(ctype,"tRNS") == 0) || 
		//Color Space Info.
			(SizeCompare(ctype,"cHRM") == 0) || (SizeCompare(ctype,"gAMA") == 0) || (SizeCompare(ctype,"iCCP") == 0) || 
			(SizeCompare(ctype,"sBIT") == 0) || (SizeCompare(ctype,"sRGB") == 0) || 
		//Text Info.
			(SizeCompare(ctype,"iTXt") == 0) || (SizeCompare(ctype,"tEXt") == 0) || (SizeCompare(ctype,"zTXt") == 0) || 
		//etc... Info.
			(SizeCompare(ctype,"bkGD") == 0) || (SizeCompare(ctype,"hIST") == 0) || (SizeCompare(ctype,"pHYs") == 0) || 
			(SizeCompare(ctype,"sPLT") == 0) || 
		//Time Info
			(SizeCompare(ctype,"tTME") == 0)){
				if(!ChunksAnalyzer(buf, &i, &ihdr, &palette, &plt_size,
					&((*data)->width), &((*data)->height), &((*data)->buf))){
					delete [] buf;
					return false;
				}
		}
	}

	delete [] buf;

	if(palette != 0x00){delete [] palette;}

	_close(fadr);

	return true;
}
