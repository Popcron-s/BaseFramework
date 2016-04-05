#pragma once

#include "List.h"
#include "Object.h"

#include "..\\RenderInterface\\RenderInterface.h"

class _CGameSystem{
private:
	//List Object
	_LIST<_CObject>* m_Object_List;
	UINT m_Object_num;

	//List Camera
	_LIST<_CCamera>* m_Camera_List;
	UINT m_Camera_num;

	//List Speaker
	//List Input

	//List Update
	_funcLIST* m_update_List;
	UINT m_update_num;

	UINT m_Size_x, m_Size_y;

	static _CGameSystem* m_pSingleton;

	_CGameSystem();
	~_CGameSystem();

public:
	static _CGameSystem* GetSingleton();
	static void Destroy();

	void Update();

	UINT GetSizeX() const;
	UINT GetSizeY() const;
	void SetSize(UINT x, UINT y);

	//Object
	UINT GetObjectNumber() const;
	_CObject* CreateObject();
	bool ReleaseObject(_CObject*);
	bool ReleaseAllObject();

	//Render
	UINT GetCameraNumber() const;
	bool RegisterCamera(_CCamera*);
	bool RemoveCamera(_CCamera*);
	bool RemoveAllCamera();
	_CCamera* SearchCamera(UINT) const;
	bool SwapCamera(_CCamera*, _CCamera*);

	//update
	UINT GetUpdateNumber() const;
	bool RegisterUpdate(void (*)());
	bool RemoveUpdate(void (*)());
	bool RemoveAllUpdate();
	void* SearchUpdate(UINT) const;
	bool SwapUpdate(void*, void*);
};