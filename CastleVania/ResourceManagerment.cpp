#include "ResourceManagement.h"

ResourceManagement * ResourceManagement::__instance = nullptr;

void ResourceManagement::loadTexture(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	Textures* textures = Textures::GetInstance();
	textures->Add(id, filePath, transparentColor);
}

void ResourceManagement::loadSprites(int id, int left, int top, int right, int bottom, int idCharater)
{
	Textures* textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(idCharater);
	Sprites * sprites = Sprites::GetInstance();
	sprites->Add(id, left, top, right, bottom, texSimon);
}

//void ResourceManagerment::loadAnimation(int time)
//{
//	Animations * animations = Animations::GetInstance();
//	LPANIMATION ani;
//
//}

ResourceManagement::ResourceManagement()
{
}

ResourceManagement * ResourceManagement::GetInstance()
{
	if (__instance == nullptr) __instance = new ResourceManagement();
	return __instance;
}

ResourceManagement::~ResourceManagement()
{
}
