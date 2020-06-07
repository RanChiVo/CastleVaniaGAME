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
#include "DoubleShoot.h"

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
	else  if (name.compare("SmallBrick")==0 || name.compare("SmallBrick1") == 0)
	{
		currentAnimation = BRICK_ANI4;
	}
	else  if (name.compare("SmallBrickDarkBat") == 0)
	{
		currentAnimation = BRICK_ANI5;
	}
	else  if (name.compare("SmallBrickCrumbling") == 0)
	{
		currentAnimation = BRICK_ANI6;
	}
	isBroken = false;
}

void CBrick::Render(Viewport* viewport)
{
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
	RenderBoundingBox(viewport);
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
			item = new WeaponReward(D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_HEART:
			item = new Heart(D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_PORK_CHOP:
			item = new Pork_Chop(D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_AXE:
			item = new Axe(D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_DAGGER:
			item = new Dagger(D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_SMALL_HEART:
			item = new SmallHeart(D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_CROSS:
			item = new Cross(D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_FIRE_BOMB:
			item = new FireBomb(D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_RED_100_MIRACULOUS_BAG:
		case ID_ENTITY_BLUE_400_MIRACULOUS_BAG:
		case ID_ENTITY_WHITE_700_MIRACULOUS_BAG:
		case ID_ENTITY_BONUS_1000_MIRACULOUS_BAG:
			item = new MiraculousBag(idHiddenItem, D3DXVECTOR2(x, y - 5));
			break;
		case ID_ENTITY_DOUBLE_SHOOT:
			item = new DoubleShoot(D3DXVECTOR2(x,y-5));
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
	if (name.compare("SmallBrick") == 0)
	{
		l = x;
		t = y + 10;
		r = x + width;
		b = t + 10;
	}
}

CBrick::~CBrick()
{
}
