#include "GameplayScreen.h"
#include "../WindowUtil.h"
#include "../Direct3DManager.h"
#include "../Candle.h"
#include "../PodiumOnWall.h"
#include "../WallEntrance.h"
#include "../CollisionStair.h"
#include "../GameObjects/Zombie.h"
#include "../GameObjects/Cross.h"
#include "../GameObjects/SmallHeart.h"
#include "../GameObjects/FireBomb.h"
#include "../GameObjects/StopWatch.h"
#include "../GameObjects/MiraculousBag.h"
#include "../AreaZombie.h"
#include "../GameObjects/BlackLeopard.h"

void GameplayScreen::init()
{
	Direct3DManager* direct3D = Direct3DManager::getInstance();
	viewport = direct3D->getViewport();
}

void GameplayScreen::update(float dt)
{
	menu_point->update();

	updateViewport(dt);

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &objects);

		if (objects[i]->getID() == ID_ENTITY_SIMON)
		{
			if (id == ID_ENTITY_MAP_ENTRANCE)
			{
				if (objects[i]->getLevel() == 1)
				{
					id = ID_ENTITY_MAP_PLAYGAME;
					moveMap = true;
				}
			}
		}
		if (objects[i]->GetState() == objects[i]->STATE_DETROY)
		{
			objects.erase(objects.begin() + i);
		}
	}
	if (id == ID_ENTITY_MAP_PLAYGAME)
	{
		if (GetTickCount() - time >= TIME_ZOMBIE)
		{
			time = 0;
			createZombie(viewport);
		}
	}

	if (moveMap)
	{
		loadResources();
		createZombie(viewport);
		moveMap = false;
	}
}

void GameplayScreen::updateViewport(float dt)
{
	D3DXVECTOR2 pos_Simon = simon->getPosition();

	int widthframeSimon = simon->getWidth();

	D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};

	newPosViewport.x = simon->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
	newPosViewport.y = viewport->getY();

	newPosViewport.x = min(resourceManagement->getTiledMap(id)->getWidthWorld() - viewport->getWidth(), newPosViewport.x);
	newPosViewport.y = min(resourceManagement->getTiledMap(id)->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
	newPosViewport.x = max(0, newPosViewport.x);
	newPosViewport.y = max(0, newPosViewport.y);

	viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
}

void GameplayScreen::renderObject()
{
	resourceManagement->getTiledMap(id)->draw(viewport);
	menu_point->Draw();
	for (int i = 0; i < objects.size(); i++)
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
		zombie->SetPosition(D3DXVECTOR2(viewport->getX(), 295));
		objects.push_back(zombie);

		zombie = new Zombie();
		zombie->SetState(ZOMBIE_STATE_WALKING_LEFT);
		zombie->SetPosition(D3DXVECTOR2(viewport->getX() + viewport->getWidth() - i * 60, 295));
		objects.push_back(zombie);
	}
	if (time == 0)
	time = GetTickCount();
}

void GameplayScreen::getInfoFromObjectInfo(ObjectInfo *info, LPGAMEOBJECT object)
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
	delete castlewall;
	for (auto object : resourceManagement->getTiledMap(id)->getObjectInfo())
	{
		StaticObject* objectInit = nullptr;
		switch (resourceManagement->getStringToEntity()[object->get_ObjectId()])
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
			break;
		case ID_ENTITY_CASTLEVANIA_WALL:
			castlewall = new CastleWall();
			getInfoFromObjectInfo(object, castlewall);
			break;
		}
		if (objectInit)
		{
			getInfoFromObjectInfo(object, objectInit);
			objects.push_back(objectInit);
			objectInit = nullptr;
		}
	}

	if (id == ID_ENTITY_MAP_ENTRANCE)
	{
		simon->SetPosition(D3DXVECTOR2(1200, 0));
		objects.push_back(simon);
		objects.push_back(castlewall);
		menu_point->loadResource();
	}
	else if (id == ID_ENTITY_MAP_PLAYGAME)
	{
		simon->SetPosition(D3DXVECTOR2(0, 300));
		objects.push_back(simon);
	}
}

GameplayScreen::GameplayScreen()
{
	resourceManagement = ResourceManagement::GetInstance();

	id = ID_ENTITY_MAP_ENTRANCE;

	menu_point = new MenuPoint();

}
GameplayScreen::~GameplayScreen()
{
	delete simon;
}
