#pragma once

#define WINGDIAPI __declspec(dllimport)
#define APIENTRY __stdcall
#define CALLBACK __stdcall
//#include <Windows.h>
//#include <stdio.h>
#include <gl\\GL.h>
#include <gl\\GLU.h>

#include "..\\ResourceManager\\ResourceManager.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "Interface.h"

class _COpenGLRenderer : public _CInterface{
public:
	_COpenGLRenderer(){
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		//glDrawBuffer(GL_BACK);
		//glReadBuffer(GL_BACK);
		//glEnable(GL_LIGHTING);
		//glEnable(GL_CULL_FACE);
		//glShadeModel(GL_SMOOTH);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		AddResource("temp.bmp");
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		UINT tex_width = 0, tex_height = 0, *tex_buf = 0x00;
		GetResource("temp.bmp", &tex_width, &tex_height, &tex_buf);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0,GL_RGBA, GL_UNSIGNED_BYTE, tex_buf);
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