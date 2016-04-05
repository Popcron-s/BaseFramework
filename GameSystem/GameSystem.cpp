#include "GameSystem.h"

void update(){
	_CGameSystem::GetSingleton()->Update();
}

void* CreateObject(void (*func)()){
	_CObject* obj = _CGameSystem::GetSingleton()->CreateObject();
	obj->update = func;
	return (void*)obj;
}
bool ReleaseObject(void* obj){
	return _CGameSystem::GetSingleton()->ReleaseObject((_CObject*)obj);
}

bool RegisterUpdate(void* pointer){
	_CObject* obj = (_CObject*)pointer;
	return _CGameSystem::GetSingleton()->RegisterUpdate(obj->update);
}
bool RemoveUpdate(void* pointer){
	_CObject* obj = (_CObject*)pointer;
	return _CGameSystem::GetSingleton()->RemoveUpdate(obj->update);
}

void* CreateCamera(){
	_CCamera* cam = new _CCamera;
	return cam;
}
bool ReleaseCameraUsePointer(void* cam){
	delete cam;
	return true;
}
bool ReleaseCameraUseID(UINT ID){
	_CCamera* cam = _CGameSystem::GetSingleton()->SearchCamera(ID);
	delete cam;
	return true;
}

void SetBackBuffer(UINT x, UINT y){
	_CGameSystem::GetSingleton()->SetSize(x,y);
}
UINT GetBackBufferX(){
	return _CGameSystem::GetSingleton()->GetSizeX();
}
UINT GetBackBufferY(){
	return _CGameSystem::GetSingleton()->GetSizeY();
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

bool RegisterObjectForCamera(Camera cam, Object obj){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->RegisterObject((_CObject*)obj);
}
bool RemoveObjectForCamera(Camera cam, Object obj){
	_CCamera* t_cam = (_CCamera*)cam;
	return t_cam->RemoveObject((_CObject*)obj);
}