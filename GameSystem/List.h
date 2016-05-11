#pragma once

#include "..\\Common\\Variable.h"

template <class T>
struct _LIST{
public:
	T* _node;
	_LIST<T>* _next;
};

#define CREATE_LIST(Class,Name)										\
private:															\
_LIST<Class>* m_##Name##_List;										\
UINT m_##Name##_num;												\
public:																\
UINT Get##Name##Number() const;										\
Class* Create##Name##();											\
bool Release##Name##(Class* temp);									\
bool ReleaseAll##Name##();											\
Class* Search##Name##(UINT id) const;								\
bool Swap##Name##(Class* temp1, Class* temp2);

#define CREATE_LIST_FUNTION(Pregnant,Class,Name)					\
UINT Pregnant::Get##Name##Number() const{return m_##Name##_num;}	\
Class* Pregnant::Create##Name##(){									\
	_LIST<Class>** t_node = &m_##Name##_List;						\
	while((*t_node) != 0x00){										\
		t_node = &((*t_node)->_next);								\
	}																\
	(*t_node) = new _LIST<Class>;									\
	(*t_node)->_node = new Class;									\
	(*t_node)->_next = 0x00;										\
	++m_##Name##_num;												\
	return (*t_node)->_node;										\
}																	\
bool Pregnant::Release##Name##(Class* temp){						\
	_LIST<Class>** t_node = &m_##Name##_List;						\
	while((*t_node)->_node != temp){								\
		t_node = &((*t_node)->_next);								\
		if((*t_node) == 0x00){return false;}						\
	}																\
	_LIST<Class>* d_node = (*t_node);								\
	(*t_node) = (*t_node)->_next;									\
	delete d_node->_node;											\
	delete d_node;													\
	--m_##Name##_num;												\
	return true;													\
}																	\
bool Pregnant::ReleaseAll##Name##(){								\
	_LIST<Class>** t_node = &m_##Name##_List;						\
	while((*t_node) != 0x00){										\
		_LIST<Class>* d_node = (*t_node);							\
		(*t_node) = (*t_node)->_next;								\
		delete d_node->_node;										\
		delete d_node;												\
		--m_##Name##_num;											\
	}																\
	m_##Name##_List = 0x00;											\
	if(m_##Name##_num == 0){return true;}							\
	else{return false;}												\
}																	\
Class* Pregnant::Search##Name##(UINT id) const{						\
	_LIST<Class>* t_node = m_##Name##_List;							\
	for(UINT i = 0 ; i < m_##Name##_num ; ++i){						\
		if(i == id){return	t_node->_node;}							\
		t_node = t_node->_next;										\
	}																\
	return 0x00;													\
}																	\
bool Pregnant::Swap##Name##(Class* temp1, Class* temp2){			\
	_LIST<Class>* t_node1 = m_##Name##_List;						\
	_LIST<Class>* t_node2 = m_##Name##_List;						\
	for(UINT i = 0 ; i<m_##Name##_num ; ++i){						\
		if(t_node1->_node != temp1){t_node1 = t_node1->_next;}		\
		if(t_node2->_node != temp2){t_node2 = t_node2->_next;}		\
		if(t_node1->_node == temp1 && t_node2->_node == temp2){		\
			t_node1->_node = temp2;									\
			t_node2->_node = temp1;									\
			return true;											\
		}															\
	}																\
	return false;													\
}

#define REGISTER_LIST(Class,Name)									\
private:															\
_LIST<Class>* m_##Name##_List;										\
UINT m_##Name##_num;												\
public:																\
UINT Get##Name##Number() const{return m_##Name##_num;}				\
bool Register##Name(Class* temp){									\
	_LIST<Class>** t_node = &m_##Name##_List;						\
	while((*t_node) != 0x00){										\
		if((*t_node)->_node == temp){return false;}					\
		t_node = &((*t_node)->_next);								\
	}																\
	(*t_node) = new _LIST<Class>;									\
	(*t_node)->_node = temp;										\
	(*t_node)->_next = 0x00;										\
	++m_##Name##_num;												\
	return true;													\
}																	\
bool Remove##Name##(Class* temp){									\
	_LIST<Class>** t_node = &m_##Name##_List;						\
	while((*t_node)->_node != temp){								\
		t_node = &((*t_node)->_next);								\
		if((*t_node) == 0x00){return false;}						\
	}																\
	_LIST<Class>* d_node = (*t_node);								\
	(*t_node) = (*t_node)->_next;									\
	delete d_node;													\
	--m_##Name##_num;												\
	return true;													\
}																	\
bool RemoveAll##Name##(){											\
	_LIST<Class>** t_node = &m_##Name##_List;						\
	while((*t_node) != 0x00){										\
		_LIST<Class>* d_node = (*t_node);							\
		(*t_node) = (*t_node)->_next;								\
		delete d_node;												\
		--m_##Name##_num;											\
	}																\
	m_##Name##_List = 0x00;											\
	if(m_##Name##_num == 0){return true;}							\
	else{return false;}												\
}																	\
Class* Search##Name##(UINT id) const{								\
	_LIST<Class>* t_node = m_##Name##_List;							\
	for(UINT i = 0 ; i < m_##Name##_num ; ++i){						\
		if(i == id){return	t_node->_node;}							\
		t_node = t_node->_next;										\
	}																\
	return 0x00;													\
}																	\
bool Swap##Name##(Class* temp1, Class* temp2){						\
	_LIST<Class>* t_node1 = m_##Name##_List;						\
	_LIST<Class>* t_node2 = m_##Name##_List;						\
	for(UINT i = 0 ; i<m_##Name##_num ; ++i){						\
		if(t_node1->_node != temp1){t_node1 = t_node1->_next;}		\
		if(t_node2->_node != temp2){t_node2 = t_node2->_next;}		\
		if(t_node1->_node == temp1 && t_node2->_node == temp2){		\
			t_node1->_node = temp2;									\
			t_node2->_node = temp1;									\
			return true;											\
		}															\
	}																\
	return false;													\
}