#include <Windows.h>

#include "Interface.h"

bool WINAPI DllMain(HINSTANCE hInstace, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_DETACH) {
		_CInterface::Destroy();
	}
	return true;
}