#include <Windows.h>

#include "Interface.h"

bool WINAPI DllMain(HINSTANCE hInstace, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_DETACH) {
		if(_CInterface::GetSingleton() != 0x00){
			_CInterface::Destroy();
		}
	}
	return true;
}