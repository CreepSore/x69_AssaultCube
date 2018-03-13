#pragma once
#include <Windows.h>

class Hack {
public:
	virtual void onRender2d() = 0;
	virtual void onRender3d() = 0;
	virtual void onUpdate() = 0;
	virtual void onShoot() = 0;
};

struct TeleportHack : Hack {
	virtual void onRender3d() override;
	virtual void onRender2d() override;
	virtual void onUpdate() override;
	virtual void onShoot() override;
};