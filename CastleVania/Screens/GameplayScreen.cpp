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
	vector< LPGAMEOBJECT> staticObjects;

	if (id == ID_TEX_MAP_ENTRANCE)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			staticObjects.push_back(objects[i]);
		}

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &staticObjects);

			if (objects[i]->getID() == ID_TEX_SIMON)
			{
				if (objects[i]->IsChangeLevel())
				{
					id = ID_TEX_MAP_PLAYGAME;
				}
			}
		}
	}
	else
	{
		staticObjects.clear();

	/*	if (isActive)
		{
			if (timer_zombie >= TIME_ZOMBIE)
			{
				createZombie(viewport);
			}

		}
*/
		for (int i = 0; i < objectslv2.size(); i++)
		{
			staticObjects.push_back(objectslv2[i]);
		}

		for (int i = 0; i < objectslv2.size(); i++)
		{
			objectslv2[i]->Update(dt, &staticObjects);
			if (objectslv2[i]->getID() == ID_TEX_SIMON)
			{
				if (objectslv2[i]->IsCollision())
				{
					isActive = true;
					//timer_zombie += dt;
				}
				else
				{
					isActive = false;
				}

			}
		}

		/*for (int i = 0; i < objectslv2.size(); i++)
		{
			if (objectslv2[i]->getID() == ID_TEX_ZOMBIE)
			{
				float l, t, r, b;
				objectslv2[i]->GetBoundingBox(l, t, r, b);
				RECT rect1 = RECT{ int(l), int(t), int(r), int(b) };
				int nx = objectslv2[i]->GetDirection();

				if (nx == -1 && (rect1.right < viewport->getX()) || ((nx == 1) && (rect1.left > (viewport->getX() + viewport->getWidth()))))
				{
					objectslv2.erase(objectslv2.begin() + i);
				}
			}
		}
		*/
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
	else
	{
		objects.clear();
		for (int i = 0; i < objectslv2.size(); i++)
		{
			objectslv2[i]->Render(viewport);
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
	object->setName(info->get_name());
	object->setIdHiddenItem(info->get_idHiddenItem());
}

void GameplayScreen::loadResources()
{


	for (auto object : resourceManagement->getTiledMap(id)->getObjectInfo())
	{
		if (object->get_name() == "floor")
		{
			Floor* floor = new Floor();
			floor->SetPosition(object->get_postition());
			getInfoFromObjectInfo(object, floor);
			objects.push_back(floor);
		}
		else if (object->get_name() == "CastleWall")
		{
			CastleWall* castlewall = new CastleWall();
			castlewall->SetPosition(object->get_postition());
			getInfoFromObjectInfo( object, castlewall);
			objects.push_back(castlewall);
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
		else if (object->get_name() == "heart")
		{
			Heart* heart = new Heart();
			getInfoFromObjectInfo(object, heart);
			objects.push_back(heart);
		}
		else if (object->get_name() == "weapon_reward")
		{
			WeaponReward* weaponReward = new WeaponReward(object->get_postition());
			getInfoFromObjectInfo(object, weaponReward);
			objects.push_back(weaponReward);
		}
		else if (object->get_name() == "katana")
		{
			Katana* katana = new Katana(object->get_postition());
			getInfoFromObjectInfo( object, katana);
			objects.push_back(katana);
		}
	
	}
	KatanaWeapon * katanaWeapon = new KatanaWeapon();
	objects.push_back(katanaWeapon);

	for (auto object : resourceManagement->getTiledMap(ID_TEX_MAP_PLAYGAME)->getObjectInfo())
	{
		if (object->get_name() == "floor")
		{
			Floor* floor = new Floor();
			floor->SetPosition(D3DXVECTOR2(object->get_postition().x, object->get_postition().y));
			getInfoFromObjectInfo(object, floor);
			objectslv2.push_back(floor);
		}
		else if (object->get_name() == "Candle")
		{
			Candle* candle = new Candle();
			getInfoFromObjectInfo(object, candle);
			candle->SetPosition(D3DXVECTOR2(object->get_postition().x, object->get_postition().y - object->get_height()));
			objectslv2.push_back(candle);
		}
		
		else if (object->get_name() == "collisionStair")
		{
			CollisionStair* collisionStair = new CollisionStair(object->get_postition());
			getInfoFromObjectInfo( object, collisionStair);
			collisionStair->SetPosition(object->get_postition());
			objectslv2.push_back(collisionStair);

		}
		else if (object->get_name() == "front_of_wall")
		{
			CBrick* Brick = new CBrick();
			getInfoFromObjectInfo(object, Brick);
			Brick->SetPosition(object->get_postition());
			objectslv2.push_back(Brick);
		}
		else if (object->get_name() == "behind_wall")
		{
			WallEntrance* wallEntrance = new WallEntrance();
			getInfoFromObjectInfo(object, wallEntrance);
			wallEntrance->SetPosition(object->get_postition());
			objectslv2.push_back(wallEntrance);
		}
		else if (object->get_name() == "heart")
		{
			Heart* heart = new Heart();
			getInfoFromObjectInfo(object, heart);
			objectslv2.push_back(heart);
		}
		else if (object->get_name() == "small_heart")
		{
			SmallHeart* small_heart = new SmallHeart(object->get_postition());
			getInfoFromObjectInfo( object, small_heart);
			objectslv2.push_back(small_heart);
		}
		else if (object->get_name() == "cross")
		{
			Cross* cross = new Cross(object->get_postition());
			getInfoFromObjectInfo( object, cross);
			objectslv2.push_back(cross);
		}
		else if (object->get_name() == "fire_bomb")
		{
			FireBomb* fire_bomb = new FireBomb();
			getInfoFromObjectInfo( object, fire_bomb);
			fire_bomb->SetPosition(object->get_postition());
			objectslv2.push_back(fire_bomb);
		}
		else if (object->get_name() == "money_bag")
		{
			MiraculousBag* miraculousBag = new MiraculousBag();
			getInfoFromObjectInfo(object, miraculousBag);
			objectslv2.push_back(miraculousBag);
		}
	/*	else if (object->get_name() == "zombie_right")
		{
			Zombie* zombie = new Zombie();
			getInfoFromObjectInfo(object, zombie);
			zombie->SetPosition(object->get_postition());
			zombie->SetState(ZOMBIE_STATE_WALKING_RIGHT);
			objectslv2.push_back(zombie);
		}*/
		/*else if (object->get_name() == "zombie_left")
		{
			Zombie* zombie = new Zombie();
			getInfoFromObjectInfo(object, zombie);
			zombie->SetPosition(object->get_postition());
			zombie->SetState(ZOMBIE_STATE_WALKING_LEFT);
			objectslv2.push_back(zombie);
		}*/
		else if (object->get_name() == "areaZombie")
		{
			AreaZombie* area_zombie = new AreaZombie();
			getInfoFromObjectInfo(object, area_zombie);
			area_zombie->SetPosition(object->get_postition());
			objectslv2.push_back(area_zombie);
		}
		else if (object->get_name() == "black_leopard")
		{
			BlackLeopard* black_leopard = new BlackLeopard();
			getInfoFromObjectInfo(object, black_leopard);
			black_leopard->SetPosition(D3DXVECTOR2(object->get_postition().x, object->get_postition().y - object->get_height()));
			objectslv2.push_back(black_leopard);
		}

	}

	simon->loadResource();
	objects.push_back(simon);
	objectslv2.push_back(simon);

}

GameplayScreen::GameplayScreen()
{
	directInput = DirectInput::getInstance();

	simon = new Simon();

	resourceManagement = ResourceManagement::GetInstance();

	id = ID_TEX_MAP_ENTRANCE;
	
	menu_point = new MenuPoint();
}
GameplayScreen::~GameplayScreen()
{
	delete simon;
}
