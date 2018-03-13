#include "stdafx.h"
#include "Hooking.h"
#include <Windows.h>

hookData::hookData(void * toHook, void * hookedFunc) {
	this->vpToHook = toHook;
	this->vpHookedFunc = hookedFunc;
}

void hookData::setupHook() {
	/*
	SetupHook basically sets up a Memory Region, so you can call the original Function that you hooked.
	*/
	if (this->bIsSettedUp) return;
	if (this->bIsHooked) return;

	// Allocate the Memory Region for the Function
	this->dwOriginalFuncAddy = (DWORD)VirtualAlloc(NULL, this->pageSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// Make the Function to Hook readable
	DWORD oldProtection;
	VirtualProtect(this->vpToHook, this->pageSize, PAGE_EXECUTE_READWRITE, &oldProtection);

	// Copy the Bytes of the Function to Hook into our fresh made Memory Region
	memcpy((void*)this->dwOriginalFuncAddy, this->vpToHook, this->pageSize);

	// Reset the Memory-Region Protections
	DWORD temp;
	VirtualProtect(this->vpToHook, this->pageSize, oldProtection, &temp);
	VirtualProtect((void*)this->dwOriginalFuncAddy, this->pageSize, PAGE_EXECUTE_READ, &temp);

	this->bIsSettedUp = true;
}

bool hookData::hook() {
	if (!this->bIsSettedUp) return false;
	if (this->bIsHooked) return false;

	// Make the Function to Hook readable
	DWORD oldProtection;
	VirtualProtect(this->vpToHook, 5, PAGE_EXECUTE_READWRITE, &oldProtection);

	// calculate the relative address for the jmp-execution
	DWORD relAddress = ((DWORD)this->vpHookedFunc - (DWORD)this->vpToHook) - 5;

	// Generate the jmp-execution
	*(BYTE*)(this->vpToHook) = 0xE9;
	*(DWORD*)((DWORD)this->vpToHook + 0x1) = relAddress;

	// Reset the Protection
	DWORD temp;
	VirtualProtect(this->vpToHook, 5, oldProtection, &temp);

	this->bIsHooked = true;
	return true;
}

bool hookData::unhook() {
	if (!this->bIsSettedUp) return false;
	if (!this->bIsHooked) return false;

	// Make the Function to Hook readable
	DWORD oldProtection;
	VirtualProtect(this->vpToHook, 5, PAGE_EXECUTE_READWRITE, &oldProtection);

	memcpy(this->vpToHook, (void*)this->dwOriginalFuncAddy, 5);

	// Reset the Protection
	DWORD temp;
	VirtualProtect(this->vpToHook, 5, oldProtection, &temp);

	VirtualFree((void*)this->dwOriginalFuncAddy, 0, MEM_RELEASE);

	return true;
}