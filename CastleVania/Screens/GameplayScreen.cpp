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
	updateViewport(dt);

	for (int i = 0; i < staticObjects.size(); i++)
	{
		objects.push_back(staticObjects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &staticObjects);
	}
}

void GameplayScreen::updateViewport(float dt)
{
	D3DXVECTOR2 pos_Simon = simon->getPosition();

	D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};

	newPosViewport.x = simon->getPosition().x - viewport->getWidth() / 2;
	newPosViewport.y = viewport->getY();

	newPosViewport.x = min(tile_map->getWidthWorld() - viewport->getWidth(), newPosViewport.x);
	newPosViewport.y = min(tile_map->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
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
	for (int i = 0; i < staticObjects.size(); i++)
	{
		staticObjects[i]->Render(viewport);
	}
}

void GameplayScreen::loadResources()
{
	resourceManagement->textures->Add(ID_TEX_GAMEPLAYSCREEN, L"TiledMap\\Entrance.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 textPlayScreen = resourceManagement->textures->Get(ID_TEX_GAMEPLAYSCREEN);

	tile_map->readMapfromfile("TiledMap\\Entrance.tmx", textPlayScreen);

	simon->loadResource();
	objects.push_back(simon);

	for (auto object : tile_map->getObjectInfo())
	{
		if (object.first.second == "BurnBarrel")
		{
			BurnBarrel* burnbarrel = new BurnBarrel(object.second);
			staticObjects.push_back(burnbarrel);
		}
	}

	Heart* heart = new Heart(D3DXVECTOR2(0, -100));
	staticObjects.push_back(heart);

	WeaponReward* weaponReward = new WeaponReward(D3DXVECTOR2(0, -100));
	staticObjects.push_back(weaponReward);

	heart = new Heart(D3DXVECTOR2(0, -100));
	staticObjects.push_back(heart);

	weaponReward = new WeaponReward(D3DXVECTOR2(0, -100));
	staticObjects.push_back(weaponReward);

	Katana* katana = new Katana(D3DXVECTOR2(0, -100));
	staticObjects.push_back(katana);

	MiraculousBag* miraculousBag = new MiraculousBag(D3DXVECTOR2(0, -100));
	staticObjects.push_back(miraculousBag);

	for (int i = 0; i < 96; i++)
	{
		CBrick* brick = new CBrick();
		brick->SetPosition(D3DXVECTOR2(0 + i * 16.0f, 350));
		staticObjects.push_back(brick);
	}

	for (int i = 0; i < 20; i++)
	{
		CBrick* brick = new CBrick();
		brick->SetPosition(D3DXVECTOR2(0, 0 + i * 16.0f));
		staticObjects.push_back(brick);
	}

	for (int i = 0; i < 20; i++)
	{
		CBrick* brick = new CBrick();
		brick->SetPosition(D3DXVECTOR2(1500, 0 + i * 16.0f));
		staticObjects.push_back(brick);
	}
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
