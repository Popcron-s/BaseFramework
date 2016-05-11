#include <Windows.h>

#include "MainSystem.h"

bool WINAPI DllMain(HINSTANCE hInstace, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_DETACH) {
		_CGameSystem::Destroy();
		//_iStream::Destroy();
		_oStream::Destroy();
	}
	return true;
}