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
typedef void* Mesh;
typedef void* Camera;

//MainSetting
extern "C"{
	GSYS_API void update();

	GSYS_API void SetBackBuffer(UINT x, UINT y);
	GSYS_API UINT GetBackBufferX();
	GSYS_API UINT GetBackBufferY();

	GSYS_API void SetMainLoop(void (*)());

	GSYS_API bool SetGraphicRenderer(RENDER_TYPE::RENDER_TYPE);
	GSYS_API RENDER_TYPE::RENDER_TYPE GetGraphicRenderer();
}

//Create/Release
extern "C"{
	GSYS_API Object CreateObject(Object);
	GSYS_API bool ReleaseObject(Object);

	GSYS_API Mesh CreateMesh(Object);
	GSYS_API bool ReleaseMesh(Mesh);

	GSYS_API Camera CreateCamera();
	GSYS_API bool ReleaseCamera(Camera);
	GSYS_API bool ReleaseCameraUseID(UINT);
}

//Object
extern "C"{
	GSYS_API _vector3 GetPosition(Object);
	GSYS_API _vector3 GetRotation(Object);
	GSYS_API _vector3 GetScale(Object);
	GSYS_API void SetPosition(Object, _vector3);
	GSYS_API void SetRotation(Object, _vector3);
	GSYS_API void SetScale(Object, _vector3);
	GSYS_API void AlterPosition(Object, _vector3);
	GSYS_API void AlterRotation(Object, _vector3);
	GSYS_API void AlterScale(Object, _vector3);

	GSYS_API _matrix4x4 GetWorldMatrix(Object);
	GSYS_API void SetWorldMatrix(Object);
}

//Mesh
extern "C"{
	GSYS_API _defaultvertex* GetVertex(Mesh);
	GSYS_API UINT GetVertexNum(Mesh);
	GSYS_API void SetVertex(Mesh, _defaultvertex*, UINT);

	GSYS_API char** GetTexture(Mesh);
	GSYS_API UINT GetTextureNum(Mesh);
	GSYS_API void SetTexture(Mesh, char**, UINT);
}

//Camera
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
	GSYS_API _vector2 GetProjXRange(Camera);
	GSYS_API _vector2 GetProjYRange(Camera);
	GSYS_API _vector2 GetProjZRange(Camera);
	GSYS_API void SetProjectionRange(Camera, _vector2 x, _vector2 y, _vector2 z);
	GSYS_API void SetPerspectiveFov(Camera, FLOAT asp, FLOAT fov, FLOAT n, FLOAT f);
	GSYS_API void SetOrthoProjMatrix(Camera);
	GSYS_API void SetPerspectiveProjMatrix(Camera);
}