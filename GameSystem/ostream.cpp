#include "ostream.h"

_oStream* _oStream::m_pSingleton = 0x00;

CREATE_LIST_FUNTION(_oStream,_CCamera,Camera);

_oStream::_oStream() : 
	m_Size_x(0), m_Size_y(0), 
	m_Camera_List(0x00), m_Camera_num(0)
{}
_oStream::~_oStream(){
	ReleaseAllCamera();
}

UINT _oStream::GetSizeX() const{return m_Size_x;}
UINT _oStream::GetSizeY() const{return m_Size_y;}
void _oStream::SetSize(UINT x, UINT y){m_Size_x = x; m_Size_y = y;}

void _oStream::render_graphic(){
	_LIST<_CCamera>* t_node = m_Camera_List;
	UINT able_cam = 0;
	while(t_node != 0x00){
		if(t_node->_node->Getable()){++able_cam;}
		t_node = t_node->_next;
	}
	if(able_cam == 0){return;}
	t_node = m_Camera_List;
	_DISPLAY* t_disp = new _DISPLAY[able_cam];
	for(UINT i = 0 ; i<able_cam ; ){
		if(t_node->_node->Getable()){
			t_node->_node->Render(&(t_disp[i]));
			++i;
		}
	}
	DrawDisplay(m_Size_x, m_Size_y, t_disp, able_cam);
	for(UINT i = 0 ; i<able_cam ; ++i){
		delete [] t_disp[i].buf;
	}
	delete [] t_disp;
}

void _oStream::render(){
	render_graphic();
}