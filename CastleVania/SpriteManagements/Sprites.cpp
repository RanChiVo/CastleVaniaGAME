#include "Sprites.h"


Sprites * Sprites::__instance = nullptr;

void Sprites::Add(std::string id, RECT r,  LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, r, tex);
	sprites[id] = s;
}

LPSPRITE Sprites::Get(std::string id)
{
	return sprites[id];
}

void Sprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}

Sprites * Sprites::GetInstance()
{
	if (__instance == nullptr) __instance = new Sprites();
	return __instance;
}
