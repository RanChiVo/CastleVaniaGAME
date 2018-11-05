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
	Map->Draw(0,0);
	
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void GameplayScreen::loadResources()
{
	resourceManagement->textures->Add(ID_TEX_GAMEPLAYSCREEN, L"map\\mapEntrance.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 textPlayScreen = resourceManagement->textures->Get(ID_TEX_GAMEPLAYSCREEN);

	tile_map->loadMap("map\\EntranceMap.tmx", 1, viewport);

	Map = new Sprite("Texture1", 0, 0, 640, 480, textPlayScreen);

	simon->loadResource();
	
	objects.push_back(simon);
}

GameplayScreen::GameplayScreen()
{
	tile_map = new TileMap();

	directInput = DirectInput::getInstance();

	simon = new Simon();

	resourceManagement = ResourceManagement::GetInstance();

	viewport = new Viewport(0, ScreenBase_height, ScreenBase_width, ScreenBase_height);
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
}
