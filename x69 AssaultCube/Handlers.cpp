#include "stdafx.h"
#include "Handlers.h"
#include "Hooking.h"
#include "GameFunctions.h"
#include <vector>

hookData HookedFunctions::onRender2dHook = hookData(nullptr, nullptr);
hookData HookedFunctions::onShootHook = hookData(nullptr, nullptr);
hookData HookedFunctions::onUpdateHook = hookData(nullptr, nullptr);
hookData HookedFunctions::onRender3dHook = hookData(nullptr, nullptr);


HookHandler::HookHandler() {
	HookedFunctions::onRender2dHook = hookData((void*)(DWORD)0x455630, (void*)(HookedFunctions::onRender2d));
	HookedFunctions::onShootHook = hookData((void*)0x455630, (void*)(HookedFunctions::onShoot));
	HookedFunctions::onUpdateHook = hookData((void*)0x405330, (void*)(HookedFunctions::onUpdate));
	HookedFunctions::onRender3dHook = hookData((void*)0x4157D0, (void*)(HookedFunctions::onRender3d));

	HackHandler::setupHacks();
	GameFunctions::printToChat((char*)"x69 Assaultcube Version successfully injected <3");
}

void HookHandler::hook() {
	this->hookGraphics();
	this->hookOnUpdate();
	//this->hookOnShoot();
}

void HookHandler::hookGraphics() {
	HookedFunctions::onRender2dHook.setupHook();
	HookedFunctions::onRender2dHook.hook();

	HookedFunctions::onRender3dHook.setupHook();
	HookedFunctions::onRender3dHook.hook();
}

void HookHandler::hookOnShoot() {
	HookedFunctions::onShootHook.setupHook();
	HookedFunctions::onShootHook.hook();
}

void HookHandler::hookOnUpdate() {
	HookedFunctions::onUpdateHook.setupHook();
	HookedFunctions::onUpdateHook.hook();
}


void HookedFunctions::onRender2d() {
	//((void(*)())HookedFunctions::onRenderHook.dwOriginalFuncAddy)();

	for (Hack * hacc : HackHandler::hacks) {
		hacc->onRender2d();
	}
}

void HookedFunctions::onRender3d() {
	((void(*)())HookedFunctions::onRender3dHook.dwOriginalFuncAddy)();

	for (Hack * hacc : HackHandler::hacks) {
		hacc->onRender3d();
	}
}

void HookedFunctions::onShoot() {
	((void(*)())HookedFunctions::onShootHook.dwOriginalFuncAddy)();

	for (Hack * hacc : HackHandler::hacks) {
		hacc->onShoot();
	}
}

double HookedFunctions::onUpdate() {
	for (Hack * hacc : HackHandler::hacks) {
		hacc->onUpdate();
	}

	return ((double(*)())HookedFunctions::onUpdateHook.dwOriginalFuncAddy)();
}

std::vector<Hack*> HackHandler::hacks = std::vector<Hack*>();
void HackHandler::setupHacks() {
	HackHandler::hacks.push_back(new TeleportHack());
}
