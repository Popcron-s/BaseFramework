#pragma once

#ifdef GAMESYSTEM_EXPORTS
#define GSYS_API __declspec(dllexport)
#else
#define GSYS_API __declspec(dllimport)
#endif

#include "Variable.h"

extern "C"{
	GSYS_API bool SetText(_TEXT*, const char*);

	GSYS_API UINT GetLength(const char*);
	
	GSYS_API INT LengthCompare(_TEXT*, _TEXT*);	//-1 : small / 0 : equal / 1 : large
	GSYS_API INT SizeCompare(_TEXT*, _TEXT*);	//-1 : small / 0 : equal / 1 : large
	GSYS_API char* CharSearch(_TEXT*, const char*, const char);	//0 : no search / else : address
}