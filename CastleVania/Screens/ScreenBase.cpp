#include "ScreenBase.h"
#include "../ResourceManagement.h"
#include "../CastleWall.h"
#include "../EntityID.h"
#include "../GameObjects/Floor.h"
#include "../Door.h"
#include "../Brick.h"
#include "../GameObjects/BurnBarrel.h"
#include "../VampireBat.h"
#include "../Enemy.h"
#include "../ResourceManagement.h"
#include "../GameObjects/Entrance.h"
#include "../Candle.h"
#include "../WallEntrance.h"
#include "../FishMan.h"
#include "../Panther.h"


ScreenBase::ScreenBase()
{
	menu_point = new MenuPoint();
}

void ScreenBase::update(DWORD deltatime)
{
	menu_point->update();

	ResourceManagement::GetInstance()->getTiledMap(IdScreen)->Update(deltatime, &objects);
}

void ScreenBase::loadResources()
{
	ResourceManagement::GetInstance()->loadResource(path);
	menu_point->loadResource();
	objects.clear();
	CastleWall* castleWall = nullptr;
	for (auto object : ResourceManagement::GetInstance()->getTiledMap(IdScreen)->getObjectInfo())
	{
		StaticObject* objectInit = nullptr;
		Enemy* objectEnemy = nullptr;
		int idObject = ResourceManagement::GetInstance()->getStringToEntity()[object->get_ObjectId()];
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
}

void ScreenBase::renderObject(Viewport * viewport)
{
	ResourceManagement::GetInstance()->getTiledMap(IdScreen)->draw(viewport);
	menu_point->Draw();
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render(viewport);
	}
}

void ScreenBase::getInfoFromObjectInfo(ObjectInfo::builder *info, LPGAMEOBJECT object)
{
	object->setName(info->get_name());
	object->SetPosition(info->get_postition());
	object->setHeight(info->get_height());
	object->setWidth(info->get_width());
	object->setIdHiddenItem(info->get_idHiddenItem());
	object->setEnemyName(info->get_enemyName());
}

ScreenBase::~ScreenBase()
{
}
