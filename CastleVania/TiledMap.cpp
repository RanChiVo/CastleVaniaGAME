#include "TiledMap.h"
#include <d3dx9.h>
#include "DebugOut/DebugOut.h"
#include "Library/pugixml.hpp"
#include "ResourceManagement.h"
#include "EntityID.h"

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

	widthWorld = sourceDoc.child("imagelayer").child("image").attribute("width").as_float();
	heightWorld = sourceDoc.child("imagelayer").child("image").attribute("height").as_float();

	tileset = new TileSet(IDtex, tileWidth, tileHeight);
	tileset->createTileSet(tilesInMapWidth, tilesInMapHeight);

	auto objectGroupNode = sourceDoc.child("objectgroup");

	for (auto objectNode : objectGroupNode.children("object"))
	{
		int id = objectNode.attribute("id").as_int();
		std::string name = objectNode.attribute("name").as_string();
		float x = objectNode.attribute("x").as_float();
		float y = objectNode.attribute("y").as_float();
		int width = objectNode.attribute("width").as_int();
		int height = objectNode.attribute("height").as_int();
		
		auto properties = objectNode.child("properties");
		std::string idHiddenItemString = properties.child("property").attribute("value").as_string();

		ResourceManagement* resource = ResourceManagement::GetInstance();
		
		ObjectInfo* info_object = new ObjectInfo(id, name, height, width, D3DXVECTOR2(x, y), idHiddenItemString);
		objectInfo.push_back(info_object);
	}


}

std::vector<ObjectInfo*> TiledMap::getObjectInfo()
{
	return objectInfo;
}

void TiledMap::draw(Viewport* viewport)
{
	int beginRow = viewport->getX() / tileWidth;
	int endRow = viewport->getX() + viewport->getWidth() / tileWidth + 1;
	int beginCol = viewport->getY() / tileHeight;
	int endCol = viewport->getY() + viewport->getHeight() / tileHeight + 1;

	beginRow = (beginRow < 0) ? 0 : ((beginRow > (tilesInMapWidth)) ? (tilesInMapWidth) : beginRow);
	endRow = (endRow < 0) ? 0 : ((endRow > (tilesInMapWidth)) ? (tilesInMapWidth) : endRow);
	beginCol = (beginCol < 0) ? 0 : ((beginCol > (tilesInMapHeight)) ? (tilesInMapHeight) : beginCol);
	endCol = (endCol < 0) ? 0 : ((endCol > (tilesInMapHeight)) ? (tilesInMapHeight) : endCol);

	for (int row = beginRow; row < endRow; row++)
	{
		for (int col = beginCol; col < endCol; col++)
		{
			auto tile = tileset->getPositionTile(row, col);
			auto rect = tile.getRect();
			worldPosition = D3DXVECTOR2{ float(rect.left), float(rect.top) };
			viewPosition = viewport->WorldToScreen(worldPosition);

			tile.Draw(viewPosition);
		}
	}
}

float TiledMap::getWidthWorld()
{
	return widthWorld;
}

float TiledMap::getHeightWorld()
{
	return heightWorld;
}

TiledMap::~TiledMap()
{
}
