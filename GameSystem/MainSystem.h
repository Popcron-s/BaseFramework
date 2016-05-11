#pragma once

#include "List.h"
#include "Object.h"
#include "ostream.h"

class _CGameSystem{
	PHOENIX_SINGLETON(_CGameSystem);
	REGISTER_LIST(_CObjectSet,Object);

private:

public:
	//update
	void (*main_loop)();
	void update();

	void AllRemoveObject(_CObjectSet* obj);
	void AllRemoveAllObject();
};