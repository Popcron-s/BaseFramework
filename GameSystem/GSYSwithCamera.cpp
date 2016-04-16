#include "GameSystem.h"

//Setting Camera
bool RegisterObjectForCamera(Camera cam, Object obj){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->RegisterObject((_CObject*)obj);
}
bool RemoveObjectForCamera(Camera cam, Object obj){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->RemoveObject((_CObject*)obj);
}

_vector2 GetCameraSize(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetSize();
}
_vector2 GetCameraPosition(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetPosition();
}
void SetCameraSize(Camera cam, _vector2 size){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetSize(size);
}
void SetCameraPosition(Camera cam, _vector2 pos){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetPosition(pos);
}

_vector3 GetEye(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetEye();
}
_vector3 GetLookat(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetLookat();
}
_vector3 GetUp(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetUp();
}
void SetEye(Camera cam, _vector3 eye){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetEye(eye);
}
void SetLookat(Camera cam, _vector3 la){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetLookat(la);
}
void SetUp(Camera cam, _vector3 up){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetUp(up);
}
void SetViewMatrix(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetViewMatrix();
}

_vector3 GetNearOrtho(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetNearOrtho();
}
_vector3 GetFarOrtho(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetFarOrtho();
}
void SetOrtho(Camera cam, _vector3 n, _vector3 f){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetOrtho(n,f);
}
void SetOrthoProjMatrix(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetOrthoProjMatrix();
}

_vector2 GetAspect(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetAspect();
}
FLOAT GetNearZ(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetNearZ();
}
FLOAT GetFarZ(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetFarZ();
}
void SetPerspective(Camera cam, _vector2 asp, FLOAT n, FLOAT f){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetPerspective(asp, n, f);
}
void SetPerspectiveProjMatrix(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetPerspectiveProjMatrix();
}