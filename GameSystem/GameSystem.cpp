#include "GameSystem.h"

//UNIFY
void update(){
	_CGameSystem::GetSingleton()->Update();
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

//Create Object
void* CreateObject(void (*func)()){
	_CObject* obj = _CGameSystem::GetSingleton()->CreateObject();
	obj->update = func;
	return (void*)obj;
}
bool ReleaseObject(void* obj){
	return _CGameSystem::GetSingleton()->ReleaseObject((_CObject*)obj);
}

//Create Camera
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
