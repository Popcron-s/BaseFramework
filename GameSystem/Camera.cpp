#include "Object.h"
#include "MainSystem.h"

_CCamera::_CCamera(){
	m_eye = {0.0f, 0.0f, 0.0f};
	m_lookat = {0.0f, 0.0f, 0.0f};
	m_up = {0.0f, 1.0f, 0.0f};

	m_aspect = {1.0f, 1.0f};
	m_z = {1.0f, 10.0f};

	m_view = {1.0f, 0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f, 0.0f,
			  0.0f, 0.0f, 1.0f, 0.0f,
			  0.0f, 0.0f, 20.0f, 1.0f};
	m_proj = {800.0f, 0.0f, 0.0f, 0.0f,
			  0.0f, 600.0f, 0.0f, 0.0f,
			  0.0f, 0.0f, 1.0f, 1.0f,
			  0.0f, 0.0f, -10.0f, 0.0f};

	m_Object_List = 0x00;

	m_pos = {0.0f, 0.0f};
	m_size = {800.0f, 600.0f};

	m_able = true;

	_CGameSystem::GetSingleton()->RegisterCamera(this);
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
	while((*t_node) != 0x00){
		if((*t_node)->_next->_node == obj){
			_LIST<_CObject>* d_node = (*t_node)->_next;
			(*t_node)->_next = d_node->_next;
			delete d_node;
			return true;
		}
		t_node = &((*t_node)->_next);
	}
	return false;
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
		//obj_list[i] = t_node;
		obj_list[i].vertex_num = t_node->_node->GetVertexNumber();
		obj_list[i].vertex = new _VERTEX[obj_list[i].vertex_num];
		for(UINT j = 0 ; j<(obj_list[i].vertex_num) ; ++j){
			/*obj_list[i].vertex[j].vertex.x = t_node->_node->GetVertex()[j].pos.x;
			obj_list[i].vertex[j].vertex.y = t_node->_node->GetVertex()[j].pos.y;
			obj_list[i].vertex[j].vertex.z = t_node->_node->GetVertex()[j].pos.z;
			obj_list[i].vertex[j].vertex.w = t_node->_node->GetVertex()[j].pos.w;

			obj_list[i].vertex[j].diffuse.x = t_node->_node->GetVertex()[j].diffuse.x;
			obj_list[i].vertex[j].diffuse.y = t_node->_node->GetVertex()[j].diffuse.y;
			obj_list[i].vertex[j].diffuse.z = t_node->_node->GetVertex()[j].diffuse.z;
			obj_list[i].vertex[j].diffuse.w = t_node->_node->GetVertex()[j].diffuse.w;

			obj_list[i].vertex[j].normal.x = t_node->_node->GetVertex()[j].normal.x;
			obj_list[i].vertex[j].normal.y = t_node->_node->GetVertex()[j].normal.y;
			obj_list[i].vertex[j].normal.z = t_node->_node->GetVertex()[j].normal.z;
			obj_list[i].vertex[j].normal.w = t_node->_node->GetVertex()[j].normal.w;

			obj_list[i].vertex[j].textureUV.x = t_node->_node->GetVertex()[j].tex.x;
			obj_list[i].vertex[j].textureUV.y = t_node->_node->GetVertex()[j].tex.y;*/
			obj_list[i].vertex[j] = t_node->_node->GetVertex()[j];
		}
		obj_list[i].texture_num = t_node->_node->GetTextureNumber();
		obj_list[i].texture = new TEXT[obj_list[i].texture_num];
		for(UINT j = 0 ; j<(obj_list[i].texture_num) ; ++j){
			obj_list[i].texture[j] = t_node->_node->GetTexture()[j];
		}
		obj_list[i].world_mat._11 = t_node->_node->GetWorldMatrix()._11;
		obj_list[i].world_mat._12 = t_node->_node->GetWorldMatrix()._12;
		obj_list[i].world_mat._13 = t_node->_node->GetWorldMatrix()._13;
		obj_list[i].world_mat._14 = t_node->_node->GetWorldMatrix()._14;
		obj_list[i].world_mat._21 = t_node->_node->GetWorldMatrix()._21;
		obj_list[i].world_mat._22 = t_node->_node->GetWorldMatrix()._22;
		obj_list[i].world_mat._23 = t_node->_node->GetWorldMatrix()._23;
		obj_list[i].world_mat._24 = t_node->_node->GetWorldMatrix()._24;
		obj_list[i].world_mat._31 = t_node->_node->GetWorldMatrix()._31;
		obj_list[i].world_mat._32 = t_node->_node->GetWorldMatrix()._32;
		obj_list[i].world_mat._33 = t_node->_node->GetWorldMatrix()._33;
		obj_list[i].world_mat._34 = t_node->_node->GetWorldMatrix()._34;
		obj_list[i].world_mat._41 = t_node->_node->GetWorldMatrix()._41;
		obj_list[i].world_mat._42 = t_node->_node->GetWorldMatrix()._42;
		obj_list[i].world_mat._43 = t_node->_node->GetWorldMatrix()._43;
		obj_list[i].world_mat._44 = t_node->_node->GetWorldMatrix()._44;

		t_node = t_node->_next;
	}

	_CAMERA* camera = new _CAMERA;

	camera->view_mat._11 = m_view._11; camera->view_mat._12 = m_view._12;
	camera->view_mat._13 = m_view._13; camera->view_mat._14 = m_view._14;
	camera->view_mat._21 = m_view._21; camera->view_mat._22 = m_view._22;
	camera->view_mat._23 = m_view._23; camera->view_mat._24 = m_view._24;
	camera->view_mat._31 = m_view._31; camera->view_mat._32 = m_view._32;
	camera->view_mat._33 = m_view._33; camera->view_mat._34 = m_view._34;
	camera->view_mat._41 = m_view._41; camera->view_mat._42 = m_view._42;
	camera->view_mat._43 = m_view._43; camera->view_mat._44 = m_view._44;

	camera->proj_mat._11 = m_proj._11; camera->proj_mat._12 = m_proj._12;
	camera->proj_mat._13 = m_proj._13; camera->proj_mat._14 = m_proj._14;
	camera->proj_mat._21 = m_proj._21; camera->proj_mat._22 = m_proj._22;
	camera->proj_mat._23 = m_proj._23; camera->proj_mat._24 = m_proj._24;
	camera->proj_mat._31 = m_proj._31; camera->proj_mat._32 = m_proj._32;
	camera->proj_mat._33 = m_proj._33; camera->proj_mat._34 = m_proj._34;
	camera->proj_mat._41 = m_proj._41; camera->proj_mat._42 = m_proj._42;
	camera->proj_mat._43 = m_proj._43; camera->proj_mat._44 = m_proj._44;

	display->x = m_pos.x;
	display->y = m_pos.y;
	display->width = m_size.x;
	display->height = m_size.y;
	display->buf = new UINT[(display->width * display->height)];

	::Render(display->width, display->height, display->buf,
		obj_list, obj_num, 0x00, 0, camera);

	for(UINT i = 0 ;i<obj_num ; ++i){
		delete [] (obj_list[i].vertex);
		delete [] (obj_list[i].texture);
	}
	delete [] obj_list;
	delete camera;
}