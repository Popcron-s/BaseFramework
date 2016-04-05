#pragma once


template <class T>
struct _LIST{
public:
	T* _node;
	_LIST<T>* _next;
};

struct _funcLIST{
	void (*_func)();
	_funcLIST* _next;
};