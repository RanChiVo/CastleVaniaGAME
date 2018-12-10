#include "SmallHeart.h"
#include "../ResourceManagement.h"

constexpr float SMALL_HEART_GRAVITY = 0.0006f;


SmallHeart::SmallHeart(D3DXVECTOR2 position)
{
	id = ID_TEX_SMALL_HEART;
	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_HEART)->Get("small_heart1")->getRect();
	int height = r.bottom - r.top;

	x = position.x;
	y = position.y;

	AddAnimation(HEART_ANI);

	state = SMALL_HEART_STATE_HIDE;
	currentAnimation = HEART_ANI;
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	if (state == SMALL_HEART_STATE_SHOW)
	{
		vy += SMALL_HEART_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != SMALL_HEART_STATE_HIDE)
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
	else return;
}

void SmallHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_SMALL_HEART)->Get("small_heart1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void SmallHeart::Render(Viewport * viewport)
{
	if (state == SMALL_HEART_STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		Flip flip = flip_horiz;

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	else return;
}

SmallHeart::~SmallHeart()
{
}
