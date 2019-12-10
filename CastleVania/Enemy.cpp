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

constexpr int FIRE_LIVE_TIME = 300;

Enemy::Enemy()
{
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
		if (state == STATE_EFFECT)
		{
			if (GetTickCount() - liveTime > FIRE_LIVE_TIME)
			
				//rand() % (b – a + 1) + a.
				if (id == ID_ENTITY_VAMPIRE_BAT)
				{
					state = VampireBat::VAMPIRE_STATE_HIDDEN;
				}
				else if(id == ID_ENTITY_FISH_MAN)
				{
					state = FishMan::FISH_MAN_STATE_HIDDEN;
				}
				else state = STATE_DETROY;
				liveTime = 0;
				GameObject* item = nullptr;
				int idRandom = rand() % 13 + 8;
				switch (idRandom)
				{
				case ID_ENTITY_WEAPON_REWARD:
					item = new WeaponReward(this->getPosition());
					break;
				case ID_ENTITY_HEART:
					item = new Heart(this->getPosition());
					break;
				case ID_ENTITY_DAGGER:
					item = new Dagger(this->getPosition());
					break;
				case ID_ENTITY_SMALL_HEART:
					item = new SmallHeart(this->getPosition());
					break;
				case ID_ENTITY_FIRE_BOMB:
					item = new FireBomb(this->getPosition());
					break;
				case ID_ENTITY_RED_100_MIRACULOUS_BAG:
				case ID_ENTITY_BLUE_400_MIRACULOUS_BAG:
				case ID_ENTITY_WHITE_700_MIRACULOUS_BAG:
				case ID_ENTITY_BONUS_1000_MIRACULOUS_BAG:
					item = new MiraculousBag((EntityID)idRandom, this->getPosition());
					break;
				}
				if (item)
					coObjects->push_back(item);
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

Enemy::~Enemy()
{
}
