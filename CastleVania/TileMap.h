#pragma once

#include <vector>
#include "Viewport.h"
#include "SpriteManagements/Sprite.h"
#include "Tile.h"
#include <map>

class TileMap
{
private:

	D3DXVECTOR2 positionTile;// Xac dinh toa do ve
	LPSPRITE sprite;//ve cac tile bang sprite

	D3DXVECTOR2 positionWorld;
	D3DXVECTOR2 positionView;

	int** MAPDATA;
	int collumns;
	int rows;

	int tileWidth;
	int tileHeight;

	std::vector<Tile*> Tiles;
public:
	TileMap();
	void loadMap(std::string resourcepath, int id, Viewport* viewport);
	void draw(D3DXVECTOR2 postion);
	~TileMap();
};

