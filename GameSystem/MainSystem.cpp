#include "MainSystem.h"

_CGameSystem* _CGameSystem::m_pSingleton = 0x00;

_CGameSystem* _CGameSystem::GetSingleton(){
	if(m_pSingleton == 0x00){
		m_pSingleton = new _CGameSystem;
	}
	return m_pSingleton;
}

void _CGameSystem::Destroy(){
	if(m_pSingleton != 0x00){
		delete m_pSingleton;
		m_pSingleton = 0x00;
	}
}

_CGameSystem::_CGameSystem() : 
	m_Object_List(0x00), m_Object_num(0),
	m_Camera_List(0x00), m_Camera_num(0),
	m_update_List(0x00), m_update_num(0),
	m_Size_x(0), m_Size_y(0)
{}
_CGameSystem::~_CGameSystem(){
	RemoveAllCamera();
	RemoveAllUpdate();
	ReleaseAllObject();
}

void _CGameSystem::Update(){
	// Update
	_funcLIST* t_func = m_update_List;
	while(t_func != 0x00){
		if(t_func->_func != 0x00){t_func->_func();}
		t_func = t_func->_next;
	}

	//Render
	_LIST<_CCamera>* t_cam = m_Camera_List;
	UINT enable_cam = 0;
	while(t_cam != 0x00){
		if(t_cam->_node->Getable()){
			++enable_cam;
		}
		t_cam = t_cam->_next;
	}
	_DISPLAY* display = new _DISPLAY[enable_cam];
	t_cam = m_Camera_List;
	UINT now_cam = 0;
	while(t_cam != 0x00){
		if(t_cam->_node->Getable()){
			t_cam->_node->Render(&(display[now_cam]));
			++now_cam;
		}
		t_cam = t_cam->_next;
	}
	DrawDisplay(m_Size_x,m_Size_y,display,enable_cam);
	for(UINT i = 0 ; i<enable_cam ; ++i){
		delete [] (display[i].buf);
	}
	delete [] display;
}

UINT _CGameSystem::GetSizeX() const{return m_Size_x;}
UINT _CGameSystem::GetSizeY() const{return m_Size_y;}
void _CGameSystem::SetSize(UINT x, UINT y){m_Size_x = x; m_Size_y = y;}

//Object//////////////////////////////////////////////////////////////////////////////////////
UINT _CGameSystem::GetObjectNumber() const{return m_Object_num;}
_CObject* _CGameSystem::CreateObject(){
	_LIST<_CObject>* t_node = new _LIST<_CObject>;
	t_node->_node = new _CObject;
	t_node->_next = m_Object_List;
	m_Object_List = t_node;

	++m_Object_num;

	return t_node->_node;
}

bool _CGameSystem::ReleaseObject(_CObject* obj){
	_LIST<_CObject>* t_node = m_Object_List;
	_LIST<_CObject>* prev = 0x00;
	while(t_node != 0x00){
		if(t_node->_node == obj){
			_LIST<_CCamera>* c_node = m_Camera_List;
			while(c_node != 0x00){
				c_node->_node->RemoveObject(obj);
				c_node = c_node->_next;
			}
			//remove speaker in obj
			//remove input in obj

			if(prev != 0x00){
				prev->_next = t_node->_next;
			}
			else{
				m_Object_List = t_node->_next;
			}
			delete (t_node->_node);
			delete t_node;

			--m_Object_num;

			return true;
		}
		prev = t_node;
		t_node = t_node->_next;
	}
	return false;
}
bool _CGameSystem::ReleaseAllObject(){
	_LIST<_CObject>* d_node = m_Object_List;
	while(d_node != 0x00){
		m_Object_List = m_Object_List->_next;
		delete (d_node->_node);
		delete d_node;
		d_node = m_Object_List;
	}

	m_Object_num = 0;
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//Camera//////////////////////////////////////////////////////////////////////////////////////
UINT _CGameSystem::GetCameraNumber() const{return m_Camera_num;}
bool _CGameSystem::RegisterCamera(_CCamera* cam){
	_LIST<_CCamera>** t_node = &m_Camera_List;
	while((*t_node) != 0x00){
		if((*t_node)->_node == cam){return false;}
		t_node = &((*t_node)->_next);
	}
	(*t_node) = new _LIST<_CCamera>;
	(*t_node)->_node = cam;
	(*t_node)->_next = 0x00;

	++m_Camera_num;

	return true;
}
bool _CGameSystem::RemoveCamera(_CCamera* cam){
	_LIST<_CCamera>* t_node = m_Camera_List;
	_LIST<_CCamera>* prev = 0x00;
	while(t_node != 0x00){
		if(t_node->_node == cam){
			if(prev != 0x00){
				prev->_next = t_node->_next;
			}
			else{
				m_Camera_List = t_node->_next;
			}
			delete t_node;

			--m_Camera_num;

			return true;
		}
		prev = t_node;
		t_node = t_node->_next;
	}
	return false;
}
bool _CGameSystem::RemoveAllCamera(){
	_LIST<_CCamera>* d_node = m_Camera_List;
	while(d_node != 0x00){
		m_Camera_List = m_Camera_List->_next;
		delete d_node;
		d_node = m_Camera_List;
	}
	m_Camera_num = 0;
	return true;
}
_CCamera* _CGameSystem::SearchCamera(UINT ID) const{
	_LIST<_CCamera>* t_node = m_Camera_List;
	for(UINT i = 0 ; i<ID ; ++i){
		if(t_node == 0x00){return 0x00;}
		t_node = t_node->_next;
	}
	return t_node->_node;
}
bool _CGameSystem::SwapCamera(_CCamera* cam1, _CCamera* cam2){return false;}
//////////////////////////////////////////////////////////////////////////////////////////

//Update//////////////////////////////////////////////////////////////////////////////////
UINT _CGameSystem::GetUpdateNumber() const{return m_update_num;}
bool _CGameSystem::RegisterUpdate(void (*func)()){
	_funcLIST** t_node = &m_update_List;
	while((*t_node) != 0x00){
		if((*t_node)->_func == func){return false;}
		t_node = &((*t_node)->_next);
	}
	(*t_node) = new _funcLIST;
	(*t_node)->_func = func;
	(*t_node)->_next = 0x00;

	++m_update_num;

	return true;
}
bool _CGameSystem::RemoveUpdate(void (*func)()){
	_funcLIST* t_node = m_update_List;
	_funcLIST* prev = 0x00;
	while(t_node != 0x00){
		if(t_node->_func == func){
			if(prev != 0x00){
				prev->_next = t_node->_next;
			}
			else{
				m_update_List = t_node->_next;
			}
			delete t_node;

			--m_update_num;

			return true;
		}
		prev = t_node;
		t_node = t_node->_next;
	}
	return false;
}
bool _CGameSystem::RemoveAllUpdate(){
	_funcLIST* d_node = m_update_List;
	while(d_node != 0x00){
		m_update_List = m_update_List->_next;
		delete d_node;
		d_node = m_update_List;
	}
	m_update_num = 0;
	return true;
}
void* _CGameSystem::SearchUpdate(UINT ID) const{
	_funcLIST* t_node = m_update_List;
	for(UINT i = 0 ; i<ID ; ++i){
		if(t_node == 0x00){return 0x00;}
		t_node = t_node->_next;
	}
	return t_node->_func;
}
bool _CGameSystem::SwapUpdate(void*, void*){return false;}
//////////////////////////////////////////////////////////////////////////////////////////
