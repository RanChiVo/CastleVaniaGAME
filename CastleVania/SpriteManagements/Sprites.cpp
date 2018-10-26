#include "Sprites.h"
#include "../Textures/Textures.h"

Sprites * Sprites::__instance = nullptr;

void Sprites::Add(std::string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex);
	spritesList[id] = s;
}

LPSPRITE Sprites::Get(std::string id)
{
	return spritesList[id];
}

Sprites * Sprites::GetInstance()
{
	if (__instance == nullptr) __instance = new Sprites();
	return __instance;
}
