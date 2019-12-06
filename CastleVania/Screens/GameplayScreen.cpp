#include "GameplayScreen.h"
#include "../WindowUtil.h"
#include "../Direct3DManager.h"
#include "../Candle.h"
#include "../PodiumOnWall.h"
#include "../WallEntrance.h"
#include "../CollisionStair.h"
#include "../AreaZombie.h"
#include "../GameObjects/Zombie.h"
#include "../Brick.h"
#include "../GameObjects/Floor.h"
#include "../GameObjects/GameObject.h"
#include "../CastleWall.h"
#include "../GameObjects/BurnBarrel.h"
#include "../Candle.h"
#include "../GameObjects/Entrance.h"
#include "../ObjectStair.h"
#include "../Panther.h"
#include "../VampireBat.h"
#include "../FishMan.h"
#include "../Door.h"

void GameplayScreen::init()
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	viewport = direct3D->getViewport();
}

void GameplayScreen::update(DWORD dt)
{
	menu_point->update();

	resourceManagement->getTiledMap(mapId)->Update(dt, &objects);

	updateViewport(dt);

	updateMap();

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);
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
}

void GameplayScreen::updateViewport(DWORD dt)
{
	if (viewport->getState() == viewport->STATE_ACTION)
	{
		D3DXVECTOR2 pos_Simon = Simon::getInstance()->getPosition();

		int widthframeSimon = Simon::getInstance()->getWidth();
		D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};


		if (Simon::getInstance()->isMovedMap())
		{
			extraWidth = viewport->getX();
			//resourceManagement->getTiledMap(mapId)->setWidthWorld(extraWidth);

			Simon::getInstance()->SetStateMoveMap(false);
		}

		newPosViewport.x = Simon::getInstance()->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
		newPosViewport.x = min(resourceManagement->getTiledMap(mapId)->getWidthWorld()  - viewport->getWidth(), newPosViewport.x);
		//newPosViewport.y = min(resourceManagement->getTiledMap(mapId)->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
		
		newPosViewport.x = max(0 + extraWidth, newPosViewport.x);
		//newPosViewport.y = max(0, newPosViewport.y);
		viewport->setX(float(newPosViewport.x));
		//viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
	}
	else return;
}

void GameplayScreen::updateMap()
{
	switch (mapId)
	{
	case ID_ENTITY_MAP_ENTRANCE:
		if (Simon::getInstance()->getLevel() == 1)
		{
			resourceManagement->getTiledMap(mapId)->clearObjectInfo();
			mapId = ID_ENTITY_MAP_PLAYGAME;
			moveMap = true;
		}
		break;
	case ID_ENTITY_MAP_PLAYGAME:
		updateEnemy();
		break;
	}
}

void GameplayScreen::updateEnemy()
{
	checkSimonInSpawn = Simon::getInstance()->checkisInSpawn();
	idEnemy = Simon::getInstance()->getIdEnemySpawn();
	if (checkSimonInSpawn)
{
		if (idEnemy == ID_ENTITY_ZOMBIE)
		{
			if (time == 0)
			{
				time = GetTickCount();
				if (idEnemy == ID_ENTITY_ZOMBIE)
				{
					createZombie(viewport);
				}
			}
		}
	}

	if ((GetTickCount() - time >= TIME_ZOMBIE) && idEnemy == ID_ENTITY_ZOMBIE)
	{
		time = 0;
		Simon::getInstance()->setIsInSpawn(false);
	}
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
		if (RandomEnemy == 1)
		{
			Zombie* zombie = new Zombie();
			zombie->SetState(ZOMBIE_STATE_WALKING_RIGHT);
			zombie->SetPosition(D3DXVECTOR2(viewport->getX() + i * 60, 344));
			objects.push_back(zombie);
		}
		else
		{
			Zombie* zombie = new Zombie();
			zombie->SetState(ZOMBIE_STATE_WALKING_LEFT);
			zombie->SetPosition(D3DXVECTOR2(viewport->getX() + viewport->getWidth() - i * 60, 344));
			objects.push_back(zombie);
		}
	}
	RandomEnemy = -RandomEnemy;
}

void GameplayScreen::getInfoFromObjectInfo(ObjectInfo::builder* info, LPGAMEOBJECT object)
{
	object->setName(info->get_name());
	object->SetPosition(info->get_postition());
	object->setHeight(info->get_height());
	object->setWidth(info->get_width());
	object->setIdHiddenItem(info->get_idHiddenItem());
	object->setEnemyName(info->get_enemyName());
}

void GameplayScreen::loadResources()
{
	objects.clear();
	CastleWall* castleWall = nullptr;
	for (auto object : resourceManagement->getTiledMap(mapId)->getObjectInfo())
	{
		StaticObject* objectInit = nullptr;
		Enemy* objectEnemy = nullptr;
		idObject = resourceManagement->getStringToEntity()[object->get_ObjectId()];
		switch (idObject)
		{
		case ID_ENTITY_FLOOR:
			objectInit = new Floor();
			break;
		case ID_ENTITY_DOOR:
			objectInit = new Door(object->get_postition());
			break;
		case ID_ENTITY_BRICK:
			objectInit = new CBrick(object->get_name());
			break;
		case ID_ENTITY_BURNBARREL:
			objectInit = new BurnBarrel();
			break;
		case ID_ENTITY_VAMPIRE_BAT:
			objectEnemy = new VampireBat();
			getInfoFromObjectInfo(object, objectEnemy);
			objects.push_back(objectEnemy);
			break;
		case ID_ENTITY_ENTRANCE:
			objectInit = new Entrance();
			break;
		case ID_ENTITY_WALL_ENTRANCE:
			objectInit = new WallEntrance();
			objectInit->set_nx(object->get_nx());
			break;
		case ID_ENTITY_CANDLE:
			objectInit = new Candle();
			break;
		case ID_ENTITY_FISH_MAN:
			objectEnemy = new FishMan(object->get_postition());
			getInfoFromObjectInfo(object, objectEnemy);
			objects.push_back(objectEnemy);
			break;
		case ID_ENTITY_SIMON:
			Simon::getInstance()->loadResource();
			getInfoFromObjectInfo(object, Simon::getInstance());
			objects.push_back(Simon::getInstance());
			break;
		case ID_ENTITY_CASTLEVANIA_WALL:
			objectInit = new CastleWall();
			break;
		case ID_ENTITY_STAIR:
			objectInit = new ObjectStair(object->get_postition(), D3DXVECTOR4(object->get_width(),
				object->get_height(), object->get_nx(), object->get_ny()), object->get_stairHeight());
			break;
		case ID_ENTITY_PANTHER:
			objectEnemy = new Panther(object->get_postition(), object->get_nx());
			getInfoFromObjectInfo(object, objectEnemy);
			objects.push_back(objectEnemy);
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
	delete Simon::getInstance();
	delete menu_point;
}
