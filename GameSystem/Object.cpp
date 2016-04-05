#include "Object.h"

_CObject::_CObject(){
	m_pos = {0.0f, 0.0f, 0.0f};
	m_rot = {0.0f, 0.0f, 0.0f};
	m_scl = {1.0f, 1.0f, 1.0f};

	m_world = {1.0f, 0.0f, 0.0f, 0.0f,
			   0.0f, 1.0f, 0.0f, 0.0f,
			   0.0f, 0.0f, 1.0f, 0.0f,
			   0.0f, 0.0f, 0.0f, 1.0f};

	m_vertex = 0x00;
	m_vertex_num = 0;

	m_texture = 0x00;
	m_texture_num = 0;
}

_CObject::~_CObject(){
	if(m_vertex != 0x00){
		delete [] m_vertex;
		m_vertex = 0x00;
		m_vertex_num = 0;
	}
	if(m_texture != 0x00){
		delete [] m_texture;
		m_texture = 0x00;
		m_texture_num = 0;
	}
}

_matrix4x4 _CObject::GetWorldMatrix() const{return m_world;}

UINT _CObject::GetVertexNumber() const{
	return m_vertex_num;
}
bool _CObject::SetVertex(_defaultvertex* vertex, UINT num){
	if(m_vertex != 0x00){
		delete [] m_vertex;
		m_vertex = 0x00;
		m_vertex_num = 0;
	}
	m_vertex = new _defaultvertex[num];
	m_vertex_num = num;
	for(UINT i = 0 ; i<num ; ++i){
		m_vertex[i] = vertex[i];
	}
	return true;
}
_defaultvertex* _CObject::GetVertex() const{
	return m_vertex;
}