#pragma once

#ifdef RESOURCEMANAGER_EXPORTS
#define RMANAG_API __declspec(dllexport)
#include "ManagerClass.h"
#else
#define RMANAG_API __declspec(dllimport)
#pragma comment(lib, "..\\Release\\ResourceManager.lib")
#endif

extern "C"{
	//RMANAG_API _BaseType* GetResource(const char*);
	RMANAG_API bool GetResource(const char*, 
		unsigned int* width, unsigned int* height, unsigned int** buf);
	RMANAG_API bool AddResource(const char*);
	RMANAG_API bool RemoveResource(const char*);
	RMANAG_API bool RemoveAllResource();
	RMANAG_API void SortResource();
}