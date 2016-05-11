#include "Function.h"

bool SetText(_TEXT* text, const char* string){
	if(string == 0x00 || text == 0x00){return false;}
	if(text->text != 0x00){
		delete [] text->text;
		text->text = 0x00;
	}
	text->length = GetLength(string);
	if(text->length == 0){
		text->text = 0x00;
	}
	text->text = new char[text->length+1];
	for(UINT i = 0 ; i<=text->length ; ++i){
		text->text[i] = string[i];
	}
	return true;
}

UINT GetLength(const char* text){
	if(text == 0x00){return 0;}
	UINT length = 0;
	for(UINT i = 0 ; ; ++i){
		if(text[i] == 0x00){
			break;
		}
		++length;
	}
	return length;
}

INT LengthCompare(_TEXT* text1, _TEXT* text2){
	if(text1 == 0x00 || text2 == 0x00){return -2;}
	if(text1->length == text2->length){
		return 0;
	}
	if(text1->length > text2->length){
		return 1;
	}
	else{
		return -1;
	}
}
INT SizeCompare(_TEXT* text1, _TEXT* text2){
	if(text1 == 0x00 || text2 == 0x00){return -2;}
	if(text1->length > text2->length){
		return 1;
	}
	if(text1->length < text2->length){
		return -1;
	}
	else{
		for(UINT i = 0 ; i<text1->length ; ++i){
			if(text1->text[i] > text2->text[i]){return 1;}
			else if(text1->text[i] < text2->text[i]){return -1;}
		}
		return 0;
	}
}
char* CharSearch(_TEXT* text, const char* cha, const char mode){
	if(text == 0x00){return 0x00;}
	UINT chaLen = GetLength(cha);
	if(text->length < chaLen){return 0x00;}
	if(mode == 'n' || mode == 'N'){
		for(UINT i = 0 ; i<=(text->length-chaLen) ; ++i){
			for(UINT j = 0 ; j<chaLen ; ++j){
				if(text->text[i+j] != cha[j]){break;}
				if(j == (chaLen-1)){
					return (char*)((text->text)+i);
				}
			}
		}
	}
	else if(mode == 'r' || mode == 'R'){
		for(UINT i = text->length ; i>=(0+chaLen) ; --i){
			for(UINT j = chaLen ; j>0 ; --j){
				if(text->text[(i-1)-(chaLen-j)] != cha[j-1]){break;}
				if(j == 1){
					return (char*)((text->text)+((i-1)-(chaLen-1)));
				}
			}
		}
	}
	return 0x00;
}

_matrix4x4 MultipleMatrix4x4(_matrix4x4 m1, _matrix4x4 m2){
	_matrix4x4 m = {
		(m1._11*m2._11)+(m1._12*m2._21)+(m1._13*m2._31)+(m1._14*m2._41),
		(m1._11*m2._12)+(m1._12*m2._22)+(m1._13*m2._32)+(m1._14*m2._42),
		(m1._11*m2._13)+(m1._12*m2._23)+(m1._13*m2._33)+(m1._14*m2._43),
		(m1._11*m2._14)+(m1._12*m2._24)+(m1._13*m2._34)+(m1._14*m2._44),
		(m1._21*m2._11)+(m1._22*m2._21)+(m1._23*m2._31)+(m1._24*m2._41),
		(m1._21*m2._12)+(m1._22*m2._22)+(m1._23*m2._32)+(m1._24*m2._42),
		(m1._21*m2._13)+(m1._22*m2._23)+(m1._23*m2._33)+(m1._24*m2._43),
		(m1._21*m2._14)+(m1._22*m2._24)+(m1._23*m2._34)+(m1._24*m2._44),
		(m1._31*m2._11)+(m1._32*m2._21)+(m1._33*m2._31)+(m1._34*m2._41),
		(m1._31*m2._12)+(m1._32*m2._22)+(m1._33*m2._32)+(m1._34*m2._42),
		(m1._31*m2._13)+(m1._32*m2._23)+(m1._33*m2._33)+(m1._34*m2._43),
		(m1._31*m2._14)+(m1._32*m2._24)+(m1._33*m2._34)+(m1._34*m2._44),
		(m1._41*m2._11)+(m1._42*m2._21)+(m1._43*m2._31)+(m1._44*m2._41),
		(m1._41*m2._12)+(m1._42*m2._22)+(m1._43*m2._32)+(m1._44*m2._42),
		(m1._41*m2._13)+(m1._42*m2._23)+(m1._43*m2._33)+(m1._44*m2._43),
		(m1._41*m2._14)+(m1._42*m2._24)+(m1._43*m2._34)+(m1._44*m2._44)
	};
	return m;
}