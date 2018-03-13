#pragma once
#include "Hooking.h"
#include <Windows.h>


struct hookData {
	bool bIsSettedUp = false;
	bool bIsHooked = false;

	void * vpToHook;
	void * vpHookedFunc;

	DWORD dwOriginalFuncAddy;
	int pageSize = 1024;

	void setupHook();
	bool hook();
	bool unhook();

	unsigned char oldBytes[5];

	hookData(void * toHook, void * hookedFunc);
};