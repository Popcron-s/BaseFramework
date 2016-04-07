#pragma once

#include "..\\Common\\Variable.h"
#include "List.h"
#include "..\\Common\\Text.h"
#include "..\\RenderInterface\\RenderInterface.h"
/*
struct _RenderData{
public:
	_matrix4x4 m_world;
	_defaultvertex* m_vertex;
	UINT m_vertex_num;
};
*/

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
	TEXT* m_texture;
	UINT m_texture_num;

	//Sound state

	//Input Set

	//update

public:
	_CObject();
	~_CObject();

	//render
	//get, set, alter pos,rot,scl
	//get, set, alter wld mat
	_matrix4x4 GetWorldMatrix() const;
	//get, set vertex array
	UINT GetVertexNumber() const;
	bool SetVertex(_defaultvertex*, UINT);
	_defaultvertex* GetVertex() const;
	//get, set texture array
	UINT GetTextureNumber() const;
	bool SetTexture(TEXT*, UINT);
	TEXT* GetTexture() const;

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

	void Render(_DISPLAY*);
};

//class _CSpeaker{};
//class _CInput{};