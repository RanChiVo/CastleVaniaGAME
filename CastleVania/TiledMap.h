#pragma once

#include <vector>
#include "Viewport.h"
#include "SpriteManagements/Sprite.h"
#include "TileSet.h"
#include <map>

class TiledMap
{
private:
	D3DXVECTOR2 worldPosition;
	D3DXVECTOR2 viewPosition;

	int tilesInMapWidth;
	int tilesInMapHeight;
	int tileWidth;
	int tileHeight;

	TileSet* tileset;

public:
	TiledMap();
	void readMapfromfile(std::string resourcepath, LPDIRECT3DTEXTURE9 IDtex);
	void draw(Viewport* viewport);
	~TiledMap();
};

