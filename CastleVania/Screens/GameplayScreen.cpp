#include "GameplayScreen.h"
#include "../WindowUtil.h"
#include "../Direct3DManager.h"
#include "../CastleWall.h"
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

	if (id == ID_TEX_MAP_ENTRANCE)
	{
		for (int i = 0; i < objects.size(); i++)
		{	
			objects[i]->Update(dt, &objects);
			if (objects[i]->GetState() == objects[i]->STATE_DETROY)
			{
				objects.erase(objects.begin() + i);
			}
			if (objects[i]->getID() == ID_TEX_SIMON)
			{
				if (objects[i]->getLevel() == 1)
				{
					id == ID_TEX_MAP_PLAYGAME;
				}
			}
		}
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

	if (id == ID_TEX_MAP_ENTRANCE)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Render(viewport);
		}
	}
}

void GameplayScreen::createZombie(Viewport* viewport)
{
	for (int i = 0; i < 3; i++)
	{
		Zombie* zombie = new Zombie();
		zombie->SetState(ZOMBIE_STATE_WALKING_RIGHT);
		zombie->SetPosition(D3DXVECTOR2(viewport->getX() + 60 * i, 325));
		objectslv2.push_back(zombie);

		zombie = new Zombie();
		zombie->SetPosition(D3DXVECTOR2(viewport->getX() + viewport->getWidth() - i * 60, 325));
		zombie->SetState(ZOMBIE_STATE_WALKING_LEFT);
		objectslv2.push_back(zombie);
	}
	timer_zombie = 0;
}

void GameplayScreen::getInfoFromObjectInfo(ObjectInfo *info, LPGAMEOBJECT object)
{
	object->setHeight(info->get_height());
	object->setWidth(info->get_width());
	object->setIdHiddenItem(info->get_idHiddenItem());
}

void GameplayScreen::loadResources()
{
	CastleWall* castlewall = new CastleWall();
	for (auto object : resourceManagement->getTiledMap(id)->getObjectInfo())
	{
		if (object->get_name() == "Floor")
		{
			Floor* floor = new Floor();
			floor->SetPosition(object->get_postition());
			getInfoFromObjectInfo(object, floor);
			objects.push_back(floor);
		}
		else if (object->get_name() == "CastleWall")
		{
				castlewall->SetPosition(object->get_postition());
			getInfoFromObjectInfo( object, castlewall);
		
		}
		else if (object->get_name() == "BurnBarrel")
		{
			BurnBarrel* burnbarrel = new BurnBarrel();
			getInfoFromObjectInfo(object, burnbarrel);
			burnbarrel->SetPosition(D3DXVECTOR2(object->get_postition().x, object->get_postition().y - object->get_height()));
			objects.push_back(burnbarrel);
		}
		else if (object->get_name() == "Entrance")
		{
			Entrance* entrance = new Entrance();
			getInfoFromObjectInfo( object, entrance);
			entrance->SetPosition(object->get_postition());
			objects.push_back(entrance);
		}
		else if (object->get_name() == "wall_frontof_entrance")
		{
			CBrick* Brick = new CBrick();
			getInfoFromObjectInfo(object, Brick);
			Brick->SetPosition(object->get_postition());
			objects.push_back(Brick);
		}
		else if (object->get_name() == "wall_behind_entrance")
		{
			WallEntrance* wallEntrance = new WallEntrance();
			getInfoFromObjectInfo( object, wallEntrance);
			wallEntrance->SetPosition(object->get_postition());
			objects.push_back(wallEntrance);
		}
	}
	simon = new Simon();
	simon->loadResource();
	simon->SetPosition(D3DXVECTOR2(0, 0));
	objects.push_back(simon);
	objects.push_back(castlewall);
	menu_point->loadResource();
}

GameplayScreen::GameplayScreen()
{
	resourceManagement = ResourceManagement::GetInstance();

	id = ID_TEX_MAP_ENTRANCE;
	
	menu_point = new MenuPoint();
}
GameplayScreen::~GameplayScreen()
{
	delete simon;
}
