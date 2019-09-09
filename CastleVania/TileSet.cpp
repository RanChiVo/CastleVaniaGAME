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
	int idTile = 0;
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			idTile++;
			RECT rect = { tileWidth* col, tileHeight * row, tileWidth * col + tileWidth, tileHeight * row + tileHeight };
			tile = Sprite(std::to_string(idTile), rect, IDTex);
			tiles.emplace(std::to_string(idTile), tile);
		}
	}
}

Sprite& TileSet::getPositionTile(std::string idTile)
{
	return tiles.at(idTile);
}

TileSet::~TileSet()
{
}