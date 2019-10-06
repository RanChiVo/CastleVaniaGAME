#include "../ResourceManagement.h"
#include "WeaponReward.h"


constexpr float WEAPONREWARD_GRAVITY = 0.0006f;

WeaponReward::WeaponReward()
{
	id = ID_TEX_WEAPON_REWARD;
	LPANIMATION ani;
	AddAnimation(WEAPONREWARD_ANI);
	SetPosition(D3DXVECTOR2(0, 0));
	currentAnimation = WEAPONREWARD_ANI;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	liveTime = GetTickCount();
}

void WeaponReward::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == STATE_SHOW)
	{
		vy += WEAPONREWARD_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		
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
			y += min_ty * dy + ny * 0.1f;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		if (GetTickCount() - liveTime > 3000)
		{
			state = STATE_DETROY;
			liveTime = 0;
		}
	}
}

void WeaponReward::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void WeaponReward::Render(Viewport * viewport)
{
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	//	RenderBoundingBox(viewport);
	}
}

WeaponReward::~WeaponReward()
{
}
