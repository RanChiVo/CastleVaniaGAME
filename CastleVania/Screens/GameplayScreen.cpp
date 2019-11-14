#include "GameplayScreen.h"
#include "../WindowUtil.h"
#include "../Direct3DManager.h"
#include "../Candle.h"
#include "../PodiumOnWall.h"
#include "../WallEntrance.h"
#include "../CollisionStair.h"
#include "../AreaZombie.h"
#include "../GameObjects/BlackLeopard.h"
#include "../GameObjects/Zombie.h"
#include "../Brick.h"
#include "../GameObjects/Floor.h"
#include "../GameObjects/GameObject.h"
#include "../CastleWall.h"
#include "../GameObjects/BurnBarrel.h"
#include "../Candle.h"
#include "../GameObjects/Entrance.h"
#include "../ObjectStair.h"

void GameplayScreen::init()
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	viewport = direct3D->getViewport();
}

void GameplayScreen::update(DWORD dt)
{
	menu_point->update();

	updateViewport(dt);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);

		if (objects[i]->getID() == ID_ENTITY_SIMON)
		{
			if (mapId == ID_ENTITY_MAP_ENTRANCE)
			{
				if (objects[i]->getLevel() == 1)
				{
					resourceManagement->getTiledMap(mapId)->clearObjectInfo();
					mapId = ID_ENTITY_MAP_PLAYGAME;
					moveMap = true;
				}
			}
		}
		if (objects[i]->GetState() == objects[i]->STATE_DETROY)
		{
			objects.erase(objects.begin() + i);
		}
	}

	if (moveMap)
	{
		loadResources();
		moveMap = false;
	}

	if (mapId == ID_ENTITY_MAP_PLAYGAME)
	{
		/*if (time == 0)
		{
			time = GetTickCount();
			createZombie(viewport);
		}
		if (GetTickCount() - time >= TIME_ZOMBIE)
		{
			time = 0;
		}*/
	}
}

void GameplayScreen::updateViewport(DWORD dt)
{
	D3DXVECTOR2 pos_Simon = simon->getPosition();

	int widthframeSimon = simon->getWidth();

	D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};

	newPosViewport.x = simon->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
	newPosViewport.y = viewport->getY();

	newPosViewport.x = min(resourceManagement->getTiledMap(mapId)->getWidthWorld() - viewport->getWidth(), newPosViewport.x);
	newPosViewport.y = min(resourceManagement->getTiledMap(mapId)->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
	newPosViewport.x = max(0, newPosViewport.x);
	newPosViewport.y = max(0, newPosViewport.y);

	viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
}

void GameplayScreen::renderObject()
{
	resourceManagement->getTiledMap(mapId)->draw(viewport);
	menu_point->Draw();
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render(viewport);
	}
}

void GameplayScreen::createZombie(Viewport* viewport)
{
	for (int i = 0; i < 3; i++)
	{
		Zombie* zombie = new Zombie();
		zombie->SetState(ZOMBIE_STATE_WALKING_RIGHT);
		zombie->SetPosition(D3DXVECTOR2(viewport->getX() + i * 60, 295));
		objects.push_back(zombie);

		zombie = new Zombie();
		zombie->SetState(ZOMBIE_STATE_WALKING_LEFT);
		zombie->SetPosition(D3DXVECTOR2(viewport->getX() + viewport->getWidth() - i * 60, 295));
		objects.push_back(zombie);
	}
}

void GameplayScreen::getInfoFromObjectInfo(ObjectInfo::builder* info, LPGAMEOBJECT object)
{
	object->setName(info->get_name());
	object->SetPosition(info->get_postition());
	object->setHeight(info->get_height());
	object->setWidth(info->get_width());
	object->setIdHiddenItem(info->get_idHiddenItem());
}

void GameplayScreen::loadResources()
{
	objects.clear();
	CastleWall* castleWall = nullptr;
	for (auto object : resourceManagement->getTiledMap(mapId)->getObjectInfo())
	{
		StaticObject* objectInit = nullptr;
		idObject = resourceManagement->getStringToEntity()[object->get_ObjectId()];
		switch (idObject)
		{
		case ID_ENTITY_FLOOR:
			objectInit = new Floor();
			break;
		case ID_ENTITY_BURNBARREL:
			objectInit = new BurnBarrel();
			break;
		case ID_ENTITY_ENTRANCE:
			objectInit = new Entrance();
			break;
		case ID_ENTITY_WALL_ENTRANCE:
			objectInit = new WallEntrance();
			break;
		case ID_ENTITY_CANDLE:
			objectInit = new Candle();
			break;
		case ID_ENTITY_SIMON:
			simon = new Simon();
			simon->loadResource();
			getInfoFromObjectInfo(object, simon);
			objects.push_back(simon);
			break;
		case ID_ENTITY_CASTLEVANIA_WALL:
			objectInit = new CastleWall();
			break;
		case ID_ENTITY_STAIR:
			objectInit = new ObjectStair(object->get_postition(), D3DXVECTOR4(object->get_width(), 
				object->get_height(), object->get_nx(), object->get_ny()), object->get_stairHeight());
			break;
		}	

		if (objectInit)
		{
			if (idObject != ID_ENTITY_STAIR)
			{
				getInfoFromObjectInfo(object, objectInit);
			}
			objects.push_back(objectInit);
		}
	}
	menu_point->loadResource();
}

GameplayScreen::GameplayScreen()
{
	resourceManagement = ResourceManagement::GetInstance();

	mapId = ID_ENTITY_MAP_ENTRANCE;

	menu_point = new MenuPoint();
}

GameplayScreen::~GameplayScreen()
{
	delete simon;
	delete menu_point;
}
