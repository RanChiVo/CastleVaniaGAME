#include "TileSet.h"
#include <string>

TileSet::TileSet(LPDIRECT3DTEXTURE9 IDTex, int tileWidth, int tileHeight)
{
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->IDTex = IDTex;
}

void TileSet::createTileSet(int rows, int columns)
{
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			RECT rect = { tileWidth* row, tileHeight* col, tileWidth* row + tileWidth, tileHeight*col + tileHeight };
			std::string id = std::to_string(row) + std::to_string(col);
			tile = Sprite(id, rect, IDTex);
			tiles.emplace(std::make_pair(row, col), tile);
		}
	}
}

Sprite& TileSet::getPositionTile(int row, int col)
{
	return tiles.at(std::make_pair(row, col));
}


TileSet::~TileSet()
{
}
