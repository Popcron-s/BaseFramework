#pragma once

#ifdef GAMESYSTEM_EXPORTS
#define GSYS_API __declspec(dllexport)
#include "MainSystem.h"
#else
#define GSYS_API __declspec(dllimport)
#pragma comment(lib,"GameSystem.lib")
#endif

typedef void* Object;
typedef void* Camera;

#ifndef GAMESYSTEM_EXPORTS

#define __x86__

#ifdef __x86__
typedef float			FLOAT;
typedef int				INT;
typedef unsigned int	UINT;
#else
typedef double				FLOAT
#define __int64				INT 
#define unsigned __int64	UINT
#endif

extern "C"{
	struct _vector2{
		FLOAT x, y;
	};

	struct _vector3{
		FLOAT x, y, z;
	};

	struct _vector4{
		FLOAT x, y, z, w;
	};

	struct _matrix2x2{
		FLOAT _11, _12;
		FLOAT _21, _22;
	};

	struct _matrix3x3{
		FLOAT _11, _12, _13;
		FLOAT _21, _22, _23;
		FLOAT _31, _32, _33;
	};

	struct _matrix4x4{
		FLOAT _11, _12, _13, _14;
		FLOAT _21, _22, _23, _24;
		FLOAT _31, _32, _33, _34;
		FLOAT _41, _42, _43, _44;
	};

	struct _defaultvertex{
		_vector3 pos;
		_vector3 normal;
		_vector4 diffuse;
		_vector2 tex;
	};
}
#endif

extern "C"{
	GSYS_API void update();
}

extern "C"{
	GSYS_API void* CreateObject(void (*)());
	GSYS_API bool ReleaseObject(void*);

	GSYS_API void* CreateCamera();
	GSYS_API bool ReleaseCameraUsePointer(void*);
	GSYS_API bool ReleaseCameraUseID(UINT);

	GSYS_API bool RegisterUpdate(void*);
	GSYS_API bool RemoveUpdate(void*);
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
	GSYS_API void SetBackBuffer(UINT x, UINT y);
	GSYS_API UINT GetBackBufferX();
	GSYS_API UINT GetBackBufferY();
	GSYS_API _defaultvertex* GetVertex(Object);
	GSYS_API UINT GetVertexNum(Object);
	GSYS_API bool SetVertex(Object, _defaultvertex*, UINT);
}

extern "C"{
	GSYS_API bool RegisterObjectForCamera(Camera,Object);
	GSYS_API bool RemoveObjectForCamera(Camera,Object);
}