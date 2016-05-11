#include "Object.h"

_CMesh::_CMesh(_CObject* obj) : 
	m_vertex_num(0), m_vertex(0x00),
	m_texture_num(0), m_texture(0x00), 
	m_pParent(obj){}
_CMesh::~_CMesh(){
	if(m_vertex != 0x00){
		delete [] m_vertex;
	}
	if(m_texture != 0x00){
		for(UINT i = 0 ; i<m_texture_num ; ++i){
			delete [] (m_texture[i]);
		}
		delete [] m_texture;
	}
}

UINT _CMesh::GetVertexNumber() const{return m_vertex_num;}
UINT _CMesh::GetTextureNumber() const{return m_texture_num;}

_VERTEX* _CMesh::GetVertex() const{return m_vertex;}
char** _CMesh::GetTexture() const{return m_texture;}

void _CMesh::SetVertex(_VERTEX* vtx, UINT num){
	if(m_vertex != 0x00){
		delete [] m_vertex;
		m_vertex = 0x00;
		m_vertex_num = 0;
	}
	m_vertex = new _VERTEX[num];
	m_vertex_num = num;
	for(UINT i = 0 ; i<num ; ++i){
		m_vertex[i] = vtx[i];
	}
}
void _CMesh::SetTexture(char** tex, UINT num){
	if(m_texture != 0x00){
		for(UINT i = 0 ; i<m_texture_num ; ++i){
			delete [] (m_texture[i]);
		}
		delete [] m_texture;
		m_texture = 0x00;
		m_texture_num = 0;
	}
	m_texture = new char*[num];
	m_texture_num = num;
	for(UINT i = 0 ; i<num ; ++i){
		UINT len = GetLength(tex[i])+1;
		m_texture[i] = new char[len];
		for(UINT j = 0 ; j<len ; ++j){
			m_texture[i][j] = tex[i][j];
		}
	}
}

void _CMesh::render(){
	if(m_pParent == 0x00){return;}
	_OBJECT obj = {
		m_vertex, m_vertex_num,
		m_texture, m_texture_num,
		m_pParent->GetWorldMatrix()
	};

	DrawMesh(obj);
}