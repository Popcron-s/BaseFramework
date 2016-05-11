#pragma once

#include "RenderInterface.h"

class _CInterface{
private:
	static _CInterface* m_pSingleton;

protected:
	_CInterface(){}
	~_CInterface(){}

public:
	static void SetType(RENDER_TYPE::RENDER_TYPE);
	virtual RENDER_TYPE::RENDER_TYPE GetType();
	static _CInterface* GetSingleton();
	static void Destroy();

	virtual bool Clear(_CAMERA camera){return false;}
	virtual bool DrawMesh(_OBJECT obj){return false;}
	virtual bool Render(UINT width, UINT height, UINT* buf, _LIGHT* light_list, UINT light_num){return false;}
	virtual bool DrawDisplay(UINT width, UINT height, _DISPLAY* display, UINT display_num){return false;}
};