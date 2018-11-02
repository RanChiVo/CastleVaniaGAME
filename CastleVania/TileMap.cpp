#include "TileMap.h"
#include <d3dx9.h>
#include "DebugOut/DebugOut.h"
#include "Library/pugixml.hpp"
#include "Game.h"

TileMap::TileMap()
{
	 viewport = new ViewPort(0, ScreenBase_height, ScreenBase_width, ScreenBase_height);
}

RECT TileMap::loadMap(std::string resourcepath, int id)
{
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(resourcepath.c_str());

	if (result)
	{
		auto sourceDoc = doc.child("map").child("tileset");
	
		D3DXVECTOR2 Vector;

		positionWorld.x = sourceDoc.child("image").attribute("width").as_float();
		positionWorld.y = sourceDoc.child("image").attribute("height").as_float();

		Vector = positionWorld;

		D3DXVECTOR2 Object = viewport->WorldToScreen(Vector);

		positionView = Object;

		//Load Grid

		auto firstTildeId = sourceDoc.attribute("firstgid").as_int();
		tileWidth = sourceDoc.attribute("tilewidth").as_float();
		tileHeight = sourceDoc.attribute("tileheight").as_float();
		auto tileCount = sourceDoc.attribute("tilecount").as_float();

		RECT r = {
			0,
			0,
			tileWidth,
			tileHeight
		};

		while (tileCount--)
		{
			this->Tiles.push_back(new Tile(this->sprite, r, firstTildeId));
			firstTildeId++;

			if (r.right + tileWidth > positionWorld.x)
			{
				r.left = 0;
				r.top += tileHeight;
			}
			else
			{
				r.left += tileWidth;
				r.right = r.left + tileWidth;
				r.bottom = r.top + tileHeight;
			}
		}

		this->rows = positionWorld.y / tileHeight;
		this->collumns = positionWorld.x / tileWidth;

		MAPDATA = new int*[rows];	
		for (int i = 0; i < rows; i++)
		{
			MAPDATA[i] = new int[collumns];
		}

		auto gids = doc.child("map").child("data").children();
		int i = 0, j = 0;

		for (auto gid : gids)
		{
			MAPDATA[i][j] = gid.attribute("gid").as_int();
			j++;
			if (j >= collumns)
			{
				j = 0;
				i++;
			}
		}
	}
	else
	{
		OutputDebugString(L"[ERROR] Reading failed\n");
	}
	RECT R;

	R.left = int(positionView.x);
	R.top = int(positionView.y);
	R.right = int(positionView.x + viewport->getWidth());
	R.bottom = int(positionView.y - viewport->getHeight());

	return R;
}

void TileMap::draw(D3DXVECTOR2 position)
{
	for (int j = 0; j < collumns; j++)
	{
		for (int i = 0; i < rows; i++)
		{
			position.x = collumns * tileWidth;
			position.y = rows * tileHeight;

			for (auto tile : Tiles)
			{
				if (tile->getId() == MAPDATA[i][j])
				{
					tile->draw(MAPDATA[i][j],position);
					return;
				}
				else
				{
					continue;
				}
			}
			
		}
	}
}

TileMap::~TileMap()
{
}
