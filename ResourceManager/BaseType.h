#pragma once
#include "..\\Common\\Text.h"

/*****************************************************************
 * _BaseType value type Info
 * Attention : standardize with upper case
 * Graphic Type = "IMAGE" / _Image struct
 * 
 *
 *
 *
 *****************************************************************/

struct _BaseType{
public:
	TEXT type;
};

typedef struct _Image : public _BaseType{
public:
	unsigned int width;
	unsigned int height;
	unsigned int* buf;

	_Image(){
		width = 0; height = 0; buf = 0x00;
	}
	~_Image(){
		if(buf != 0x00){
			delete [] buf;
			buf = 0x00;
		}
		width = 0; height = 0;
	}
}ImageData;

struct _Node{
	TEXT name;
	_BaseType* data;

	_Node* LNode;
	_Node* RNode;

	_Node(){data = 0x00; LNode = 0x00; RNode = 0x00;}
	~_Node(){
		if(data != 0x00){
			delete data;
			data = 0x00;
		}
		LNode = 0x00; RNode = 0x00;
	}
};