#include "Boomerang.h"
#include "../ResourceManagement.h"

constexpr float BOOMERANG_GRAVITY = 0.0006f;

Boomerang::Boomerang(D3DXVECTOR2 position)
{
	id = ID_ENTITY_WEAPON_REWARD;

	x = position.x;
	y = position.y;

	LPANIMATION ani;

	AddAnimation(WEAPONREWARD_ANI);

	state = BOOMERANG_STATE_HIDE;
	currentAnimation = WEAPONREWARD_ANI;
}

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	if (state == BOOMERANG_STATE_SHOW)
	{
		vy += BOOMERANG_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != BOOMERANG_STATE_HIDE)
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

void Boomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Boomerang::Render(Viewport * viewport)
{
}

Boomerang::~Boomerang()
{
}
