#include "FireBomb.h"
#include "../ResourceManagement.h"

constexpr float FIRE_BOMB_GRAVITY = 0.0006f;

FireBomb::FireBomb(D3DXVECTOR2 position)
{
	id = ID_TEX_FIRE_BOMB;

	x = position.x;
	y = position.y;

	AddAnimation(FIRE_BOMB_ANI);

	state = FIRE_BOMB_STATE_HIDE;
	currentAnimation = FIRE_BOMB_ANI;
}

void FireBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	if (state == FIRE_BOMB_STATE_SHOW)
	{
		vy += FIRE_BOMB_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != FIRE_BOMB_STATE_HIDE)
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

void FireBomb::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_FIRE_BOMB)->Get("fire_bomb1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void FireBomb::Render(Viewport * viewport)
{
	if (state == FIRE_BOMB_STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		Flip flip = flip_horiz;

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
		//	RenderBoundingBox(viewport);
	}
	else return;
}

FireBomb::~FireBomb()
{
}
