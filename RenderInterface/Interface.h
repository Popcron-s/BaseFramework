#pragma once

#include "RenderInterface.h"

namespace TYPE{
	enum TYPE{
		NONE,
		OpenGL,
		DirectX9,
		DirectX11
	};
}

class _CInterface{
private:
	static _CInterface* m_pSingleton;

protected:
	_CInterface(){}
	~_CInterface(){}

public:
	static void SetType(TYPE::TYPE);
	virtual TYPE::TYPE GetType();
	static _CInterface* GetSingleton();
	static void Destroy();

	virtual bool Render(UINT width, UINT height, UINT* buf, _OBJECT* obj_list, UINT object_num, _LIGHT* light_list, UINT light_num, _CAMERA* camera) = 0;
	virtual bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num) = 0;
};