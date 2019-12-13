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
	path = "ReadSprite.txt";
	IdScreen = ID_ENTITY_MAP_PLAYGAME;
	resourceManagement = ResourceManagement::GetInstance();
}

void GameplayScreen::loadResources()
{
	ScreenBase::loadResources();
}

void GameplayScreen::update(DWORD dt)
{
	ScreenBase::update(dt);

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
}

void GameplayScreen::renderObject(Viewport * viewport)
{
	ScreenBase::renderObject(viewport);
}

void GameplayScreen::updateViewport(DWORD dt)
{
	if (viewport->getState() == viewport->STATE_ACTION)
	{
		D3DXVECTOR2 pos_Simon = Simon::getInstance()->getPosition();
		int widthframeSimon = Simon::getInstance()->getWidth();
		D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};
		newPosViewport.x = Simon::getInstance()->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
		newPosViewport.x = min(resourceManagement->getTiledMap(IdScreen)->getWidthWorld()  - viewport->getWidth(), newPosViewport.x);
		newPosViewport.y = min(resourceManagement->getTiledMap(IdScreen)->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
		newPosViewport.x = max(0, newPosViewport.x);
		newPosViewport.y = max(0, newPosViewport.y);
		viewport->setX(float(newPosViewport.x));
		viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
	}
	else return;
}

void GameplayScreen::updateMap()
{
	updateEnemy();
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

GameplayScreen::GameplayScreen()
{
}

GameplayScreen::~GameplayScreen()
{
}
