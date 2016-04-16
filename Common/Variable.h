#pragma once

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
	typedef struct _vector2{
		FLOAT x, y;
	}FLOAT2;

	typedef struct _vector3{
		FLOAT x, y, z;
	}FLOAT3;

	typedef struct _vector4{
		FLOAT x, y, z, w;
	}FLOAT4;

	typedef struct _matrix2x2{
		FLOAT _11, _12;
		FLOAT _21, _22;
	}FLOAT2x2;

	typedef struct _matrix3x3{
		FLOAT _11, _12, _13;
		FLOAT _21, _22, _23;
		FLOAT _31, _32, _33;
	}FLOAT3x3;

	typedef struct _matrix4x4{
		FLOAT _11, _12, _13, _14;
		FLOAT _21, _22, _23, _24;
		FLOAT _31, _32, _33, _34;
		FLOAT _41, _42, _43, _44;
	}FLOAT4x4;

	typedef struct _text{
		char* text;
		UINT length;
	}_TEXT;

	typedef struct _defaultvertex{
		_vector4 pos;
		_vector4 normal;
		_vector4 diffuse;
		_vector2 tex;
	}_VERTEX;

	typedef struct _defaultobject{
		_VERTEX* vertex;
		UINT vertex_num;
		_TEXT* texture;
		UINT texture_num;
		FLOAT4x4 world_mat;
	}_OBJECT;

	typedef struct _defaultlight{

	}_LIGHT;

	typedef struct _defaultcamera{
		FLOAT4x4 view_mat;
		FLOAT4x4 proj_mat;
	}_CAMERA;

	typedef struct _defaultdisplay{
		INT x, y;
		UINT width;
		UINT height;
		UINT* buf;
	}_DISPLAY;
}