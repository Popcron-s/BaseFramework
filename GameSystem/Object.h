#pragma once

#include "..\\Common\\Variable.h"
#include "List.h"
#include "..\\Common\\Function.h"
#include "..\\RenderInterface\\RenderInterface.h"

#include <cmath>

class _CCamera;
//class _CSpeaker;
//class _CInput;
class _CObject;

class _CObject{
private:
	//Graphics
	_vector3 m_pos, m_rot, m_scl;
	_matrix4x4 m_world;
	_defaultvertex* m_vertex;
	UINT m_vertex_num;
	_TEXT* m_texture;
	UINT m_texture_num;

	//Sound state

	//Input Set

	//update

public:
	_CObject();
	~_CObject();

	//render
	//get, set pos,rot,scl
	_vector3 GetPosition() const;
	_vector3 GetRotation() const;
	_vector3 GetScale() const;
	void SetPosition(_vector3);
	void SetRotation(_vector3);
	void SetScale(_vector3);
	//get, set wld mat
	_matrix4x4 GetWorldMatrix() const;
	void SetWorldMatrix();
	//get, set vertex array
	UINT GetVertexNumber() const;
	bool SetVertex(_defaultvertex*, UINT);
	_defaultvertex* GetVertex() const;
	//get, set texture array
	UINT GetTextureNumber() const;
	bool SetTexture(_TEXT*, UINT);
	_TEXT* GetTexture() const;

	//create sound set
	//create input set

	//sound

	//input

	//update
	void (*update)();
};

class _CCamera{
private:
	_vector3 m_eye, m_lookat, m_up;
	_vector2 m_aspect, m_z;
	_vector3 m_near_ortho, m_far_ortho;
	_matrix4x4 m_view, m_proj;
	_LIST<_CObject>* m_Object_List;

	_vector2 m_pos;
	_vector2 m_size;

	bool m_able;
	
public:
	_CCamera();
	~_CCamera();

	bool RegisterObject(_CObject*);
	bool RemoveObject(_CObject*);

	bool Getable() const;
	void Enable();
	void Disable();

	//get/set default
	_vector2 GetSize() const;
	_vector2 GetPosition() const;
	void SetSize(_vector2);
	void SetPosition(_vector2);

	//get/set view matrix
	_vector3 GetEye() const;
	_vector3 GetLookat() const;
	_vector3 GetUp() const;
	void SetEye(_vector3);
	void SetLookat(_vector3);
	void SetUp(_vector3);
	void SetViewMatrix();

	//get/set proj matrix
	//ortho projection
	_vector3 GetNearOrtho() const;
	_vector3 GetFarOrtho() const;
	void SetOrtho(_vector3, _vector3);
	void SetOrthoProjMatrix();
	//perspective projection
	_vector2 GetAspect() const;
	FLOAT GetNearZ() const;
	FLOAT GetFarZ() const;
	void SetPerspective(_vector2, FLOAT, FLOAT);
	void SetPerspectiveProjMatrix();

	void Render(_DISPLAY*);
};

//class _CSpeaker{};
//class _CInput{};