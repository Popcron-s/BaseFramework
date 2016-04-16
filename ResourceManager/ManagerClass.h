#pragma once

#include "BaseType.h"
#include "..\\Common\\Function.h"

class _ResourceManager{
private:
	static _ResourceManager* m_pSingleton;

	_ResourceManager();
	~_ResourceManager();

	unsigned int m_Count;
	_Node* m_Head;

public:
	static _ResourceManager* GetSingleton();
	static void Destroy();

	void TextNormalize(char*);

	bool Insert(const char*);
	bool Remove(const char*);
	bool RemoveAll();

	bool GetData(const char*, _BaseType**);
	_BaseType* GetData(const char*);

	void Sort();
};