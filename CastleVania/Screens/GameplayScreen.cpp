#include "GameplayScreen.h"
#include "../WindowUtil.h"
#include "../Direct3DManager.h"

void GameplayScreen::init()
{
	tile_map = new TiledMap();
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
	position.x = rect.left;
	position.y = rect.top;

	Direct3DManager* direct3D = Direct3DManager::getInstance();
	
	tile_map->draw(direct3D->getViewport());
	
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void GameplayScreen::loadResources()
{
	resourceManagement->textures->Add(ID_TEX_GAMEPLAYSCREEN, L"TiledMap\\Intro.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 textPlayScreen = resourceManagement->textures->Get(ID_TEX_GAMEPLAYSCREEN);

	tile_map->readMapfromfile("TiledMap\\Intro.tmx", textPlayScreen);

	simon->loadResource();
	
	objects.push_back(simon);
}

GameplayScreen::GameplayScreen()
{
	tile_map = new TiledMap();

	directInput = DirectInput::getInstance();

	simon = new Simon();

	resourceManagement = ResourceManagement::GetInstance();

	viewport = new Viewport(0, ScreenBase_height, ScreenBase_width, ScreenBase_height);
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
}
