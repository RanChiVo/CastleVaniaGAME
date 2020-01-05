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
#include "../ObjectGridCreation.h"

constexpr DWORD TIME_ZOMBIE = 10000;
constexpr float POSITION_ZOMBIE_Y = 344.0f;

void GameplayScreen::update(DWORD dt)
{
	ScreenBase::update(dt);
	updateViewport(dt);
	updateEnemy();
	//grid->update(dt, &objects);

}

void GameplayScreen::updateViewport(DWORD dt)
{
	if (viewport ->getState()== viewport->STATE_ACTION)
	{
		D3DXVECTOR2 pos_Simon = Simon::getInstance()->getPosition();
		int widthframeSimon = Simon::getInstance()->getWidth();
		D3DXVECTOR2 newPosViewport = D3DXVECTOR2{};
		newPosViewport.x = Simon::getInstance()->getPosition().x - viewport->getWidth() / 2 + widthframeSimon / 2;
		if (resourceManagement->getTiledMap(IdScreen)->getWidthWorld() - viewport->getX() == viewport->getWidth())
		{
			viewport->setStartViewPortX(newPosViewport.x);
			
			Simon::getInstance()->SetStateMoveEndMap(true);
		}
		newPosViewport.x = min(viewport->getEndViewportX() - viewport->getWidth(), newPosViewport.x);
		newPosViewport.y = min(resourceManagement->getTiledMap(IdScreen)->getHeightWorld() - viewport->getHeight(), newPosViewport.y);
		newPosViewport.x = max(viewport->getStartViewportX(), newPosViewport.x);
		newPosViewport.y = max(0, newPosViewport.y);
		viewport->setX(float(newPosViewport.x));
		viewport->SetPosition(float(newPosViewport.x), float(newPosViewport.y));
	}
	else return;
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

void GameplayScreen::loadResources()
{
	ScreenBase::loadResources();
	ObjectGridCreation* Addproperty = new ObjectGridCreation("TiledMap\\InsideCastle_map - Copy.tmx");
	/*Addproperty->divideOnjectToGrid(&objects, 2, 22);
	viewport->setEndViewPortX(resourceManagement->getTiledMap(IdScreen)->getWidthWorld());*/
	grid = new Grid(2, 22);
	grid->loadObjects(&objects);
}

void GameplayScreen::createZombie(Viewport* viewport)
{
	for (int i = 0; i < 3; i++)
	{
		if (randomEnemy == 1)
		{
			Zombie* zombie = new Zombie();
			zombie->SetState(ZOMBIE_STATE_WALKING_RIGHT);
			zombie->SetPosition(D3DXVECTOR2(viewport->getX() + i * 60, POSITION_ZOMBIE_Y));
			objects.push_back(zombie);
		}
		else
		{
			Zombie* zombie = new Zombie();
			zombie->SetState(ZOMBIE_STATE_WALKING_LEFT);
			zombie->SetPosition(D3DXVECTOR2(viewport->getX() + viewport->getWidth() - i * 60, POSITION_ZOMBIE_Y));
			objects.push_back(zombie);
		}
	}
	randomEnemy = -randomEnemy;
}

GameplayScreen::GameplayScreen()
{
	path = "ReadSprite.txt";
	IdScreen = ID_ENTITY_MAP_PLAYGAME;
}

GameplayScreen::~GameplayScreen()
{
}
