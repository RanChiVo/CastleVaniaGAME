#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Debug/DebugOut.h"
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
	
	void loadTexture(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	void loadSprites(int id, int left, int top, int right, int bottom, int idCharater);
	/*void loadAnimation(int time,int id, LPANIMATION ani);*/

	static ResourceManagement * GetInstance();
	~ResourceManagement();
	
};

