#include "Object.h"

_CObject::_CObject() :
	m_pos({0.0f, 0.0f, 0.0f}), m_rot({0.0f, 0.0f, 0.0f}), m_scl({1.0f, 1.0f, 1.0f}), 
	m_world({1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}),
	m_pParent(0x00){}
_CObject::_CObject(_CObject* parent) : 
	m_pos({0.0f, 0.0f, 0.0f}), m_rot({0.0f, 0.0f, 0.0f}), m_scl({1.0f, 1.0f, 1.0f}), 
	m_world({1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f}),
	m_pParent(parent){}
_CObject::~_CObject(){}

_vector3 _CObject::GetPosition() const{return m_pos;}
_vector3 _CObject::GetRotation() const{return m_rot;}
_vector3 _CObject::GetScale() const{return m_scl;}
void _CObject::SetPosition(_vector3 pos){m_pos = pos;}
void _CObject::SetRotation(_vector3 rot){m_rot = rot;}
void _CObject::SetScale(_vector3 scl){m_scl = scl;}

_matrix4x4 _CObject::GetWorldMatrix() const{return m_world;}
void _CObject::SetWorldMatrix(){
	if(m_pParent != 0x00){m_pParent->SetWorldMatrix();}
	//scale->rotation->Position
	_matrix4x4 t_mat = {
		m_scl.x, 0,0,0,
		0, m_scl.y,0,0,
		0,0, m_scl.z,0,
		0,0,0,1
	};

	FLOAT4 q = {
		(sin(m_rot.x/2)*cos(m_rot.y/2)*cos(m_rot.z/2))-(cos(m_rot.x/2)*sin(m_rot.y/2)*sin(m_rot.z/2)),
		(cos(m_rot.x/2)*sin(m_rot.y/2)*cos(m_rot.z/2))+(sin(m_rot.x/2)*cos(m_rot.y/2)*sin(m_rot.z/2)),
		(cos(m_rot.x/2)*cos(m_rot.y/2)*sin(m_rot.z/2))-(sin(m_rot.x/2)*sin(m_rot.y/2)*cos(m_rot.z/2)),
		(cos(m_rot.x/2)*cos(m_rot.y/2)*cos(m_rot.z/2))+(sin(m_rot.x/2)*sin(m_rot.y/2)*sin(m_rot.z/2))
	};
	//1-2yy-2zz , -2wz+2xy , 2wy+2xz
	//2wz+2xy , 1-2xx-2zz , -2wx+2yz
	//-2wy+2xz , 2wx+2yz , 1-2xx-2yy
	_matrix3x3 t_rot = {
		1-(2*q.y*q.y)-(2*q.z*q.z), (2*q.x*q.y)-(2*q.w*q.z), (2*q.x*q.z)+(2*q.w*q.y),
		(2*q.x*q.y)+(2*q.w*q.z), 1-(2*q.x*q.x)-(2*q.z*q.z), (2*q.y*q.z)-(2*q.w*q.x),
		(2*q.x*q.z)-(2*q.w*q.y), (2*q.y*q.z)+(2*q.w*q.x), 1-(2*q.x*q.x)-(2*q.y*q.y)
	};
	t_mat._11 = m_scl.x * t_rot._11; t_mat._12 = m_scl.x * t_rot._12;
	t_mat._13 = m_scl.x * t_rot._13; t_mat._14 = 0;

	t_mat._21 = m_scl.y * t_rot._21; t_mat._22 = m_scl.y * t_rot._22;
	t_mat._23 = m_scl.y * t_rot._23; t_mat._14 = 0;

	t_mat._31 = m_scl.z * t_rot._31; t_mat._32 = m_scl.z * t_rot._32;
	t_mat._33 = m_scl.z * t_rot._33; t_mat._34 = 0;
	
	t_mat._41 = m_pos.x; t_mat._42 = m_pos.y; t_mat._43 = m_pos.z; t_mat._44 = 1;

	if(m_pParent != 0x00){m_world = MultipleMatrix4x4(m_pParent->GetWorldMatrix(),t_mat);}
	else{m_world = t_mat;}
}