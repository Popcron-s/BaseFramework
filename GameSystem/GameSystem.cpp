#include "GameSystem.h"
#include "..\\RenderInterface\\RenderInterface.h"
//UNIFY
void update(){
	_CGameSystem::GetSingleton()->update();
}

void SetBackBuffer(UINT x, UINT y){
	_oStream::GetSingleton()->SetSize(x,y);
}
UINT GetBackBufferX(){
	return _oStream::GetSingleton()->GetSizeX();
}
UINT GetBackBufferY(){
	return _oStream::GetSingleton()->GetSizeY();
}
void SetMainLoop(void (*loop)()){
	_CGameSystem::GetSingleton()->main_loop = loop;
}

#define CREATE_OBJECTSET(Class,Name)								\
Name Create##Name##(Object parent){									\
	Class* obj = new Class((_CObject*) parent);						\
	_CGameSystem::GetSingleton()->RegisterObject(obj);				\
	return (Name)obj;												\
}																	\
bool Release##Name##(Name obj){										\
	_CGameSystem::GetSingleton()->AllRemoveObject((Class*)obj);		\
	_CGameSystem::GetSingleton()->RemoveObject((Class*)obj);		\
	delete obj;														\
	return true;													\
}
/*
//Create Object
Object CreateObject(){
	_CObject* obj = new _CObject;
	_CGameSystem::GetSingleton()->RegisterObject(obj);
	return (Object)obj;
}
bool ReleaseObject(Object obj){
	_CGameSystem::GetSingleton()->AllRemoveObject((_CObject*)obj);
	_CGameSystem::GetSingleton()->RemoveObject((_CObject*)obj);
	delete obj;
	return true;
}
*/
CREATE_OBJECTSET(_CObject,Object);
CREATE_OBJECTSET(_CMesh,Mesh);

//Create Camera
Camera CreateCamera(){
	return _oStream::GetSingleton()->CreateCamera();
}
bool ReleaseCameraUsePointer(Camera cam){
	return _oStream::GetSingleton()->ReleaseCamera((_CCamera*)cam);
}
bool ReleaseCameraUseID(UINT ID){
	return _oStream::GetSingleton()->ReleaseCamera(_oStream::GetSingleton()->SearchCamera(ID));
}

bool SetGraphicRenderer(RENDER_TYPE::RENDER_TYPE type){
	return SetGraphicRendererInterface(type);
}
RENDER_TYPE::RENDER_TYPE GetGraphicRenderer(){
	return GetGraphicRendererInterface();
}
