#include "Sprites.h"
#include "../Textures/Textures.h"

Sprites * Sprites::__instance = nullptr;

void Sprites::Add(std::string id, RECT r,  LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, r, tex);
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
