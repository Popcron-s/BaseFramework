#include "MainSystem.h"

_CGameSystem* _CGameSystem::m_pSingleton = 0x00;

//CREATE_LIST_FUNTION(_CGameSystem,_CObjectSet,Object);

_CGameSystem::_CGameSystem() : 
	m_Object_List(0x00), m_Object_num(0),
	main_loop(0x00)
{}
_CGameSystem::~_CGameSystem(){
	AllRemoveAllObject();
	_LIST<_CObjectSet>* t_node = m_Object_List;
	while(t_node != 0x00){
		if(t_node->_node != 0x00){delete t_node->_node; t_node->_node = 0x00;}
		t_node = t_node->_next;
	}
	RemoveAllObject();
}

void _CGameSystem::update(){

	if(main_loop != 0x00){main_loop();}

	_oStream::GetSingleton()->render();
}

void _CGameSystem::AllRemoveObject(_CObjectSet* obj){
	UINT cam_num = _oStream::GetSingleton()->GetCameraNumber();
	for(UINT i = 0 ; i<cam_num ; ++i){
		_oStream::GetSingleton()->SearchCamera(i)->RemoveObject((_CRenderObject*)obj);
	}
}
void _CGameSystem::AllRemoveAllObject(){
	UINT cam_num = _oStream::GetSingleton()->GetCameraNumber();
	for(UINT i = 0 ; i<cam_num ; ++i){
		_oStream::GetSingleton()->SearchCamera(i)->RemoveAllObject();
	}
}