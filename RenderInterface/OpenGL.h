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
private:
	_matrix4x4 view_mat;
	_matrix4x4 proj_mat;
public:
	_COpenGLRenderer(){
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glDrawBuffer(GL_BACK);
		//glReadBuffer(GL_BACK);
		glDisable(GL_LIGHTING);
		//glEnable(GL_CULL_FACE);
		//glShadeModel(GL_SMOOTH);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	~_COpenGLRenderer(){}

public:
	RENDER_TYPE::RENDER_TYPE GetType();
	bool Clear(_CAMERA camera);
	bool DrawMesh(_OBJECT obj);
	bool Render(UINT width, UINT height, UINT* buf, _LIGHT* light_list, UINT light_num);
	bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num);
	//load texture
	//remove texture
};