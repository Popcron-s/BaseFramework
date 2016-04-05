#include <Windows.h>

#include "MainSystem.h"

bool WINAPI DllMain(HINSTANCE hInstace, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_DETACH) {
		if(_CGameSystem::GetSingleton() != 0x00){
			_CGameSystem::Destroy();
		}
	}
	return true;
}