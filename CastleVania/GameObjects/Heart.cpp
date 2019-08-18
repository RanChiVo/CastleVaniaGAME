#include "Heart.h"
#include "../ResourceManagement.h"

constexpr float HEART_GRAVITY = 0.0006f;


Heart::Heart()
{
	id = ID_TEX_HEART;
	AddAnimation(HEART_ANI);

	state = HEART_STATE_HIDE;
	currentAnimation = HEART_ANI;
}

void Heart::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt);
	if (state == HEART_STATE_SHOW)
	{
		vy += HEART_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != HEART_STATE_HIDE)
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
	else if (state == HEART_STATE_HIDE)
	{
		SetPosition(D3DXVECTOR2(-100, -100));
	}
}

void Heart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Heart::Render(Viewport * viewport)
{
	if (state == HEART_STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		Flip flip = flip_horiz;

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else return;
	//	RenderBoundingBox(viewport);
}

Heart::~Heart()
{
}
