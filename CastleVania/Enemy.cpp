#include "Enemy.h"
#include "../CastleVania/ResourceManagement.h"
#include "./GameObjects/WeaponReward.h"
#include "./GameObjects/Heart.h"
#include "./GameObjects/Dagger.h"
#include "./GameObjects/FireBomb.h"
#include "./GameObjects/Cross.h"
#include "./GameObjects/SmallHeart.h"
#include "./GameObjects/MiraculousBag.h"
#include "VampireBat.h"
#include "FishMan.h"
#include <cstdlib>
#include <ctime>

constexpr DWORD LIVE_TIME = 100;
constexpr DWORD STOP_WATCH_TIME = 4000;

DWORD Enemy::stopWatchStart = 0;

Enemy::Enemy()
{

}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (stopWatchStart > 0 && GetTickCount() - stopWatchStart > STOP_WATCH_TIME)
	{
		stopWatchStart = 0;
	}
	GameObject::Update(dt, coObjects);

	if (stopWatchStart!= 0)
	{
		dx = dy = 0;
	}

	if (state == STATE_EFFECT)
	{
		if (GetTickCount() - liveTime > LIVE_TIME)
		{
			DebugOut(L"liveTime:{%d}\n", liveTime);

			//rand() % (b – a + 1) + a.
			if (id == ID_ENTITY_VAMPIRE_BAT)
			{
				state = VampireBat::VAMPIRE_STATE_HIDDEN;
			}
			else if (id == ID_ENTITY_FISH_MAN)
			{
				state = FishMan::FISH_MAN_STATE_HIDDEN;
			}
			else state = STATE_DETROY;
			GameObject* item = nullptr;
			int idRandom = rand() % (20 - 5 + 1) + 5;

			if (idRandom < 5)
			{
				item = nullptr;
			}

			liveTime = 0;
			switch (idRandom)
			{
			case ID_ENTITY_WEAPON_REWARD:
				item = new WeaponReward(D3DXVECTOR2(this->getPosition().x, this->getPosition().y));
				break;
			case ID_ENTITY_HEART:
				item = new Heart(D3DXVECTOR2(this->getPosition().x, this->getPosition().y ));
				break;
			case ID_ENTITY_DAGGER:
				item = new Dagger(D3DXVECTOR2(this->getPosition().x, this->getPosition().y ));
				break;
			case ID_ENTITY_SMALL_HEART:
				item = new SmallHeart(D3DXVECTOR2(this->getPosition().x, this->getPosition().y ));
				break;
			case ID_ENTITY_FIRE_BOMB:
				item = new FireBomb(D3DXVECTOR2(this->getPosition().x, this->getPosition().y ));
				break;	
			case ID_ENTITY_RED_100_MIRACULOUS_BAG:
			case ID_ENTITY_BLUE_400_MIRACULOUS_BAG:
			case ID_ENTITY_WHITE_700_MIRACULOUS_BAG:
			case ID_ENTITY_BONUS_1000_MIRACULOUS_BAG:
				item = new MiraculousBag((EntityID)idRandom, (D3DXVECTOR2(this->getPosition().x, this->getPosition().y - 40)));
				break;
			}
			if (item)
				coObjects->push_back(item);
		}
	}
}

void Enemy::Render(Viewport * viewport)
{
	if (state == STATE_EFFECT)
	{
		AddAnimation(ANI_EFFECT);
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animations.find(ANI_EFFECT)->second->Render(position.x, position.y, flip);
	}
}

void Enemy::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void Enemy::setTimeRevival(DWORD timeRevival)
{
	this->timeRevival = timeRevival;
}

void Enemy::StopWatchStart()
{
	if (stopWatchStart == 0)
	{
		stopWatchStart = GetTickCount();
	}
}

DWORD Enemy::getTimeRevival(DWORD timeRevival)
{
	return timeRevival;
}

Enemy::~Enemy()
{
}
