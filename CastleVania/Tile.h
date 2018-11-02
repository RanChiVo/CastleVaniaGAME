#pragma once
#include <string>
#include "../CastleVania/SpriteManagements/Sprite.h"

class Tile
{
private:
	int id;
	RECT rect;
	LPSPRITE spriteTile;

public:
	Tile(LPSPRITE spriteTile, RECT rect, int id);
	void draw(int id, D3DXVECTOR2 position);
	int getId() { return id; }

	~Tile();
};

