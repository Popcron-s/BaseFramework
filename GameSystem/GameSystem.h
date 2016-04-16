#pragma once

#ifdef GAMESYSTEM_EXPORTS
#define GSYS_API __declspec(dllexport)
#include "MainSystem.h"
#else
#define GSYS_API __declspec(dllimport)
#pragma comment(lib,"GameSystem.lib")
#endif

#include "..\\Common\\Variable.h"

typedef void* Object;
typedef void* Camera;

extern "C"{
	GSYS_API void update();

	GSYS_API void SetBackBuffer(UINT x, UINT y);
	GSYS_API UINT GetBackBufferX();
	GSYS_API UINT GetBackBufferY();
}

extern "C"{
	GSYS_API void* CreateObject(void (*)());
	GSYS_API bool ReleaseObject(void*);

	GSYS_API void* CreateCamera();
	GSYS_API bool ReleaseCameraUsePointer(void*);
	GSYS_API bool ReleaseCameraUseID(UINT);

	/*
	GSYS_API void AlterPosition(void*, FLOAT, FLOAT, FLOAT);
	GSYS_API void AlterRotation(void*, FLOAT, FLOAT, FLOAT);
	GSYS_API void AlterScale(void*, FLOAT, FLOAT, FLOAT);
	GSYS_API void SetWorldMatrix(void*, 
		FLOAT, FLOAT, FLOAT, FLOAT,
		FLOAT, FLOAT, FLOAT, FLOAT,
		FLOAT, FLOAT, FLOAT, FLOAT,
		FLOAT, FLOAT, FLOAT, FLOAT);*/

	//GSYS_API bool RegisterRender(void*, UINT);
	//GSYS_API bool RemoveRender(void*, UINT);
}

extern "C"{
	GSYS_API bool RegisterUpdate(void*);
	GSYS_API bool RemoveUpdate(void*);

	GSYS_API _vector3 GetPosition(Object);
	GSYS_API _vector3 GetRotation(Object);
	GSYS_API _vector3 GetScale(Object);
	GSYS_API void SetPosition(Object, FLOAT, FLOAT, FLOAT);
	GSYS_API void SetRotation(Object, FLOAT, FLOAT, FLOAT);
	GSYS_API void SetScale(Object, FLOAT, FLOAT, FLOAT);
	GSYS_API void AlterPosition(Object, FLOAT, FLOAT, FLOAT);
	GSYS_API void AlterRotation(Object, FLOAT, FLOAT, FLOAT);
	GSYS_API void AlterScale(Object, FLOAT, FLOAT, FLOAT);

	GSYS_API _matrix4x4 GetWorldMatrix(Object);
	GSYS_API void SetWorldMatrix(Object);

	GSYS_API _defaultvertex* GetVertex(Object);
	GSYS_API UINT GetVertexNum(Object);
	GSYS_API bool SetVertex(Object, _defaultvertex*, UINT);

	GSYS_API _TEXT* GetTexture(Object);
	GSYS_API UINT GetTextureNum(Object);
	GSYS_API bool SetTexture(Object, _TEXT*, UINT);
}

extern "C"{
	GSYS_API bool RegisterObjectForCamera(Camera,Object);
	GSYS_API bool RemoveObjectForCamera(Camera,Object);

	//get/set default
	GSYS_API _vector2 GetCameraSize(Camera);
	GSYS_API _vector2 GetCameraPosition(Camera);
	GSYS_API void SetCameraSize(Camera, _vector2);
	GSYS_API void SetCameraPosition(Camera, _vector2);

	//get/set view matrix
	GSYS_API _vector3 GetEye(Camera);
	GSYS_API _vector3 GetLookat(Camera);
	GSYS_API _vector3 GetUp(Camera);
	GSYS_API void SetEye(Camera, _vector3);
	GSYS_API void SetLookat(Camera, _vector3);
	GSYS_API void SetUp(Camera, _vector3);
	GSYS_API void SetViewMatrix(Camera);

	//get/set proj matrix
	//ortho projection
	GSYS_API _vector3 GetNearOrtho(Camera);
	GSYS_API _vector3 GetFarOrtho(Camera);
	GSYS_API void SetOrtho(Camera, _vector3, _vector3);
	GSYS_API void SetOrthoProjMatrix(Camera);
	//perspective projection
	GSYS_API _vector2 GetAspect(Camera);
	GSYS_API FLOAT GetNearZ(Camera);
	GSYS_API FLOAT GetFarZ(Camera);
	GSYS_API void SetPerspective(Camera, _vector2, FLOAT, FLOAT);
	GSYS_API void SetPerspectiveProjMatrix(Camera);
}