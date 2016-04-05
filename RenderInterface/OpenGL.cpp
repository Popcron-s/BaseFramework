#include "OpenGL.h"

TYPE::TYPE _COpenGLRenderer::GetType(){
	return TYPE::OpenGL;
}

bool _COpenGLRenderer::Render(
	UINT width, UINT height, UINT* buf, 
	_OBJECT* obj_list, UINT object_num, _LIGHT* light_list, UINT light_num, _CAMERA* camera){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	GLfloat view_mat[16] = {
		camera->view_mat._11,camera->view_mat._12,camera->view_mat._13,camera->view_mat._14,
		camera->view_mat._21,camera->view_mat._22,camera->view_mat._23,camera->view_mat._24,
		camera->view_mat._31,camera->view_mat._32,camera->view_mat._33,camera->view_mat._34,
		camera->view_mat._41,camera->view_mat._42,camera->view_mat._43,camera->view_mat._44
	};
	for(UINT i = 0 ; i < object_num ; ++i){
		GLfloat world_mat[16] = {
			obj_list[i].world_mat._11,obj_list[i].world_mat._12,obj_list[i].world_mat._13,obj_list[i].world_mat._14,
			obj_list[i].world_mat._21,obj_list[i].world_mat._22,obj_list[i].world_mat._23,obj_list[i].world_mat._24,
			obj_list[i].world_mat._31,obj_list[i].world_mat._32,obj_list[i].world_mat._33,obj_list[i].world_mat._34,
			obj_list[i].world_mat._41,obj_list[i].world_mat._42,obj_list[i].world_mat._43,obj_list[i].world_mat._44};
		glLoadMatrixf(world_mat);
		glMultMatrixf(view_mat);
		glBegin(GL_TRIANGLE_STRIP);
			for(UINT j = 0; j<obj_list[i].vertex_num ; ++j){
				glVertex3f(obj_list[i].vertex[j].vertex.x,obj_list[i].vertex[j].vertex.y,obj_list[i].vertex[j].vertex.z);
			}
		glEnd();
	}
	glMatrixMode(GL_TEXTURE);
	glMatrixMode(GL_PROJECTION);
	GLfloat proj_mat[16] = {
		camera->proj_mat._11,camera->proj_mat._12,camera->proj_mat._13,camera->proj_mat._14,
		camera->proj_mat._21,camera->proj_mat._22,camera->proj_mat._23,camera->proj_mat._24,
		camera->proj_mat._31,camera->proj_mat._32,camera->proj_mat._33,camera->proj_mat._34,
		camera->proj_mat._41,camera->proj_mat._42,camera->proj_mat._43,camera->proj_mat._44
	};
	glLoadMatrixf(proj_mat);
	//glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

	glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,buf);
	
	return true;
}

bool _COpenGLRenderer::DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num){
	glViewport(0,0,width,height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	UINT* buf = new UINT[(width*height)];
	for(UINT i = 0 ; i<(width*height) ; ++i){
		buf[i] = 0x00;
	}
	for(UINT i = 0 ; i<display_num ; ++i){
		for(UINT x = display[i].x ; x<width ; ++x){
			for(UINT y = display[i].y ; y<height ; ++y){
				buf[(y*width)+x] = display[i].buf[(y*(display[i].width))+x];
			}
		}
	}
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, buf);
	delete [] buf;
	glFlush();
	return true;
}