#include "RenderInterface.h"

#include "Interface.h"

bool SetGraphicRendererInterface(RENDER_TYPE::RENDER_TYPE type){
	_CInterface::SetType(type);
	if(_CInterface::GetSingleton()->GetType() == type){return true;}
	else{return false;}
}

RENDER_TYPE::RENDER_TYPE GetGraphicRendererInterface(){
	return _CInterface::GetSingleton()->GetType();
}

bool RenderBufferClear(_CAMERA camera){
	return _CInterface::GetSingleton()->Clear(camera);
}
bool DrawMesh(_OBJECT obj){
	return _CInterface::GetSingleton()->DrawMesh(obj);
}
bool RenderGraphic(UINT width, UINT height, UINT* buf, 
	_LIGHT* light_list, UINT light_num){
	return _CInterface::GetSingleton()->Render(width, height, buf, light_list, light_num);
}
bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num){
	return _CInterface::GetSingleton()->DrawDisplay(width, height, display, display_num);
}