#include "Sprites.h"
#include "../Textures/Textures.h"


Sprites * Sprites::__instance = NULL;

void Sprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, left, top, right, bottom, tex);
	spritesList[id] = s;
}

LPSPRITE Sprites::Get(int id)
{
	return spritesList[id];
}

#include <iostream>
#include <filesystem>

void Sprites::loadResource()
{
	Textures* textures = Textures::GetInstance();
	auto a = std::experimental::filesystem::current_path();
	textures->Add(ID_TEX_SIMON, L"texture\\mario.png", D3DCOLOR_XRGB(176, 224, 248));

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	Add(10001, 246, 154, 260, 181, texSimon);

	Add(10002, 275, 154, 290, 181, texSimon);
	Add(10003, 304, 154, 321, 181, texSimon);

	Add(10011, 186, 154, 200, 181, texSimon);

	Add(10012, 155, 154, 170, 181, texSimon);
	Add(10013, 125, 154, 140, 181, texSimon);

}

Sprites * Sprites::GetInstance()
{
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}
