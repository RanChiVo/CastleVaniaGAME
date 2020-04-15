#include "WeaponReward.h"

constexpr float WEAPONREWARD_GRAVITY = 0.0006f;

WeaponReward::WeaponReward(D3DXVECTOR2 position)
{
	id = ID_ENTITY_WEAPON_REWARD;
	LPANIMATION ani;
	///AddAnimation(WEAPONREWARD_ANI);
	SetPosition(position);
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
			float Dx = dx, Dy = dy;
			float rdx = 0;
			float rdy = 0;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			for (int i = 0; i < coEvents.size(); i++)
			{
				switch (coEvents[i]->obj->getID())
				{
				case ID_ENTITY_FLOOR:
					if (ny < 0) vy = 0;
					Dy = min_ty * dy + ny * 0.4f;
					break;
				}
			}
			y += Dy;
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
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
		RenderBoundingBox(viewport);
	}
}

WeaponReward::~WeaponReward()
{
}
