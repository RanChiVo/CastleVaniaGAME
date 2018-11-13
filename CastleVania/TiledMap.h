#pragma once

#include <vector>
#include "Viewport.h"
#include "SpriteManagements/Sprite.h"
#include "TileSet.h"
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
	std::map<std::pair<int,string>, D3DXVECTOR2> ObjectInfo;
	
public:
	TiledMap();
	void readMapfromfile(std::string resourcepath, LPDIRECT3DTEXTURE9 IDtex);
	std::map<std::pair<int, string>, D3DXVECTOR2>getObjectInfo();
	void draw(Viewport* viewport);
	float getWidthWorld();
	float getHeightWorld();
	~TiledMap();
};

