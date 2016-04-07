#pragma once

#ifdef RENDERINTERFACE_EXPORTS
#define RINTER_API __declspec(dllexport)
#else
#define RINTER_API __declspec(dllimport)
#pragma comment(lib,"..\\Release\\RenderInterface.lib")
#endif

#include "..\\Common\\Variable.h"

extern "C"{
	RINTER_API bool Render(UINT width, UINT height, UINT* buf, 
		_OBJECT* obj_list, UINT object_num, 
		_LIGHT* light_list, UINT light_num, 
		_CAMERA* camera);
	RINTER_API bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num);
}