#include "GameSystem.h"

//Setting Camera
bool RegisterObjectForCamera(Camera cam, Object obj){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->RegisterObject((_CRenderObject*)obj);
}
bool RemoveObjectForCamera(Camera cam, Object obj){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->RemoveObject((_CRenderObject*)obj);
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

_vector2 GetProjXRange(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetProjXRange();
}
_vector2 GetProjYRange(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetProjYRange();
}
_vector2 GetProjZRange(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->GetProjZRange();
}
void SetProjectionRange(Camera cam, _vector2 x, _vector2 y, _vector2 z){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetProjectionRange(x,y,z);
}
void SetPerspectiveFov(Camera cam, FLOAT asp, FLOAT fov, FLOAT n, FLOAT f){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetPerspectiveFov(asp, fov, n, f);
}
void SetOrthoProjMatrix(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetOrthoProjMatrix();
}
void SetPerspectiveProjMatrix(Camera cam){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->SetPerspectiveProjMatrix();
}