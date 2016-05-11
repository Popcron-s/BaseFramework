#include "Text.h"

INT LengthCompare(const char* text1, const char* text2){
	if(text1 == 0x00 || text2 == 0x00){return -2;}
	for(UINT i = 0 ; ; ++i){
		if((text1[i] == 0x00) && (text2[i] == 0x00)){
			return 0;
		}
		else if(text2[i] == 0x00){
			return 1;
		}
		else if(text1[i] == 0x00){
			return -1;
		}
	}
	return -2;
}

INT SizeCompare(const char* text1, const char* text2){
	if(text1 == 0x00 || text2 == 0x00){return -2;}
	INT result = LengthCompare(text1, text2);
	if(result != 0){return result;}

	UINT Length = GetLength(text1);
	for(UINT i = 0 ; i<Length ; ++i){
		if(text1[i] > text2[i]){
			return 1;
		}
		else if(text1[i] < text2[i]){
			return -1;
		}
	}
	return 0;
}

char* CharSearch(const char* text, const char* cha, const char mode){
	if(text == 0x00){return 0x00;}
	UINT Length = GetLength(text);
	UINT chaLen = GetLength(cha);
	if(Length < chaLen){return 0x00;}
	if(mode == 'n' || mode == 'N'){
		for(UINT i = 0 ; i<=(Length-chaLen) ; ++i){
			for(UINT j = 0 ; j<chaLen ; ++j){
				if(text[i+j] != cha[j]){break;}
				if(j == (chaLen-1)){
					return (char*)(text+i);
				}
			}
		}
	}
	else if(mode == 'r' || mode == 'R'){
		for(UINT i = Length ; i>=(0+chaLen) ; --i){
			for(UINT j = chaLen ; j>0 ; --j){
				if(text[(i-1)-(chaLen-j)] != cha[j-1]){break;}
				if(j == 1){
					return (char*)(text+((i-1)-(chaLen-1)));
				}
			}
		}
	}
	return 0x00;
}
