#pragma once

#include "Viewport.h"
#include "TileSet.h"
#include "ObjectInfo.h"
#include <map>
#include <vector>
#include "Library/pugixml.hpp"
#include "GameObjects/GameObject.h"

class TiledMap
{
private:
	//Info in the game world
	D3DXVECTOR2 worldPosition;
	D3DXVECTOR2 viewPosition;
	float heightWorld;
	float widthWorld;

	//Info in map.xml
	std::string resourcepath;
	LPDIRECT3DTEXTURE9 IDtex;
	int tilesInMapWidth;
	int tilesInMapHeight;
	int tileWidth;
	int tileHeight;
	pugi::xml_document doc;
	pugi::xml_node rootNode;
	pugi::xml_parse_result isGoodFile;
	std::string mapIndices;
	std::string **matrixMap;

	//Info tileset
	TileSet* tileset;
	int tileSetWidth;
	int tileSetHeight;

	//Info Game Object 
	std::vector<ObjectInfo::builder*> objectInfo;
	
	//Create effect when collision Cross
	static DWORD createEffectStart;
public:
	static void CreateEffectStart() { createEffectStart = GetTickCount(); }
	TiledMap(std::string resourcepath, LPDIRECT3DTEXTURE9 IDtex);
	void readMapfromfile();
	void checkGoodFile();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* object = NULL);
	//get info of Objects in Layer 
	void readMatrixMap();
	std::vector <ObjectInfo::builder*> getObjectInfo();
	void clearObjectInfo();
	void draw(Viewport* viewport, int alpha = 255);
	float getHeightWorld();
	float getWidthWorld();
	~TiledMap();
};

