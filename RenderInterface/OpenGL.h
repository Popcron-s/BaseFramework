#pragma once

#include <Windows.h>
#include <gl\\GL.h>
#include <gl\\GLU.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "Interface.h"

class _COpenGLRenderer : public _CInterface{
public:
	_COpenGLRenderer(){
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK);
	}
	~_COpenGLRenderer(){}

public:
	TYPE::TYPE GetType();
	bool Render(UINT width, UINT height, UINT* buf, 
		_OBJECT* obj_list, UINT object_num, 
		_LIGHT* light_list, UINT light_num, 
		_CAMERA* camera);
	bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num);
	//load texture
	//remove texture
};