#include "ostream.h"
#include "MainSystem.h"

_CCamera::_CCamera(){
	m_pos = {0.0f, 0.0f};
	m_size = {1.0f, 1.0f};

	m_able = true;

	m_eye = {0.0f, 0.0f, 1.0f};
	m_lookat = {0.0f, 0.0f, 0.0f};
	m_up = {0.0f, 1.0f, 0.0f};

	m_view = {1.0f, 0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f, 0.0f,
			  0.0f, 0.0f, 1.0f, 0.0f,
			  0.0f, 0.0f, 0.0f, 1.0f};

	m_x = {-1.0f, 1.0f};
	m_y = {-1.0f, 1.0f};
	m_z = {-1.0f, 1.0f};

	m_proj = {1.0f, 0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f, 0.0f,
			  0.0f, 0.0f, 1.0f, 0.0f,
			  0.0f, 0.0f, 0.0f, 1.0f};

	SetViewMatrix();
	SetOrthoProjMatrix();

	m_Object_List = 0x00;
	m_Object_num = 0;
}
_CCamera::~_CCamera(){
	RemoveAllObject();
}

_vector2 _CCamera::GetSize() const{return m_size;}
_vector2 _CCamera::GetPosition() const{return m_pos;}
void _CCamera::SetSize(_vector2 s){m_size = s;}
void _CCamera::SetPosition(_vector2 p){m_pos = p;}

bool _CCamera::Getable() const{return m_able;}
void _CCamera::Enable(){m_able = true;}
void _CCamera::Disable(){m_able = false;}

void _CCamera::Render(_DISPLAY* display){
	//Clear buffer
	_CAMERA camera = {m_view, m_proj};
	RenderBufferClear(camera);

	//Render Display
	_LIST<_CRenderObject>* t_node = m_Object_List;
	while(t_node != 0x00){
		t_node->_node->render();
		t_node = t_node->_next;
	}

	//Write Display buffer
	display->x = m_pos.x;
	display->y = m_pos.y;
	display->width = m_size.x;
	display->height = m_size.y;
	display->buf = new UINT[(display->width * display->height)];
	RenderGraphic(display->width, display->height, display->buf, 0x00, 0);
}

_vector3 _CCamera::GetEye() const{return m_eye;}
_vector3 _CCamera::GetLookat() const{return m_lookat;}
_vector3 _CCamera::GetUp() const{return m_up;}
void _CCamera::SetEye(_vector3 e){m_eye = e;}
void _CCamera::SetLookat(_vector3 l){m_lookat = l;}
void _CCamera::SetUp(_vector3 u){m_up = u;}
void _CCamera::SetViewMatrix(){
	//z axis : normalize(eye-lookat)
	//_vector3 z_axis = {m_eye.x-m_lookat.x, m_eye.y-m_lookat.y, m_eye.z-m_lookat.z};
	_vector3 z_axis = {m_lookat.x-m_eye.x, m_lookat.y-m_eye.y, m_lookat.z-m_eye.z};
	FLOAT size = sqrt((z_axis.x*z_axis.x)+(z_axis.y*z_axis.y)+(z_axis.z*z_axis.z));
	z_axis.x /= size; z_axis.y /= size; z_axis.z /= size;
	//x axis : normalize(cross(z_axis, up));
	_vector3 x_axis = { (z_axis.y*m_up.z)-(z_axis.z*m_up.y),
						(z_axis.z*m_up.x)-(z_axis.x*m_up.z),
						(z_axis.x*m_up.y)-(z_axis.y*m_up.x)};
	size = sqrt((x_axis.x*x_axis.x)+(x_axis.y*x_axis.y)+(x_axis.z*x_axis.z));
	x_axis.x /= size; x_axis.y /= size; x_axis.z /= size;
	//y axis : normalize(cross(x_axis, z_axis));
	_vector3 y_axis = { (x_axis.y*z_axis.z)-(x_axis.z*z_axis.y),
						(x_axis.z*z_axis.x)-(x_axis.x*z_axis.z),
						(x_axis.x*z_axis.y)-(x_axis.y*z_axis.x)};
	size = sqrt((y_axis.x*y_axis.x)+(y_axis.y*y_axis.y)+(y_axis.z*y_axis.z));
	y_axis.x /= size; y_axis.y /= size; y_axis.z /= size;
	//pos : dot(x_axis,eye) dot(y_axis,eye) dot(z_axis,eye)
	_vector3 pos = {-((x_axis.x*m_eye.x)+(x_axis.y*m_eye.y)+(x_axis.z*m_eye.z)),
					-((y_axis.x*m_eye.x)+(y_axis.y*m_eye.y)+(y_axis.z*m_eye.z)),
					-((z_axis.x*m_eye.x)+(z_axis.y*m_eye.y)+(z_axis.z*m_eye.z))};

	//setting
	m_view = {  x_axis.x, y_axis.x, z_axis.x, 0,
				x_axis.y, y_axis.y, z_axis.y, 0,
				x_axis.z, y_axis.z, z_axis.z, 0,
				   pos.x,    pos.y,    pos.z, 1};
	/*m_view._11 = x_axis.x; m_view._12 = y_axis.x; m_view._13 = z_axis.x; m_view._14 = 0;
	m_view._21 = x_axis.y; m_view._22 = y_axis.y; m_view._23 = z_axis.y; m_view._24 = 0;
	m_view._31 = x_axis.z; m_view._32 = y_axis.z; m_view._33 = z_axis.z; m_view._34 = 0;
	m_view._41 = pos.x;	   m_view._42 = pos.y;	  m_view._43 = pos.z;	 m_view._44 = 1;*/
}

_vector2 _CCamera::GetProjXRange() const{return m_x;}
_vector2 _CCamera::GetProjYRange() const{return m_y;}
_vector2 _CCamera::GetProjZRange() const{return m_z;}
void _CCamera::SetProjectionRange(_vector2 x, _vector2 y, _vector2 z){
	m_x = x;
	m_y = y;
	m_z = z;
}
void _CCamera::SetPerspectiveFov(FLOAT aspect, FLOAT fov, FLOAT n, FLOAT f){
	FLOAT y = n*tan(fov/2);
	FLOAT x = y*aspect;
	m_y = {-y,y};
	m_x = {-x,x};
	m_z = {n,f};
}
void _CCamera::SetOrthoProjMatrix(){
	_matrix4x4 ortho = {
		2/(m_x.y-m_x.x), 0,0,0,
		0, 2/(m_y.y-m_y.x),0,0,
		0,0, 2/(m_z.y-m_z.x),0,
		-((m_x.y+m_x.x)/(m_x.y-m_x.x)),-((m_y.y+m_y.x)/(m_y.y-m_y.x)),-((m_z.y+m_z.x)/(m_z.y-m_z.x)),1
	};
	m_proj = ortho;
}
void _CCamera::SetPerspectiveProjMatrix(){
	/*_matrix4x4 pers = {
		(2*m_z.x)/(m_x.y-m_x.x), 0, 0, 0,
		0,(2*m_z.x)/(m_y.y-m_y.x),0,0,
		(m_x.y+m_x.x)/(m_x.y-m_x.x),(m_y.y+m_y.x)/(m_y.y-m_y.x),((m_z.y+m_z.x)/(m_z.y-m_z.x)),-1,
		0,0,((2*m_z.y*m_z.x)/(m_z.y-m_z.x)),0
	};*/
	_matrix4x4 pers = {
		(2*m_z.x)/(m_x.y-m_x.x),0,0,0,
		0,(2*m_z.x)/(m_y.y-m_y.x),0,0,
		(m_x.y+m_x.x)/(m_x.y-m_x.x),(m_y.y+m_y.x)/(m_y.y-m_y.x),((m_z.y+m_z.x)/(m_z.y-m_z.x)),1,
		0,0,-((2*m_z.y*m_z.x)/(m_z.y-m_z.x)),0
	};
	m_proj = pers;
}
