#include "GameplayScreen.h"
#include "../WindowUtil.h"
#include "../Direct3DManager.h"
#include "../CastleWall.h"
#include "../Candle.h"
#include "../PodiumOnWall.h"
#include "../WallEntrance.h"

void GameplayScreen::init()
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	viewport = direct3D->getViewport();
}

void GameplayScreen::update(float dt)
{
	updateViewport(dt);
	vector< LPGAMEOBJECT> staticObjects;

	if (id == ID_TEX_MAP_ENTRANCE)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			staticObjects.push_back(objects[i]);
		}

		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[0]->IsChangeLevel())
			{
				id = ID_TEX_MAP_PLAYGAME;

			}
			objects[i]->Update(dt, &staticObjects);
		}
	}
	else
	{

		for (int i = 0; i < objectslv2.size(); i++)
		{
			staticObjects.push_back(objectslv2[i]);
		}

		for (int i = 0; i < objectslv2.size(); i++)
		{
			if (objectslv2[0]->IsChangeLevel())
			{
				id = ID_TEX_MAP_PLAYGAME;

			}
			objectslv2[i]->Update(dt, &staticObjects);
		}
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

	if (id == ID_TEX_MAP_ENTRANCE)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (i == 0)
			{
				objects[i]->setWidthWorld(tile_map->getWidthWorld());
			}
			objects[i]->Render(viewport);
		}
	}
	else
	{
		objects.erase(objects.begin() + 2, objects.begin() + objects.size());
		for (int i =  objectslv2.size() - 1; i >= 0; i--)
		{
			if (i == 0)
			{
				objectslv2[i]->setWidthWorld(tile_map->getWidthWorld());
			}
			objectslv2[i]->Render(viewport);
		}
	}
}

void GameplayScreen::loadResources()
{
	simon->loadResource();
	objects.push_back(simon);
	objectslv2.push_back(simon);

	Floor* floor = new Floor();
	floor->SetPosition(D3DXVECTOR2(0, 350));
	objects.push_back(floor);
	objectslv2.push_back(floor);

	D3DXVECTOR2 posEntrance;

	for (auto object : resourceManagement->getTiledMap(id)->getObjectInfo())
	{
		if (object.first.second == "CastleWall")
		{
			CastleWall* castlewall = new CastleWall();
			castlewall->SetPosition(object.second);
			objects.push_back(castlewall);
		}
		else if (object.first.second == "BurnBarrel")
		{
			BurnBarrel* burnbarrel = new BurnBarrel(object.second);
			objects.push_back(burnbarrel);
		}
		else if (object.first.second == "Entrance")
		{
			Entrance* entrance = new Entrance(object.second);
			objects.push_back(entrance);
		}
		else if (object.first.second == "wall_frontof_entrance")
		{
			CBrick* Brick = new CBrick(object.second);
			objects.push_back(Brick);
		}
		else if (object.first.second == "wall_behind_entrance")
		{
			WallEntrance* wallEntrance = new WallEntrance(object.second);
			objects.push_back(wallEntrance);
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

	MiraculousBag* miraculousBag = new MiraculousBag(D3DXVECTOR2(0, -100));
	objects.push_back(miraculousBag);

	KatanaWeapon * katanaWeapon = new KatanaWeapon(D3DXVECTOR2(-200, -100));
	objects.push_back(katanaWeapon);

	for (auto object : resourceManagement->getTiledMap(ID_TEX_MAP_PLAYGAME)->getObjectInfo())
	{
		if (object.first.second == "Candle")
		{
			Candle* candle = new Candle(object.second);
			objectslv2.push_back(candle);
		}
		else if (object.first.second == "podium_on_wall1")
		{
			for (int i = 0; i < 3; i++)
			{
				PodiumOnWall* podium = new PodiumOnWall(D3DXVECTOR2((i + 1)* object.second.x, object.second.y));
				objectslv2.push_back(podium);
			}
		}
		else if (object.first.second == "podium_on_wall2")
		{
			for (int i = 0; i < 10; i++)
			{
				PodiumOnWall* podium = new PodiumOnWall(D3DXVECTOR2((i + 1)* object.second.x, object.second.y));
				objectslv2.push_back(podium);
			}
		}
		else if (object.first.second == "podium_on_wall3")
		{
			for (int i = 0; i < 6; i++)
			{
				PodiumOnWall* podium = new PodiumOnWall(D3DXVECTOR2((i + 1)* object.second.x, object.second.y));
				objectslv2.push_back(podium);
			}
		}
		else if (object.first.second == "podium_on_wall4")
		{
			for (int i = 0; i < 10; i++)
			{
				PodiumOnWall* podium = new PodiumOnWall(D3DXVECTOR2((i + 1)* object.second.x, object.second.y));
				objectslv2.push_back(podium);
			}
		}
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
