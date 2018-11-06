#include "Tile.h"

Tile::Tile(LPSPRITE spriteTile, RECT rect, int id)
{
	this->id = id;
	this->spriteTile = spriteTile;
	this->rect = rect;
}

void Tile::draw(int id, D3DXVECTOR2 position)
{	
	spriteTile->Draw(position);
}

Tile::~Tile()
{
}
