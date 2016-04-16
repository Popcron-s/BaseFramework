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
		for(UINT i = 0 ; i<m_texture_num ; ++i){
			delete [] m_texture[i].text;
			m_texture[i].text = 0;
			m_texture[i].length = 0;
		}
		delete [] m_texture;
		m_texture = 0x00;
		m_texture_num = 0;
	}
}

_vector3 _CObject::GetPosition() const{return m_pos;}
_vector3 _CObject::GetRotation() const{return m_rot;}
_vector3 _CObject::GetScale() const{return m_scl;}
void _CObject::SetPosition(_vector3 pos){m_pos = pos;}
void _CObject::SetRotation(_vector3 rot){m_rot = rot;}
void _CObject::SetScale(_vector3 scl){m_scl = scl;}

_matrix4x4 _CObject::GetWorldMatrix() const{return m_world;}
void _CObject::SetWorldMatrix(){
	//scale->rotation->Position
	_matrix4x4 t_mat = {
		m_scl.x, 0,0,0,
		0, m_scl.y,0,0,
		0,0, m_scl.z,0,
		0,0,0,1
	};
	//1-2yy-2zz , -2wz+2xy , 2wy+2xz
	//2wz+2xy , 1-2xx-2zz , -2wx+2yz
	//-2wy+2xz , 2wx+2yz , 1-2xx-2yy
	_matrix3x3 t_rot = {
		1-(2*m_rot.y*m_rot.y)-(2*m_rot.z*m_rot.z), (2*m_rot.x*m_rot.y)-(2*m_rot.z), (2*m_rot.x*m_rot.z)+(2*m_rot.y),
		(2*m_rot.x*m_rot.y)+(2*m_rot.z), 1-(2*m_rot.x*m_rot.x)-(2*m_rot.z*m_rot.z), (2*m_rot.y*m_rot.z)-(2*m_rot.x),
		(2*m_rot.x*m_rot.z)-(2*m_rot.y), (2*m_rot.y*m_rot.z)+(2*m_rot.x), 1-(2*m_rot.x*m_rot.x)-(2*m_rot.y*m_rot.y)
	};
	t_mat._11 = m_scl.x * t_rot._11; t_mat._12 = m_scl.x * t_rot._21;
	t_mat._13 = m_scl.x * t_rot._31; t_mat._14 = 0;

	t_mat._21 = m_scl.y * t_rot._12; t_mat._22 = m_scl.y * t_rot._22;
	t_mat._23 = m_scl.y * t_rot._32; t_mat._14 = 0;

	t_mat._31 = m_scl.z * t_rot._13; t_mat._32 = m_scl.z * t_rot._23;
	t_mat._33 = m_scl.z * t_rot._33; t_mat._34 = 0;
	
	t_mat._41 = m_pos.x; t_mat._42 = m_pos.y; t_mat._43 = m_pos.z; t_mat._44 = 1;

	m_world = t_mat;
}

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

UINT _CObject::GetTextureNumber() const{return m_texture_num;}
bool _CObject::SetTexture(_TEXT* tex, UINT num){
	if(m_texture != 0x00){
		for(UINT i = 0 ; i<m_texture_num ; ++i){
			if(m_texture[i].text != 0x00){
				delete [] m_texture[i].text;
				m_texture[i].text = 0;
				m_texture[i].length = 0;
			}
		}
		delete [] m_texture;
		m_texture = 0x00;
		m_texture_num = 0;
	}
	m_texture = new _TEXT[num];
	m_texture_num = num;
	for(UINT i = 0 ; i<num ; ++i){
		m_texture[i].text = 0x00;
		m_texture[i].length = 0;
		SetText(&(m_texture[i]),tex[i].text);
	}
	return true;
}
_TEXT* _CObject::GetTexture() const{return m_texture;}