#include "RenderInterface.h"

#include "Interface.h"

bool Render(UINT width, UINT height, UINT* buf, 
	_OBJECT* obj_list, UINT object_num, 
	_LIGHT* light_list, UINT light_num, 
	_CAMERA* camera){
	return _CInterface::GetSingleton()->Render(width, height, buf, obj_list, object_num, light_list, light_num, camera);
}
bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num){
	return _CInterface::GetSingleton()->DrawDisplay(width, height, display, display_num);
}