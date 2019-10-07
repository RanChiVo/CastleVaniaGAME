#include "StaticObject.h"
#include "./GameObjects/WeaponReward.h"
#include "./GameObjects/Heart.h"
#include "./GameObjects/Dagger.h"
#include "./GameObjects/SmallHeart.h"
#include "./GameObjects/Cross.h"
#include "./GameObjects/FireBomb.h"

constexpr int FIRE_LIVE_TIME = 300;

StaticObject::StaticObject()
{
}

void StaticObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	if (state == STATE_FIRE)
	{
		if (GetTickCount() - liveTime > FIRE_LIVE_TIME)
		{
			state = STATE_DETROY;
			liveTime = 0;

			if (this->getIdHiddenItem() == "weapon_reward")
			{
				WeaponReward* weaponReward = new WeaponReward();
				weaponReward->SetPosition(this->getPosition());
				coObjects->push_back(weaponReward);
			}
			else if (this->getIdHiddenItem() == "heart")
			{
				Heart* heart = new Heart();
				heart->SetPosition(this->getPosition());
				coObjects->push_back(heart);
			}
			else if (this->getIdHiddenItem() == "dagger")
			{
				Dagger* dagger = new Dagger();
				dagger->SetPosition(this->getPosition());
				coObjects->push_back(dagger);
			}
			else if (this->getIdHiddenItem() == "small_heart")
			{
				SmallHeart* smallHeart = new SmallHeart(this->getPosition());
				coObjects->push_back(smallHeart);
			}
			else if (this->getIdHiddenItem() == "cross")
			{
				Cross* cross = new Cross(this->getPosition());
				coObjects->push_back(cross);
			}
			else if (this->getIdHiddenItem() == "fire_bomb")
			{
				FireBomb* fire_bomb = new FireBomb();
				fire_bomb->SetPosition(this->getPosition());
				coObjects->push_back(fire_bomb);
			}
		}
	}
}

void StaticObject::Render(Viewport * viewport)
{
	if (state == STATE_FIRE)
	{
		AddAnimation(ANI_EFFECT);
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animations.find(ANI_EFFECT)->second->Render(position.x, position.y, flip);
	}
}

StaticObject::~StaticObject()
{
}
