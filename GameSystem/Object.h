#pragma once

#include "..\\Common\\Variable.h"
#include "List.h"
#include "..\\Common\\Function.h"
#include "..\\RenderInterface\\RenderInterface.h"

#include <cmath>

class _CObjectSet{};

class _CObject;

class _CMesh;
//class _CString;
//class _CSound;
//class _CCollider;

class _CObject : public _CObjectSet{
private:
	_vector3 m_pos, m_rot, m_scl;
	_matrix4x4 m_world;

	_CObject* m_pParent;

public:
	_CObject();
	_CObject(_CObject*);
	~_CObject();

	//object position
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
};

class _CRenderObject : public _CObjectSet{
public:
	virtual void render() = 0;
};

class _CMesh : public _CRenderObject{
private:
	UINT m_vertex_num;
	_VERTEX* m_vertex;

	UINT m_texture_num;
	char** m_texture;
	
	_CObject* m_pParent;

public:
	_CMesh(_CObject*);
	~_CMesh();

	UINT GetVertexNumber() const;
	UINT GetTextureNumber() const;

	_VERTEX* GetVertex() const;
	char** GetTexture() const;

	void SetVertex(_VERTEX*, UINT);
	void SetTexture(char**, UINT);

	void render();
};