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
	vector< LPGAMEOBJECT> staticObjects;

	for (int i = 0; i < objects.size(); i++)
	{
		staticObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[0]->IsChangeLevel())
		{
			id = ID_TEX_MAP_PLAYGAME;

			//objects[0]->SetPosition(D3DXVECTOR2(50, objects[0]->getPosition().y));
		}
		objects[i]->Update(dt, &staticObjects);
	}
}

void GameplayScreen::updateViewport(float dt)
{
	D3DXVECTOR2 pos_Simon = simon->getPosition();

	RECT r = resourceManagement->getSprite(ID_TEX_SIMON)->Get("Walking1")->getRect();
	int widthframeSimon = (r.right - r.left);

	D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};

	newPosViewport.x = simon->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
	newPosViewport.y = viewport->getY();

	newPosViewport.x = min(tile_map->getWidthWorld() - viewport->getWidth(), newPosViewport.x);
	newPosViewport.y = min(tile_map->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
	newPosViewport.x = max(0, newPosViewport.x);
	newPosViewport.y = max(0, newPosViewport.y);

	viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
}

void GameplayScreen::renderObject()
{	
	tile_map = resourceManagement->getTiledMap(id);
	tile_map->draw(viewport);
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render(viewport);
	}
}

void GameplayScreen::loadResources()
{
	simon->loadResource();
	objects.push_back(simon);

	if (id != ID_TEX_MAP_ENTRANCE)
	{
		return;
	}
	else
	{
		D3DXVECTOR2 posEntrance;

		for (auto object : resourceManagement->getTiledMap(id)->getObjectInfo())
		{
			if (object.first.second == "BurnBarrel")
			{
				BurnBarrel* burnbarrel = new BurnBarrel(object.second);
				objects.push_back(burnbarrel);
			}
			else if (object.first.second == "Entrance")
			{
				posEntrance = object.second;
			}
		}

		Heart* heart = new Heart(D3DXVECTOR2(0, -100));
		objects.push_back(heart);

		WeaponReward* weaponReward = new WeaponReward(D3DXVECTOR2(0, -100));
		objects.push_back(weaponReward);

		heart = new Heart(D3DXVECTOR2(0, -100));
		objects.push_back(heart);

		weaponReward = new WeaponReward(D3DXVECTOR2(0, -100));
		objects.push_back(weaponReward);

		Katana* katana = new Katana(D3DXVECTOR2(0, -100));
		objects.push_back(katana);

	//	MiraculousBag* miraculousBag = new MiraculousBag(D3DXVECTOR2(0, -100));
	//	objects.push_back(miraculousBag);

		Floor* floor = new Floor();
		floor->SetPosition(D3DXVECTOR2(0, 350));
		objects.push_back(floor);

		for (int i = 0; i < 2; i++)
		{
			CBrick* brick = new CBrick();
			brick->SetPosition(D3DXVECTOR2(0 + i * 1500, 0));
			objects.push_back(brick);
		}

		Entrance* entrance = new Entrance(D3DXVECTOR2(-200, -100));
		entrance->setNewposition(posEntrance);
		objects.push_back(entrance);

		KatanaWeapon * katanaWeapon = new KatanaWeapon(D3DXVECTOR2(-200, -100));
		objects.push_back(katanaWeapon);
	}
}

GameplayScreen::GameplayScreen()
{
	directInput = DirectInput::getInstance();

	simon = new Simon();

	resourceManagement = ResourceManagement::GetInstance();

	tile_map = new TiledMap();

	id = ID_TEX_MAP_ENTRANCE;
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
}
