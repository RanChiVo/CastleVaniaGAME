#pragma once
#include "Viewport.h"
#include "TileSet.h"
#include "ObjectInfo.h"
#include <map>
#include <vector>
#include "Library/pugixml.hpp"
#include "GameObjects/GameObject.h"

constexpr int EXTRA_HEIGHT_SCREEN = 90;

class TiledMap
{
private:
	//Info in the game world
	D3DXVECTOR2 worldPosition;
	D3DXVECTOR2 viewPosition;
	float heightWorld;
	float widthWorld;

	//Info in map.xml
	LPDIRECT3DTEXTURE9 IDtex;
	int tilesInMapWidth;
	int tilesInMapHeight;
	int tileWidth;
	int tileHeight;
	pugi::xml_node rootNode;
	pugi::xml_parse_result isGoodFile;
	std::string mapIndices;
	std::string **matrixMap;

	//Info tileset
	TileSet* tileset;
	int tileSetWidth;
	int tileSetHeight;

	//Create effect when collision Cross
	static DWORD createEffectStart;
public:
	TiledMap(pugi::xml_node node);
	float getHeightWorld();
	float getWidthWorld();
	void setHeightWorld(float heightWorld);
	void setWidthWorld(float widthWorld);

	static void CreateEffectStart() { createEffectStart = GetTickCount(); }
	void readMapfromfile();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* object = NULL);
	void readMatrixMap();
	void draw(Viewport* viewport, int alpha = 255);

	~TiledMap();
};

