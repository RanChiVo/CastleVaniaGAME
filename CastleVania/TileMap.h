#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SpriteManagements/Sprite.h"

using namespace std;

class TileMap
{
private:

	int**  MAPDATA;
	int collumns;
	int rows;
	int mapWidth;
	int mapHeight;

	int tileWidth;
	int tileHeight;
	RECT rect;
	D3DXVECTOR2 positionTile;

public:
	TileMap();

	void init();
	void loadTiles();
	void drawTiles();

	~TileMap();
};

