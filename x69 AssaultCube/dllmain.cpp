#include "stdafx.h"
#include "Handlers.h"
#include <Windows.h>


BOOL __stdcall mainThread(LPVOID arg0) {
	HookHandler hh = HookHandler();
	hh.hook();


	while (true) {

	}

	return TRUE;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)mainThread, hModule, NULL, nullptr);
        break;
    }
    return TRUE;
}