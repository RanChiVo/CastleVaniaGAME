#pragma once

#include "Viewport.h"
#include "SpriteManagements/Sprite.h"
#include "TileSet.h"
#include "ObjectInfo.h"
#include <map>
#include <vector>

class TiledMap
{
private:
	D3DXVECTOR2 worldPosition;
	D3DXVECTOR2 viewPosition;
	float widthWorld;
	float heightWorld;

	int tilesInMapWidth;
	int tilesInMapHeight;
	int tileWidth;
	int tileHeight;

	TileSet* tileset;
	std::vector<ObjectInfo*> objectInfo;
	
public:
	TiledMap();
	void readMapfromfile(std::string resourcepath, LPDIRECT3DTEXTURE9 IDtex);
	std::vector<ObjectInfo*> getObjectInfo();
	void draw(Viewport* viewport);
	float getWidthWorld();
	float getHeightWorld();
	
	~TiledMap();
};

