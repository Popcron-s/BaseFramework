#pragma once

#ifdef RENDERINTERFACE_EXPORTS
#define RINTER_API __declspec(dllexport)
#else
#define RINTER_API __declspec(dllimport)
#pragma comment(lib,"..\\Release\\RenderInterface.lib")
#endif

#include "..\\Text.h"

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
	struct FLOAT4{
		FLOAT x,y,z,w;
	};
	struct FLOAT2{
		FLOAT x,y;
	};
	struct FLOAT4x4{
		FLOAT _11,_12,_13,_14;
		FLOAT _21,_22,_23,_24;
		FLOAT _31,_32,_33,_34;
		FLOAT _41,_42,_43,_44;
	};
}

extern "C"{
	struct _VERTEX{
		FLOAT4 vertex;
		FLOAT4 diffuse;
		FLOAT4 normal;
		FLOAT2 textureUV;
	};
	struct _OBJECT{
		_VERTEX* vertex;
		UINT vertex_num;
		TEXT* texture;
		UINT texture_num;
		FLOAT4x4 world_mat;
	};
	struct _LIGHT{

	};
	struct _CAMERA{
		FLOAT4x4 view_mat;
		FLOAT4x4 proj_mat;
	};

	struct _DISPLAY{
		UINT x, y;
		UINT width;
		UINT height;
		UINT* buf;
	};
}

extern "C"{
	RINTER_API bool Render(UINT width, UINT height, UINT* buf, 
		_OBJECT* obj_list, UINT object_num, 
		_LIGHT* light_list, UINT light_num, 
		_CAMERA* camera);
	RINTER_API bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num);
}