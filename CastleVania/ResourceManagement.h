#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "DebugOut/DebugOut.h"
#include "Textures/Textures.h"	
#include "SpriteManagements/Sprites.h"
#include "Animations/Animations.h"
#include <string>

#pragma once
class ResourceManagement
{
private:
	static ResourceManagement * __instance;
	ResourceManagement();
	ID3DXFont* font = nullptr;

public:

	Textures * textures;
	Sprites* sprites;
	Animations* Getanimations;

	ID3DXFont* getFont() { return font; }
	D3DXVECTOR2 getFontSize(ID3DXFont* font , std::string text);
	void loadFont(LPTSTR path);
	void loadTexture(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	void loadSprites(std::string id, int left, int top, int right, int bottom, int idCharater);
	/*void loadAnimation(int time,int id, LPANIMATION ani);*/

	static ResourceManagement * GetInstance();
	~ResourceManagement();
	
};

