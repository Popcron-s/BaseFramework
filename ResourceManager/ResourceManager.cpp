#include "ResourceManager.h"

_BaseType* GetResource(const char* filename){
	return _ResourceManager::GetSingleton()->GetData(filename);
}

bool GetResource(const char* filename, 
	unsigned int* width, unsigned int* height, unsigned int** buf){
		_BaseType* data = 0x00;
		if(_ResourceManager::GetSingleton()->GetData(filename, &data)){
			if(data->type != "IMAGE"){return false;}
			*width = ((ImageData*)data)->width;
			*height = ((ImageData*)data)->height;
			(*buf) = ((ImageData*)data)->buf;
			return true;
		}
		else{
			return false;
		}
}

bool AddResource(const char* filename){
	return _ResourceManager::GetSingleton()->Insert(filename);
}

bool RemoveResource(const char* filename){
	return _ResourceManager::GetSingleton()->Remove(filename);
}

bool RemoveAllResource(){
	return _ResourceManager::GetSingleton()->RemoveAll();
}

void SortResource(){
	return _ResourceManager::GetSingleton()->Sort();
}