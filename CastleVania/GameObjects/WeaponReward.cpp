#include "../ResourceManagement.h"
#include "WeaponReward.h"

WeaponReward::WeaponReward()
{
}

WeaponReward::WeaponReward(D3DXVECTOR2 position)
{
	id = ID_TEX_WEAPON_REWARD;

	x = position.x;
	y = position.y;

	LPANIMATION ani;

	ani = new Animation(40);
	ani->Add("weapon_reward1");
	Animations::GetInstance()->Add(WEAPONREWARD_ANI_HIDE, ani);

	ani = new Animation(40);
	ani->Add("Effect1");
	ani->Add("Effect2");
	ani->Add("Effect3");
	ani->Add("Effect4");
	ani->Add("weapon_reward1");

	Animations::GetInstance()->Add(WEAPONREWARD_ANI_SHOW, ani);

	AddAnimation(WEAPONREWARD_ANI_HIDE);
	AddAnimation(WEAPONREWARD_ANI_SHOW);

	state = WEAPONREWARD_STATE_HIDE;
	currentAnimation = WEAPONREWARD_ANI_HIDE;
}

void WeaponReward::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	std::vector<LPGAMEOBJECT> brickList;
	for (int i = 11; i < coObjects->size() - 2; i++)
	{
		brickList.push_back(coObjects->at(i));
	}

	if (state == WEAPONREWARD_STATE_HIDE)
	{
		currentAnimation = WEAPONREWARD_ANI_HIDE;
	}
	else if (state == WEAPONREWARD_STATE_SHOW)
	{
		currentAnimation = WEAPONREWARD_ANI_SHOW;

		if (animations.find(currentAnimation)->second->getCurrentFrame() == 4)

			animations.find(currentAnimation)->second->SetFinish1(true);

		vy += WEAPONREWARD_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != WEAPONREWARD_STATE_HIDE)
			CalcPotentialCollisions(&brickList, coEvents);

		if (coEvents.size() == 0)
		{
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			y += min_ty * dy + ny * 0.4f;
			if (ny != 0) vy = 0;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void WeaponReward::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_WEAPON_REWARD)->Get("weapon_reward1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height- 10 ;
}

void WeaponReward::Render(Viewport * viewport)
{
	D3DXVECTOR2 pos = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	animations.find(currentAnimation)->second->Render(position.x, position.y);
}

WeaponReward::~WeaponReward()
{
}
