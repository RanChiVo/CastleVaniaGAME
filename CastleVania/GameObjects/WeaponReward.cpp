#include "../ResourceManagement.h"
#include "WeaponReward.h"


constexpr float WEAPONREWARD_GRAVITY = 0.0006f;

WeaponReward::WeaponReward()
{
}

WeaponReward::WeaponReward(D3DXVECTOR2 position)
{
	id = ID_TEX_WEAPON_REWARD;

	x = position.x;
	y = position.y;

	LPANIMATION ani;

	AddAnimation(WEAPONREWARD_ANI);

	state = WEAPONREWARD_STATE_HIDE;
	currentAnimation = WEAPONREWARD_ANI;
}

void WeaponReward::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == WEAPONREWARD_STATE_SHOW)
	{

		vy += WEAPONREWARD_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != WEAPONREWARD_STATE_HIDE)
			CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			if (ny != 0) vy = 0;
			y += min_ty * dy + ny * 0.4f;
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
	bottom = y + height;
}

void WeaponReward::Render(Viewport * viewport)
{
	if (state == WEAPONREWARD_STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else return;
}

WeaponReward::~WeaponReward()
{
}
