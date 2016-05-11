#include "OpenGL.h"

#define __OPERATOR_MATRIX(m) {m._11, m._12, m._13, m._14, m._21, m._22, m._23, m._24, \
						m._31, m._32, m._33, m._34, m._41, m._42, m._43, m._44}

RENDER_TYPE::RENDER_TYPE _COpenGLRenderer::GetType(){
	return RENDER_TYPE::OpenGL;
}

bool _COpenGLRenderer::Clear(_CAMERA camera){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	view_mat = camera.view_mat;
	proj_mat = camera.proj_mat;
	//view_mat[16] = __OPERATOR_MATRIX(camera.view_mat);
	//proj_mat[16] = __OPERATOR_MATRIX(camera.proj_mat);
	glPushMatrix();
	return true;
}

bool _COpenGLRenderer::DrawMesh(_OBJECT obj){
	glMatrixMode(GL_MODELVIEW);
	GLfloat world[16] = __OPERATOR_MATRIX(obj.world_mat);
	GLfloat view[16] =  __OPERATOR_MATRIX(view_mat);
	glLoadMatrixf(world);
	glMultMatrixf(view);
	
	for(UINT i = 0 ; i<obj.texture_num ; ++i){
		UINT tex_w, tex_h, *tex_buf;
		if(!GetResource(obj.texture[i], &tex_w, &tex_h, &tex_buf)){
			if(!AddResource(obj.texture[i])){continue;}
			GetResource(obj.texture[i], &tex_w, &tex_h, &tex_buf);
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_w, tex_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_buf);
		glEnable(GL_TEXTURE_2D);
	}
	glBegin(GL_TRIANGLE_STRIP);
	for(UINT i = 0; i<obj.vertex_num ; ++i){
		//glNormal3f();
		glColor4f(obj.vertex[i].diffuse.x, obj.vertex[i].diffuse.y, obj.vertex[i].diffuse.z, obj.vertex[i].diffuse.w);
		glTexCoord2f(obj.vertex[i].tex.x, obj.vertex[i].tex.y);
		glVertex3f(obj.vertex[i].pos.x,obj.vertex[i].pos.y,obj.vertex[i].pos.z);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	return true;
}

bool _COpenGLRenderer::Render(
	UINT width, UINT height, UINT* buf, 
	_LIGHT* light_list, UINT light_num){
	//Lighting and etc...

	glMatrixMode(GL_PROJECTION);
	//GLfloat view_mat[16] = __OPERATOR_MATRIX(camera->view_mat);
	GLfloat proj[16] = __OPERATOR_MATRIX(proj_mat);
	//glLoadMatrixf(view_mat);
	//glMultMatrixf(proj_mat);
	glLoadMatrixf(proj);
	//glMultMatrixf(view_mat);

	glReadPixels(0,0,width,height,GL_RGBA,GL_UNSIGNED_BYTE,buf);
	return true;
}

bool _COpenGLRenderer::DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	UINT* buf = new UINT[(width*height)];
	for(UINT i = 0 ; i<(width*height) ; ++i){
		buf[i] = 0x00;
	}
	for(UINT i = 0 ; i<display_num ; ++i){
		INT w = (width  <= (display[i].width +display[i].x))?width :(display[i].width +display[i].x); 
		INT h = (height <= (display[i].height+display[i].y))?height:(display[i].height+display[i].y); 
		for(INT y = (display[i].y<0)?0:display[i].y ; y<h ; ++y){
			for(INT x = (display[i].x<0)?0:display[i].x ; x<w ; ++x){
				//if(((display[i].buf[((y-display[i].y)*(display[i].width))+(x-display[i].x)]>>24) & 0xFF) != 0xFF){continue;}
				buf[(y*width)+x] = display[i].buf[((y-display[i].y)*(display[i].width))+(x-display[i].x)];
			}
		}
	}
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, buf);
	delete [] buf;
	glFlush();
	return true;
}