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
		for(UINT j = 0 ; j<obj_list[i].texture_num ; ++j){
			UINT tex_w, tex_h, *tex_buf;
			if(!GetResource(obj_list[i].texture[j].text, &tex_w, &tex_h, &tex_buf)){
				if(!AddResource(obj_list[i].texture[j].text)){continue;}
				GetResource(obj_list[i].texture[j].text, &tex_w, &tex_h, &tex_buf);
			}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_w, tex_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_buf);
			glEnable(GL_TEXTURE_2D);
		}
		glBegin(GL_TRIANGLE_STRIP);
			for(UINT j = 0; j<obj_list[i].vertex_num ; ++j){
				//glNormal3f();
				glColor4f(obj_list[i].vertex[j].diffuse.x, obj_list[i].vertex[j].diffuse.y, obj_list[i].vertex[j].diffuse.z, obj_list[i].vertex[j].diffuse.w);
				glTexCoord2f(obj_list[i].vertex[j].tex.x, obj_list[i].vertex[j].tex.y);
				glVertex3f(obj_list[i].vertex[j].pos.x,obj_list[i].vertex[j].pos.y,obj_list[i].vertex[j].pos.z);
			}
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	//glMatrixMode(GL_TEXTURE);
	glMatrixMode(GL_PROJECTION);
	GLfloat proj_mat[16] = {
		camera->proj_mat._11,camera->proj_mat._12,camera->proj_mat._13,camera->proj_mat._14,
		camera->proj_mat._21,camera->proj_mat._22,camera->proj_mat._23,camera->proj_mat._24,
		camera->proj_mat._31,camera->proj_mat._32,camera->proj_mat._33,camera->proj_mat._34,
		camera->proj_mat._41,camera->proj_mat._42,camera->proj_mat._43,camera->proj_mat._44
	};
	//glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -10.0f, 10.0f);
	//gluPerspective((3.141592/8), 800.0f/600.0f, 1.0f, 10.0f);
	glLoadMatrixf(proj_mat);

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
		for(INT x = (display[i].x<0)?0:display[i].x ; x<(INT)display[i].width ; ++x){
			for(INT y = (display[i].y<0)?0:display[i].y ; y<(INT)display[i].height ; ++y){
				if(((display[i].buf[((y-display[i].y)*(display[i].width))+(x-display[i].x)]>>24) & 0xFF) != 0xFF){continue;}
				buf[(y*width)+x] = display[i].buf[((y-display[i].y)*(display[i].width))+(x-display[i].x)];
			}
		}
	}
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, buf);
	delete [] buf;
	glFlush();
	return true;
}