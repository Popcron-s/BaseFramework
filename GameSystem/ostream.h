#pragma once

#include "List.h"
#include "ClassPattern.h"
#include "..\\Common\\Variable.h"
#include "..\\Common\\Function.h"
#include "..\\RenderInterface\\RenderInterface.h"

#include "Object.h"

#include <cmath>

class _CCamera;
//class _CSpeaker;

class _oStream{
	PHOENIX_SINGLETON(_oStream);
	CREATE_LIST(_CCamera,Camera);
	//CREATE_LIST(_CSpeaker,Speaker);

private:
	UINT m_Size_x, m_Size_y;

	void render_graphic();
	
public:
	UINT GetSizeX() const;
	UINT GetSizeY() const;
	void SetSize(UINT x, UINT y);

	void render();
};

class _CCamera{
private:
	_vector2 m_pos;
	_vector2 m_size;

	bool m_able;

public:
	_CCamera();
	~_CCamera();

	bool Getable() const;
	void Enable();
	void Disable();

	//get/set default
	_vector2 GetSize() const;
	_vector2 GetPosition() const;
	void SetSize(_vector2);
	void SetPosition(_vector2);

	void Render(_DISPLAY*);

	REGISTER_LIST(_CRenderObject,Object)

private:
	_vector3 m_eye, m_lookat, m_up;
	_matrix4x4 m_view;

public:
	//get/set view matrix
	_vector3 GetEye() const;
	_vector3 GetLookat() const;
	_vector3 GetUp() const;
	void SetEye(_vector3);
	void SetLookat(_vector3);
	void SetUp(_vector3);
	void SetViewMatrix();

private:
	_vector2 m_x, m_y, m_z;
	_matrix4x4 m_proj;

public:
	//get/set proj matrix
	_vector2 GetProjXRange() const;
	_vector2 GetProjYRange() const;
	_vector2 GetProjZRange() const;
	void SetProjectionRange(_vector2, _vector2, _vector2);
	void SetPerspectiveFov(FLOAT, FLOAT, FLOAT, FLOAT);
	void SetOrthoProjMatrix();
	void SetPerspectiveProjMatrix();
};

//class _CSpeaker{};