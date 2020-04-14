#include "TiledMap.h"
#include <d3dx9.h>
#include <sstream>
#include "EntityID.h"
#include "SpriteManagements/Sprite.h"
#include "Utils.h"
#include "Textures/Textures.h"

constexpr int TILEMAP_CROSS_EFFECT_TIME = 1000;

DWORD TiledMap::createEffectStart;

TiledMap::TiledMap(pugi::xml_node node)
{
	this->rootNode = node;
	createEffectStart = 0;
}

void TiledMap::Update(DWORD dt, vector<LPGAMEOBJECT>* object)
{
	if (createEffectStart > 0 && GetTickCount() - createEffectStart > TILEMAP_CROSS_EFFECT_TIME)
		createEffectStart = 0;
}

void TiledMap::readMapfromfile()
{
	tilesInMapHeight = rootNode.attribute("height").as_int();
	tilesInMapWidth = rootNode.attribute("width").as_int();
	tileWidth = rootNode.attribute("tilewidth").as_int();
	tileHeight = rootNode.attribute("tileheight").as_int();
	//size of the game world
	widthWorld = tilesInMapWidth * tileWidth;
	heightWorld = tilesInMapHeight * tileHeight;

	//create tileset
	tileSetWidth = rootNode.child("tileset").child("image").attribute("width").as_float();
	tileSetHeight = rootNode.child("tileset").child("image").attribute("height").as_float();
	std::string pathImageMap = rootNode.child("imagelayer").child("image").attribute("source").as_string();
	std::string idText = rootNode.child("imagelayer").child("image").attribute("id").as_string();
	EntityID idTextfromfile = stringToEntityID[idText];

	std::wstring pathImageMapfromfile(pathImageMap.begin(), pathImageMap.end());
	LPCWSTR pathImageMapLoad = pathImageMapfromfile.c_str();
	Textures::GetInstance()->Add(idTextfromfile, pathImageMapLoad, D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texID = Textures::GetInstance()->Get(idTextfromfile);
	tileset = new TileSet(IDtex, tileWidth, tileHeight);
	int rowsTileSet = tileSetHeight / tileHeight;
	int colsTileSet = tileSetWidth / tileWidth;
	tileset->createTileSet(rowsTileSet, colsTileSet);
	//read MatrixMap
	this->readMatrixMap();
}

void TiledMap::readMatrixMap()
{
	auto layerNode = rootNode.child("layer");
	auto dataNote = layerNode.child("data");
	mapIndices = dataNote.first_child().value();
	// data into matrix map
	eraseAllSubStr(mapIndices, "\n");
	findAndReplaceAll(mapIndices, ",", " ");
	std::string line;
	matrixMap = new std::string*[tilesInMapHeight];
	for (int i = 0; i < tilesInMapHeight; i++)
	{
		matrixMap[i] = new std::string[tilesInMapWidth];
	}
	int row = 0;
	int col = 0;
	std::stringstream spliter;
	spliter << mapIndices;
	while (!spliter.eof())
	{
		std::string str;
		spliter >> str;
		matrixMap[row][col] = str;
		col++;
		if (col >= tilesInMapWidth)
		{
			col = 0;
			row++;
		}
	}
}

void TiledMap::draw(Viewport* viewport, int alpha)
{
	int beginCol = viewport->getX() / tileWidth;
	int endCol = (viewport->getX() + viewport->getWidth()) / tileWidth + 1;
	int beginRow = viewport->getY() / tileHeight;
	int endRow = (viewport->getY() + viewport->getHeight())/ tileHeight + 1;

	beginCol = (beginCol < 0) ? 0 : ((beginCol > (tilesInMapWidth)) ? (tilesInMapWidth) : beginCol);
	endCol = (endCol < 0) ? 0 : ((endCol > (tilesInMapWidth)) ? (tilesInMapWidth) : endCol);
	beginRow = (beginRow < 0) ? 0 : ((beginRow > (tilesInMapHeight)) ? (tilesInMapHeight) : beginRow);
	endRow = (endRow < 0) ? 0 : ((endRow > (tilesInMapHeight)) ? (tilesInMapHeight) : endRow);

	if (createEffectStart > 0)
	{
		alpha = GetTickCount() % 100 > 50 ? 80 : 255;
		if (alpha == 80)
			Direct3DManager::getInstance()->
			GetDirect3DDevice()->ColorFill(Direct3DManager::getInstance()->GetBackBuffer(), NULL, D3DXCOLOR(0xBBBBBB));
	}

	for (int row = beginRow; row < endRow; row++)
	{
		for (int col = beginCol; col < endCol; col++)
		{
			auto tile = tileset->getPositionTile(matrixMap[row][col]);
			worldPosition.x = tileWidth * col;
			worldPosition.y = tileHeight * row + EXTRA_HEIGHT_SCREEN;
			viewPosition = viewport->WorldToScreen(worldPosition);
			tile.Draw(viewPosition, alpha);
		}
	}
}

float TiledMap::getHeightWorld()
{
	return heightWorld;
}

float TiledMap::getWidthWorld()
{
	return widthWorld;
}

void TiledMap::setHeightWorld(float heightWorld)
{
	this->heightWorld = heightWorld;
}

void TiledMap::setWidthWorld(float widthWorld)
{
	this->widthWorld = widthWorld;
}

TiledMap::~TiledMap()
{
	delete tileset;

	for (int i = 0; i < tilesInMapHeight; i++)
		delete[] matrixMap[i];
	delete[] matrixMap;
}
