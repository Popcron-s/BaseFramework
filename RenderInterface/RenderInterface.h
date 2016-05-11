#pragma once

#ifdef RENDERINTERFACE_EXPORTS
#define RINTER_API __declspec(dllexport)
#else
#define RINTER_API __declspec(dllimport)
#pragma comment(lib,"..\\Release\\RenderInterface.lib")
#endif

#include "..\\Common\\Variable.h"

extern "C"{
	RINTER_API bool SetGraphicRendererInterface(RENDER_TYPE::RENDER_TYPE);
	RINTER_API RENDER_TYPE::RENDER_TYPE GetGraphicRendererInterface();
	RINTER_API bool RenderBufferClear(_CAMERA camera);
	RINTER_API bool DrawMesh(_OBJECT obj);
	RINTER_API bool RenderGraphic(UINT width, UINT height, UINT* buf, 
		_LIGHT* light_list, UINT light_num);
	RINTER_API bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num);
}