#include "GameSystem.h"

_defaultvertex* GetVertex(Mesh mesh){
	_CMesh* t_mesh = (_CMesh*)mesh;
	return t_mesh->GetVertex();
}
UINT GetVertexNum(Mesh mesh){
	_CMesh* t_mesh = (_CMesh*)mesh;
	return t_mesh->GetVertexNumber();
}
void SetVertex(Mesh mesh, _defaultvertex* vtx, UINT vtx_n){
	_CMesh* t_mesh = (_CMesh*)mesh;
	return t_mesh->SetVertex(vtx,vtx_n);
}

char** GetTexture(Mesh mesh){
	_CMesh* t_mesh = (_CMesh*)mesh;
	return t_mesh->GetTexture();
}
UINT GetTextureNum(Mesh mesh){
	_CMesh* t_mesh = (_CMesh*)mesh;
	return t_mesh->GetTextureNumber();
}
void SetTexture(Mesh mesh, char** tex, UINT tex_n){
	_CMesh* t_mesh = (_CMesh*)mesh;
	return t_mesh->SetTexture(tex,tex_n);
}