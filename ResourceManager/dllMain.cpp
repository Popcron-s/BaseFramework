#include <Windows.h>
#include "ManagerClass.h"

bool WINAPI DllMain(HINSTANCE hInstace, DWORD fdwReason, LPVOID lpReserved){
	if(fdwReason == DLL_PROCESS_DETACH){
		if(_ResourceManager::GetSingleton() != 0x0){
			_ResourceManager::Destroy();
		}
	}

	return true;
}