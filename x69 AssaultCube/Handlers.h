#pragma once
#include "Hooking.h"
#include "Hacks.h"
#include <vector>

struct HookedFunctions {
	static hookData onRender2dHook;
	static void onRender2d();
	static hookData onRender3dHook;
	static void onRender3d();
	static hookData onShootHook;
	static void onShoot();
	static hookData onUpdateHook;
	static double onUpdate();
};

struct HackHandler {
	static std::vector<Hack*> hacks;
	static void setupHacks();
};

class HookHandler {
private:
	void hookGraphics();
	void hookOnShoot();
	void hookOnUpdate();

public:
	void hook();

	HookHandler();
};