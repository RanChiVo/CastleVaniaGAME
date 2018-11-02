#include "GameplayScreen.h"

constexpr int  ID_TEX_GAMEPLAYSCREEN = 2;

void GameplayScreen::init()
{
	tile_map = new TileMap();
}

void GameplayScreen::update(float dt)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
}

void GameplayScreen::renderObject()
{
	D3DXVECTOR2 position;
	position.x = RECT.left;
	position.y = RECT.top;

	tile_map->draw(position);

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void GameplayScreen::loadResources()
{
	resourceManagement->textures->Add(ID_TEX_GAMEPLAYSCREEN, L"map\\mapEntrance.png", D3DCOLOR_XRGB(0, 0, 0));

	LPDIRECT3DTEXTURE9 textPlayScreen = resourceManagement->textures->Get(ID_TEX_GAMEPLAYSCREEN);

	RECT = tile_map->loadMap("map\\EntranceMap.tmx", 1);

	Sprite * Map = new Sprite("Texture1", RECT.left, RECT.top, RECT.right, RECT.bottom, textPlayScreen);

	simon->loadResource();

	objects.push_back(simon);
}

GameplayScreen::GameplayScreen()
{
	tile_map = new TileMap();

	directInput = DirectInput::getInstance();

	simon = new Simon();

	resourceManagement = ResourceManagement::GetInstance();
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
}
