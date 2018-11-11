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

void GameplayScreen::updateViewport(float dt)
{
	D3DXVECTOR2 pos_Simon = simon->getPosSimon();
	
	D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};
	D3DXVECTOR2 pos_World =  viewport->ScreenToWorld(D3DXVECTOR2(viewport->getX(), viewport->getY()));
	
	newPosViewport.x = pos_World.x - pos_Simon.x / 2;
	newPosViewport.y = viewport->getY();

	viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
}

void GameplayScreen::renderObject()
{
	D3DXVECTOR2 position;
	position.x = rect.left;
	position.y = rect.top;

	Direct3DManager* direct3D = Direct3DManager::getInstance();
	
	viewport = direct3D->getViewport();

	tile_map->draw(viewport);
	
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
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
}
