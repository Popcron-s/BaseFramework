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

struct _vector2{
public:
	FLOAT x, y;
};

struct _vector3{
public:
	FLOAT x, y, z;
};

struct _vector4{
public:
	FLOAT x, y, z, w;
};

struct _matrix2x2{
public:
	FLOAT _11, _12;
	FLOAT _21, _22;
};

struct _matrix3x3{
public:
	FLOAT _11, _12, _13;
	FLOAT _21, _22, _23;
	FLOAT _31, _32, _33;
};

struct _matrix4x4{
public:
	FLOAT _11, _12, _13, _14;
	FLOAT _21, _22, _23, _24;
	FLOAT _31, _32, _33, _34;
	FLOAT _41, _42, _43, _44;
};

struct _defaultvertex{
public:
	_vector4 pos;
	_vector4 normal;
	_vector4 diffuse;
	_vector2 tex;
};