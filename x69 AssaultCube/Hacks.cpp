#include "stdafx.h"
#include "Hacks.h"
#include "vec.h"
#include "GameFunctions.h"
#include <sstream>
#include <gl\GL.h>
#include <gl\GLU.h>

#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

void TeleportHack::onRender3d()
{
	vec3f * rayTracePos = (vec3f*)0x50A400;
	vec3f * playerPos = (vec3f*)((*(DWORD*)0x50F4F4) + 0x34);

	vec3f from = vec3f();
	from.x = rayTracePos->x - playerPos->x;
	from.y = rayTracePos->y - playerPos->y;
	from.z = rayTracePos->z - playerPos->z;

	from = *rayTracePos;

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glColor4f(1.0f, 0, 0, 1.0f);

	glBegin(GL_LINES);

	glVertex3d(from.x - 2, from.y - 2, from.z);
	glVertex3d(from.x + 2, from.y + 2, from.z);

	glVertex3d(from.x + 2, from.y - 2, from.z);
	glVertex3d(from.x - 2, from.y + 2, from.z);

	glEnd();

	glPopAttrib();
	glPopMatrix();
}

void TeleportHack::onRender2d()
{

}

void TeleportHack::onUpdate()
{
	if (GetAsyncKeyState(VK_LMENU) & 1) {
		vec3f * rayTracePos = (vec3f*)0x50A400;
		vec3f * playerPos = (vec3f*)((*(DWORD*)0x50F4F4) + 0x34);
		playerPos->x = rayTracePos->x;
		playerPos->y = rayTracePos->y;
		playerPos->z = rayTracePos->z;
	}
}

void TeleportHack::onShoot()
{

}
