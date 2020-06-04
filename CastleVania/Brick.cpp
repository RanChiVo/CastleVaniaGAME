#include "Brick.h"
#include "Animations/Animations.h"
#include "./GameObjects/WeaponReward.h"
#include "./GameObjects/Heart.h"
#include "./GameObjects/Dagger.h"
#include "./GameObjects/SmallHeart.h"
#include "./GameObjects/Cross.h"
#include "./GameObjects/FireBomb.h"
#include "./GameObjects/MiraculousBag.h"
#include "./Axe.h"
#include "./Pork_Chop.h"
#include "BrickBrokenEffect.h"

CBrick::CBrick(std::string name, D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_BRICK;
	state = STATE_SHOW;

	SetPosition(pos);

	this->height = height;

	this->width = width;

	this->name = name;

	if (name.compare("BigSitdownBrick")==0)
	{
		currentAnimation = BRICK_ANI2;
	}
	else  if (name.compare("BigStandBrick")==0)
	{
		currentAnimation = BRICK_ANI1;
	}
	else  if (name.compare("TunelBrick")==0)
	{
		currentAnimation = BRICK_ANI3;
	}
	else  if (name.compare("SmallBrick")==0)
	{
		currentAnimation = BRICK_ANI4;
	}
	else  if (name.compare("SmallBrickDarkBat") == 0)
	{
		currentAnimation = BRICK_ANI5;
	}
	isBroken = false;
}

void CBrick::Render(Viewport* viewport)
{
	RenderBoundingBox(viewport);

	if (name.compare("EdgeBrick")==0)
	{
		return;
	}
	if (state == STATE_SHOW )
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = normal;
		animation_set->at(currentAnimation)->Render(position.x, position.y, flip);
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	if (!isBroken && state == STATE_EFFECT)
	{
		state = STATE_DETROY;
		GameObject* item = nullptr;
		idHiddenItem = Utils::getInstance()->getStringToEntityID()[getIdHiddenItem()];
		switch (idHiddenItem)
		{
		case ID_ENTITY_WEAPON_REWARD:
			item = new WeaponReward(this->getPosition());
			break;
		case ID_ENTITY_HEART:
			item = new Heart(this->getPosition());
			break;
		case ID_ENTITY_PORK_CHOP:
			item = new Pork_Chop(this->getPosition());
			break;
		case ID_ENTITY_AXE:
			item = new Axe(this->getPosition());
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
		}
		if (item)
			coObjects->push_back(item);
		BrickBrokenEffect* effect = new BrickBrokenEffect(getPosition());
		coObjects->push_back(effect);
	}
}

void CBrick::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
	if (currentAnimation == BRICK_ANI4)
	{
		l = x;
		t = y + 8;
		r = x + width;
		b = t + height- 10;
	}
}

CBrick::~CBrick()
{
}
