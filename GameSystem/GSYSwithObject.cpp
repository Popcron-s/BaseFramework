#include "GameSystem.h"

//Setting Object
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
void SetPosition(Object obj, _vector3 v){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->SetPosition(v);
}
void SetRotation(Object obj, _vector3 v){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->SetRotation(v);
}
void SetScale(Object obj, _vector3 v){
	_CObject* t_obj = (_CObject*)obj;
	return t_obj->SetScale(v);
}
void AlterPosition(Object obj, _vector3 v){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {t_obj->GetPosition().x+v.x,t_obj->GetPosition().y+v.y,t_obj->GetPosition().z+v.z};
	return t_obj->SetPosition(t_v);
}
void AlterRotation(Object obj, _vector3 v){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {t_obj->GetRotation().x+v.x,t_obj->GetRotation().y+v.y,t_obj->GetRotation().z+v.z};
	return t_obj->SetRotation(t_v);
}
void AlterScale(Object obj, _vector3 v){
	_CObject* t_obj = (_CObject*)obj;
	_vector3 t_v = {t_obj->GetScale().x+v.x,t_obj->GetScale().y+v.y,t_obj->GetScale().z+v.z};
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