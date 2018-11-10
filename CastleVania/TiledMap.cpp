#include "TiledMap.h"
#include <d3dx9.h>
#include "DebugOut/DebugOut.h"
#include "Library/pugixml.hpp"

TiledMap::TiledMap()
{
}

void TiledMap::readMapfromfile(std::string resourcepath, LPDIRECT3DTEXTURE9 IDtex)
{
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(resourcepath.c_str());

	if (!result)
	{
		OutputDebugString(L"[ERROR] Reading failed\n");
		return;
	}
	auto sourceDoc = doc.child("map");

	tilesInMapHeight = sourceDoc.attribute("height").as_int();
	tilesInMapWidth = sourceDoc.attribute("width").as_int();
	tileWidth = sourceDoc.attribute("tilewidth").as_int();
	tileHeight = sourceDoc.attribute("tileheight").as_int();

	tileset = new TileSet(IDtex, tileWidth, tileHeight);
	tileset->createTileSet(tilesInMapWidth, tilesInMapHeight);
}

void TiledMap::draw(Viewport* viewport)
{
	int beginRow = viewport->getX() / tileWidth;
	int endRow = viewport->getWidth() / tileWidth + 1;
	int beginCol = viewport->getY() / tileHeight;
	int endCol = viewport->getHeight() / tileHeight + 1;

	beginRow = (beginRow < 0) ? 0 : ((beginRow > (tilesInMapWidth - 1)) ? (tilesInMapWidth - 1) : beginRow);
	endRow = (endRow < 0) ? 0 : ((endRow > (tilesInMapWidth - 1)) ? (tilesInMapWidth - 1) : endRow);
	beginCol = (beginCol < 0) ? 0 : ((beginCol > (tilesInMapHeight - 1)) ? (tilesInMapHeight - 1) : beginCol);
	endCol = (endCol < 0) ? 0 : ((endCol > (tilesInMapHeight - 1)) ? (tilesInMapHeight - 1) : endCol);

	for (int row = beginRow; row < endRow; row++)
	{
		for (int col = beginCol; col < endCol; col++)
		{
			auto tile = tileset->getPositionTile(row, col);
			auto rect = tile.getRect();
			worldPosition = D3DXVECTOR2{float(rect.left), float(rect.top) };
			viewPosition = viewport->WorldToScreen(worldPosition);

			tile.Draw(viewPosition);
		}
	}
}

TiledMap::~TiledMap()
{
}
