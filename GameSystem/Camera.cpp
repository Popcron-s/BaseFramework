#include "Object.h"
#include "MainSystem.h"

_CCamera::_CCamera(){
	m_eye = {0.0f, 0.0f, 1.0f};
	m_lookat = {0.0f, 0.0f, 0.0f};
	m_up = {0.0f, 1.0f, 0.0f};

	m_aspect = {1.0f, 1.0f};
	m_z = {1.0f, 10.0f};

	m_near_ortho = {-1.0f, -1.0f, -1.0f};
	m_far_ortho = {1.0f, 1.0f, 1.0f};

	m_view = {1.0f, 0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f, 0.0f,
			  0.0f, 0.0f, 1.0f, 0.0f,
			  0.0f, 0.0f, 0.0f, 1.0f};
	m_proj = {1.0f, 0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f, 0.0f,
			  0.0f, 0.0f, 1.0f, 0.0f,
			  0.0f, 0.0f, 0.0f, 1.0f};

	m_Object_List = 0x00;

	m_pos = {0.0f, 0.0f};
	m_size = {1.0f, 1.0f};

	m_able = true;

	_CGameSystem::GetSingleton()->RegisterCamera(this);

	SetViewMatrix();
	SetPerspectiveProjMatrix();
}
_CCamera::~_CCamera(){
	while(m_Object_List != 0x00){
		_LIST<_CObject>* t_node = m_Object_List;
		m_Object_List = m_Object_List->_next;
		delete t_node;
	}
	
	_CGameSystem::GetSingleton()->RemoveCamera(this);
}

bool _CCamera::RegisterObject(_CObject* obj){
	_LIST<_CObject>** t_node = &m_Object_List;
	while((*t_node) != 0x00){
		if((*t_node)->_node == obj){return false;}
		t_node = &((*t_node)->_next);
	}
	(*t_node) = new _LIST<_CObject>;
	(*t_node)->_node = obj;
	(*t_node)->_next = 0x00;
	return true;
}
bool _CCamera::RemoveObject(_CObject* obj){
	_LIST<_CObject>** t_node = &m_Object_List;
	_LIST<_CObject>** prev_node = 0x00;
	while((*t_node) != 0x00){
		if((*t_node)->_node == obj){
			_LIST<_CObject>* d_node = (*t_node);
			if(prev_node == 0x00){m_Object_List = (d_node->_next);}
			else{(*prev_node)->_next = d_node->_next;}
			delete d_node;
			return true;
		}
		prev_node = t_node;
		t_node = &((*t_node)->_next);
	}
	return false;
}

_vector2 _CCamera::GetSize() const{return m_size;}
_vector2 _CCamera::GetPosition() const{return m_pos;}
void _CCamera::SetSize(_vector2 s){m_size = s;}
void _CCamera::SetPosition(_vector2 p){m_pos = p;}

_vector3 _CCamera::GetEye() const{return m_eye;}
_vector3 _CCamera::GetLookat() const{return m_lookat;}
_vector3 _CCamera::GetUp() const{return m_up;}
void _CCamera::SetEye(_vector3 e){m_eye = e;}
void _CCamera::SetLookat(_vector3 l){m_lookat = l;}
void _CCamera::SetUp(_vector3 u){m_up = u;}
void _CCamera::SetViewMatrix(){
	//z axis : normalize(eye-lookat)
	_vector3 z_axis = {m_eye.x-m_lookat.x, m_eye.y-m_lookat.y, m_eye.z-m_lookat.z};
	FLOAT size = sqrt((z_axis.x*z_axis.x)+(z_axis.y*z_axis.y)+(z_axis.z*z_axis.z));
	z_axis.x /= size; z_axis.y /= size; z_axis.z /= size;
	//x axis : normalize(cross(z_axis, up));
	_vector3 x_axis = { (z_axis.y*m_up.z)-(z_axis.z*m_up.y),
						(z_axis.z*m_up.x)-(z_axis.x*m_up.z),
						(z_axis.x*m_up.y)-(z_axis.y*m_up.x)};
	size = sqrt((x_axis.x*x_axis.x)+(x_axis.y*x_axis.y)+(x_axis.z*x_axis.z));
	x_axis.x /= size; x_axis.y /= size; x_axis.z /= size;
	//y axis : normalize(cross(z_axis, x_axis));
	_vector3 y_axis = { (z_axis.y*x_axis.z)-(z_axis.z*x_axis.y),
						(z_axis.z*x_axis.x)-(z_axis.x*x_axis.z),
						(z_axis.x*x_axis.y)-(z_axis.y*x_axis.x)};
	size = sqrt((y_axis.x*y_axis.x)+(y_axis.y*y_axis.y)+(y_axis.z*y_axis.z));
	y_axis.x /= size; y_axis.y /= size; y_axis.z /= size;
	//pos : dot(x_axis,eye) dot(y_axis,eye) dot(z_axis,eye)
	_vector3 pos = {-((x_axis.x*m_eye.x)+(x_axis.y*m_eye.y)+(x_axis.z*m_eye.z)),
					-((y_axis.x*m_eye.x)+(y_axis.y*m_eye.y)+(y_axis.z*m_eye.z)),
					-((z_axis.x*m_eye.x)+(z_axis.y*m_eye.y)+(z_axis.z*m_eye.z))};

	//setting
	m_view._11 = x_axis.x; m_view._12 = y_axis.x; m_view._13 = z_axis.x; m_view._14 = 0;
	m_view._21 = x_axis.y; m_view._22 = y_axis.y; m_view._23 = z_axis.y; m_view._24 = 0;
	m_view._31 = x_axis.z; m_view._32 = y_axis.z; m_view._33 = z_axis.z; m_view._34 = 0;
	m_view._41 = pos.x;	   m_view._42 = pos.y;	  m_view._43 = pos.z;	 m_view._44 = 1;
}

_vector3 _CCamera::GetNearOrtho() const{return m_near_ortho;}
_vector3 _CCamera::GetFarOrtho() const{return m_far_ortho;}
_vector2 _CCamera::GetAspect() const{return m_aspect;}
void _CCamera::SetOrtho(_vector3 st, _vector3 ed){
	m_near_ortho = st;
	m_far_ortho = ed;
}
void _CCamera::SetOrthoProjMatrix(){
	_vector3 pos = {
		-((m_far_ortho.x+m_near_ortho.x)/(m_far_ortho.x-m_near_ortho.x)),
		-((m_far_ortho.y+m_near_ortho.y)/(m_far_ortho.y-m_near_ortho.y)),
		-((m_far_ortho.z+m_near_ortho.z)/(m_far_ortho.z-m_near_ortho.z))
	};
	_matrix4x4 ortho = {
		2/(m_far_ortho.x-m_near_ortho.x), 0, 0, 0,
		0, 2/(m_far_ortho.y-m_near_ortho.y), 0, 0,
		0, 0, -2/(m_far_ortho.z-m_near_ortho.z), 0,
		pos.x, pos.y, pos.z, 1
	};
	m_proj = ortho;
}

FLOAT _CCamera::GetNearZ() const{return m_z.x;}
FLOAT _CCamera::GetFarZ() const{return m_z.y;}
void _CCamera::SetPerspective(_vector2 asp, FLOAT near_z, FLOAT far_z){
	m_aspect = asp;
	//FLOAT aspect = asp.x/asp.y;
	//m_aspect.x = near_z*aspect;
	//m_aspect.y = near_z;
	m_z.x = near_z;
	m_z.y = far_z;
}
void _CCamera::SetPerspectiveProjMatrix(){
	_matrix4x4 pers = {
		(2*m_z.x)/m_aspect.x, 0, 0, 0,
		0,(2*m_z.x)/m_aspect.y,0,0,
		0,0,-((m_z.y+m_z.x)/(m_z.y-m_z.x)),-1,
		0,0,-((2*m_z.y*m_z.x)/(m_z.y-m_z.x)),0
	};
	m_proj = pers;
}

bool _CCamera::Getable() const{return m_able;}
void _CCamera::Enable(){m_able = true;}
void _CCamera::Disable(){m_able = false;}

void _CCamera::Render(_DISPLAY* display){
	_LIST<_CObject>* t_node = m_Object_List;
	UINT obj_num = 0;
	while(t_node != 0x00){
		++obj_num;
		t_node = t_node->_next;
	}
	_OBJECT* obj_list = new _OBJECT[obj_num];
	t_node = m_Object_List;
	for(UINT i = 0 ;i<obj_num ; ++i){
		obj_list[i].vertex_num = t_node->_node->GetVertexNumber();
		if(obj_list[i].vertex_num != 0 ){
			obj_list[i].vertex = new _VERTEX[obj_list[i].vertex_num];
			for(UINT j = 0 ; j<(obj_list[i].vertex_num) ; ++j){
				obj_list[i].vertex[j] = t_node->_node->GetVertex()[j];
			}
		}
		else{
			obj_list[i].vertex = 0x00;
		}

		obj_list[i].texture_num = t_node->_node->GetTextureNumber();
		if(obj_list[i].texture_num != 0){
			obj_list[i].texture = new _TEXT[obj_list[i].texture_num];
			for(UINT j = 0 ; j<(obj_list[i].texture_num) ; ++j){
				obj_list[i].texture[j].text = 0x00;
				obj_list[i].texture[j].length = 0;
				SetText(&(obj_list[i].texture[j]),t_node->_node->GetTexture()[j].text);
			}
		}
		else{
			obj_list[i].texture = 0x00;
		}
		obj_list[i].world_mat = t_node->_node->GetWorldMatrix();
		
		t_node = t_node->_next;
	}

	_CAMERA* camera = new _CAMERA;

	camera->view_mat = m_view;
	camera->proj_mat = m_proj;

	display->x = m_pos.x;
	display->y = m_pos.y;
	display->width = m_size.x;
	display->height = m_size.y;
	display->buf = new UINT[(display->width * display->height)];

	::Render(display->width, display->height, display->buf,
		obj_list, obj_num, 0x00, 0, camera);

	for(UINT i = 0 ;i<obj_num ; ++i){
		if(obj_list[i].vertex != 0){
			delete [] (obj_list[i].vertex);
		}
		if(obj_list[i].texture != 0){
			for(UINT j = 0 ; j<(obj_list[i].texture_num) ; ++j){
				if(obj_list[i].texture[j].text != 0){
					delete [] obj_list[i].texture[j].text;
				}
			}
			delete [] (obj_list[i].texture);
		}
	}
	delete [] obj_list;
	delete camera;
}