#pragma once

#include "..\\Common\\Variable.h"
#include "..\\Common\\Function.h"


INT LengthCompare(const char*, const char*);	//-1 : small / 0 : equal / 1 : large
INT SizeCompare(const char*, const char*);	//-1 : small / 0 : equal / 1 : large
char* CharSearch(const char*, const char*, const char);	//0 : no search / else : address
