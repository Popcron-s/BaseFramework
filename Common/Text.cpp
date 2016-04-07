#include "Text.h"

_Text::_Text(){
	str = 0x00;
	length = 0;
}

_Text::_Text(const char* text){
	length = 0;
	const char* t_char = text;
	while(1){
		if(*t_char == 0x00){
			break;
		}
		++length;
		t_char += 1;
	}
	str = new char[length+1];
	for(unsigned int i = 0 ; i<(length+1) ; ++i){
		str[i] = text[i];
	}
}

_Text::~_Text(){
	if(str != 0x00){
		delete [] str;
		str = 0x00;
	}
	length = 0;
}

const char* _Text::operator =(const char* text){
	if(text == 0x00){
		if(str != 0x00){
			delete [] str;
			str = 0x00;
		}
		length = 0;
	
		return 0x00;
	}

	char* t_text = 0x00;
	unsigned int t_length = 0;
	
	while(1){
		if(text[t_length] == 0x00){
			break;
		}
		++t_length;
	}
	t_text = new char[t_length+1];
	for(unsigned int i = 0 ; i<(t_length+1) ; ++i){
		t_text[i] = text[i];
	}
	
	if(str != 0x00){
		delete [] str;
		str = 0x00;
	}

	str = t_text;
	length = t_length;

	return str;
}

//_Text::operator const char*() const{
//	return str;
//}

_Text::operator char*() const{
	return str;
}

const unsigned int _Text::GetLength(){
	return length;
}

//Compare Type : 2 small / 1 equal / 0 large

int _Text::LengthCompare(_Text* text){
	if(text == 0x00 || str == 0x00){return -1;}
	if(length > text->GetLength()){
		return 0;
	}
	else if(length < text->GetLength()){
		return 2;
	}
	else{
		return 1;
	}
}

int _Text::SizeCompare(_Text* text){
	int comp = LengthCompare(text);
	if(comp != 1){return comp;}
	for(unsigned int i = 0 ; i<length ; ++i){
		if(str[i] == (*text)[i]){continue;}
		else{
			if(str[i] > (*text)[i]){
				return 0;
			}
			else{
				return 2;
			}
		}
	}
	return 1;
}

bool _Text::operator ==(_Text& text){
	const int result = SizeCompare(&text);
	if(result < 0){return false;}
	if(result == 1){return true;}
	else{return false;}
}
bool _Text::operator !=(_Text& text){
	const int result = SizeCompare(&text);
	if(result < 0){return false;}
	if(result == 1){return false;}
	else{return true;}
}
bool _Text::operator > (_Text& text){
	const int result = SizeCompare(&text);
	if(result < 0){return false;}
	if(result == 0){return true;}
	else{return false;}
}
bool _Text::operator >=(_Text& text){
	const int result = SizeCompare(&text);
	if(result < 0){return false;}
	if(result == 0 || result == 1){return true;}
	else{return false;}
}
bool _Text::operator < (_Text& text){
	const int result = SizeCompare(&text);
	if(result < 0){return false;}
	if(result == 2){return true;}
	else{return false;}
}
bool _Text::operator <=(_Text& text){
	const int result = SizeCompare(&text);
	if(result < 0){return false;}
	if(result == 2 || result == 1){return true;}
	else{return false;}
}

bool _Text::operator ==(const char* text){
	_Text t_text = text;
	return operator ==(t_text);
}
bool _Text::operator !=(const char* text){
	_Text t_text = text;
	return operator !=(t_text);
}
bool _Text::operator >=(const char* text){
	_Text t_text = text;
	return operator >=(t_text);
}
bool _Text::operator <=(const char* text){
	_Text t_text = text;
	return operator <=(t_text);
}
bool _Text::operator < (const char* text){
	_Text t_text = text;
	return operator < (t_text);
}
bool _Text::operator > (const char* text){
	_Text t_text = text;
	return operator > (t_text);
}

char* _Text::Search(const char* text, const char type){
	if(text == 0x00){return 0;}
	char* adr = 0x00;
	
	unsigned int t_length = 0;
	while(1){
		if(*(text + t_length) == 0x00){break;}
		++t_length;
	}

	if(type == 'n' || type == 'N'){
		for(unsigned int i = 0 ; i<length ; ++i){
			if(str[i] == text[0]){
				for(unsigned int j = 0 ; (j<t_length) && (i+j<length) ; ++j){
					if(str[i+j] != text[j]){break;}
					if(j == (t_length-1)){
						adr = (str+i);
						break;
					}
				}
			}
			if(adr != 0x00){break;}
		}
	}
	else if(type == 'r' || type == 'R'){
		for(int i = length-1 ; i>=0 ; --i){
			if(str[i] == text[t_length-1]){
				for(unsigned int j = 0 ; (j<t_length) && (i-j>=0) ; ++j){
					if(str[i-j] != text[(t_length-1)-j]){break;}
					if(j == (t_length-1)){
						adr = (str+(i-j));
						break;
					}
				}
			}
			if(adr != 0x00){break;}
		}
	}

	return adr;
}