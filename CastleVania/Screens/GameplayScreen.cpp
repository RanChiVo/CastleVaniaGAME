#include "GameplayScreen.h"
#include "../WindowUtil.h"
#include "../Direct3DManager.h"

void GameplayScreen::init()
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	viewport = direct3D->getViewport();
}

void GameplayScreen::update(float dt)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
	updateViewport(dt);
}

void GameplayScreen::updateViewport(float dt)
{
	D3DXVECTOR2 pos_Simon = simon->getPosition();

	D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};

	newPosViewport.x = simon->getPosition().x - viewport->getWidth() / 2;
	newPosViewport.y = viewport->getY();

	newPosViewport.x = min(tile_map->getWidthWorld() - viewport->getWidth(), newPosViewport.x);
	newPosViewport.y = min(tile_map->getHeightWorld() - viewport->getHeight() , newPosViewport.y);
	newPosViewport.x = max(0, newPosViewport.x);
	newPosViewport.y = max(0, newPosViewport.y);

	viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
}

void GameplayScreen::renderObject()
{
	tile_map->draw(viewport);
	
	
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(viewport);
	}
}

void GameplayScreen::loadResources()
{
	resourceManagement->textures->Add(ID_TEX_GAMEPLAYSCREEN, L"TiledMap\\Entrance.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 textPlayScreen = resourceManagement->textures->Get(ID_TEX_GAMEPLAYSCREEN);

	tile_map->readMapfromfile("TiledMap\\Entrance.tmx", textPlayScreen);

	simon->loadResource();

	for (auto object : tile_map->getObjectInfo())
	{
		if (object.first.second == "BurnBarrel")
		{
			burnbarrel = new BurnBarrel(object.second);
			objects.push_back(burnbarrel);
		}
	}
	objects.push_back(simon);
}

GameplayScreen::GameplayScreen()
{
	tile_map = new TiledMap();

	directInput = DirectInput::getInstance();

	simon = new Simon();

	resourceManagement = ResourceManagement::GetInstance();
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
}
