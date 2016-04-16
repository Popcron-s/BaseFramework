#include "GameSystem.h"

//Setting Object
bool RegisterUpdate(void* pointer){
	_CObject* obj = (_CObject*)pointer;
	return _CGameSystem::GetSingleton()->RegisterUpdate(obj->update);
}
bool RemoveUpdate(void* pointer){
	_CObject* obj = (_CObject*)pointer;
	return _CGameSystem::GetSingleton()->RemoveUpdate(obj->update);
}

_vector3 GetPosition(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->GetPosition();
}
_vector3 GetRotation(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->GetRotation();
}
_vector3 GetScale(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->GetScale();
}
void SetPosition(Object obj, FLOAT x, FLOAT y, FLOAT z){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {x,y,z};
	return t_obj->SetPosition(t_v);
}
void SetRotation(Object obj, FLOAT x, FLOAT y, FLOAT z){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {x,y,z};
	return t_obj->SetRotation(t_v);
}
void SetScale(Object obj, FLOAT x, FLOAT y, FLOAT z){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {x,y,z};
	return t_obj->SetScale(t_v);
}
void AlterPosition(Object obj, FLOAT x, FLOAT y, FLOAT z){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {t_obj->GetPosition().x+x,t_obj->GetPosition().y+y,t_obj->GetPosition().z+z};
	return t_obj->SetPosition(t_v);
}
void AlterRotation(Object obj, FLOAT x, FLOAT y, FLOAT z){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {t_obj->GetRotation().x+x,t_obj->GetRotation().y+y,t_obj->GetRotation().z+z};
	return t_obj->SetRotation(t_v);
}
void AlterScale(Object obj, FLOAT x, FLOAT y, FLOAT z){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {t_obj->GetScale().x+x,t_obj->GetScale().y+y,t_obj->GetScale().z+z};
	return t_obj->SetScale(t_v);
}

_matrix4x4 GetWorldMatrix(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->GetWorldMatrix();
}
void SetWorldMatrix(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->SetWorldMatrix();
}

_defaultvertex* GetVertex(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->GetVertex();
}
UINT GetVertexNum(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->GetVertexNumber();
}
bool SetVertex(Object obj, _defaultvertex* ver, UINT num){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->SetVertex(ver, num);
}

_TEXT* GetTexture(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->GetTexture();
}
UINT GetTextureNum(Object obj){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->GetTextureNumber();
}
bool SetTexture(Object obj, _TEXT* tex, UINT num){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->SetTexture(tex, num);
}