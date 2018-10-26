#include "ResourceManagement.h"

ResourceManagement * ResourceManagement::__instance = nullptr;

void ResourceManagement::loadTexture(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	
	textures->Add(id, filePath, transparentColor);
}

void ResourceManagement::loadSprites(std::string id, int left, int top, int right, int bottom, int idCharater)
{
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(idCharater);
	sprites->Add(id, left, top, right, bottom, texSimon);
}

//void ResourceManagerment::loadAnimation(int time
//{
//	Animations * animations = Animations::GetInstance();
//	LPANIMATION ani;
//
//}

ResourceManagement::ResourceManagement()
{
	textures = Textures::GetInstance();
	sprites = Sprites::GetInstance();
	Getanimations = Animations::GetInstance();
}

ResourceManagement * ResourceManagement::GetInstance()
{
	if (__instance == nullptr) __instance = new ResourceManagement();
	return __instance;
}

ResourceManagement::~ResourceManagement()
{
}
