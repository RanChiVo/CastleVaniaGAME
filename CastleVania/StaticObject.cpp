#include "StaticObject.h"
#include "./GameObjects/WeaponReward.h"
#include "./GameObjects/Heart.h"
#include "./GameObjects/Dagger.h"
#include "./GameObjects/SmallHeart.h"
#include "./GameObjects/Cross.h"
#include "./GameObjects/FireBomb.h"
#include "./GameObjects/MiraculousBag.h"
#include "./GameObjects/StopWatch.h"
#include "./Axe.h"
#include "./InvisibilityPotion.h"
#include "./Boomerang.h"
#include "./DoubleShoot.h"
#include "./Utils.h"

constexpr int FIRE_LIVE_TIME = 200;

StaticObject::StaticObject()
{
}

void StaticObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	if (state == STATE_EFFECT)
	{
		if (GetTickCount() - liveTime > FIRE_LIVE_TIME)
		{
			state = STATE_DETROY;
			liveTime = 0;
			GameObject* item = nullptr;
			idHiddenItem = Utils::getInstance()->getStringToEntityID()[getIdHiddenItem()];
			switch (idHiddenItem)
			{
			case ID_ENTITY_STOP_WATCH:
				item = new StopWatch(this->getPosition());
				break;
			case ID_ENTITY_WEAPON_REWARD:
				item = new WeaponReward(this->getPosition());
				break;
			case ID_ENTITY_HEART:
				item = new Heart(this->getPosition());
				break;
			case ID_ENTITY_INVISIBILITY_POTION:
				item = new InvisibilityPotion(this->getPosition());
				break;
			case ID_ENTITY_AXE:
				item = new Axe(this->getPosition());
				break;
			case ID_ENTITY_BOOMERANG:
				item = new Boomerang(this->getPosition());
				break;
			case ID_ENTITY_DAGGER:
				item = new Dagger(this->getPosition());
				break;
			case ID_ENTITY_SMALL_HEART:
				item = new SmallHeart(this->getPosition());
				break;
			case ID_ENTITY_CROSS:
				item = new Cross(this->getPosition());
				break;
			case ID_ENTITY_FIRE_BOMB:
				item = new FireBomb(this->getPosition());
				break;
			case ID_ENTITY_RED_100_MIRACULOUS_BAG:
			case ID_ENTITY_BLUE_400_MIRACULOUS_BAG:
			case ID_ENTITY_WHITE_700_MIRACULOUS_BAG:
			case ID_ENTITY_BONUS_1000_MIRACULOUS_BAG:
				item = new MiraculousBag(idHiddenItem, this->getPosition());
				break;
			case ID_ENTITY_DOUBLE_SHOOT:
				item = new DoubleShoot(this->getPosition());
				break;
			}
			if(item)
			coObjects->push_back(item);
		}
	}
}

void StaticObject::Render(Viewport * viewport)
{
	if (state == STATE_EFFECT)
	{
		AnimationSets * animation_sets = AnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(ID_ENTITY_EFFECT);
		SetAnimationSet(ani_set);
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animation_set->at(ANI_EFFECT)->Render(position.x, position.y, flip);
	}
}

StaticObject::~StaticObject()
{
}
