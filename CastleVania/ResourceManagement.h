#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "DebugOut/DebugOut.h"
#include "Textures/Textures.h"	
#include "SpriteManagements/Sprites.h"
#include "Animations/Animations.h"

#pragma once
class ResourceManagement
{
private:
	static ResourceManagement * __instance;
	ResourceManagement();

public:

	Textures * textures;
	Sprites* sprites;
	Animations* Getanimations;

	void loadTexture(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	void loadSprites(std::string id, int left, int top, int right, int bottom, int idCharater);
	/*void loadAnimation(int time,int id, LPANIMATION ani);*/

	static ResourceManagement * GetInstance();
	~ResourceManagement();
	
};

