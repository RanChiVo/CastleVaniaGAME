#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "DebugOut/DebugOut.h"
#include "Textures/Textures.h"	
#include "GameObjects/GameObject.h"
#include "SpriteManagements/Sprites.h"
#include "Animations/Animations.h"
#include "ObjectInfo.h"
#include <string>
#include "EntityID.h"
#include "TiledMap.h"
#include <unordered_map>
#include <map>
#include <vector>

#pragma once
class ResourceManagement
{
private:
	static ResourceManagement * __instance;
	ResourceManagement();
	ID3DXFont* font = nullptr;
	TiledMap* tiled_map;

public:
	std::unordered_map<std::string, EntityID> stringToEntityID;
	std::unordered_map<std::string, ANI_ID> stringToAniID;
	std::unordered_map<EntityID, Sprites*> SpriteMapper;
	std::unordered_map<EntityID, TiledMap*> TiledMapList;
	Textures * textures;
	Sprites* sprites;
	Animations* Getanimations;
	ID3DXFont* getFont() { return font; }
	D3DXVECTOR2 getFontSize(ID3DXFont* font , std::string text);
	Sprites* getSprite(EntityID id);
	TiledMap* getTiledMap(EntityID id);

	void loadResource();
	void loadFont(LPTSTR path);
	void loadTexture(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	void loadSprites(std::string id, RECT r, int idCharater);
	
	void readAnimationFromFile(std::string resourcepath);
	void readSpriteFromFile(std::string resourcepath);
	static ResourceManagement * GetInstance();

	~ResourceManagement();
	
};

