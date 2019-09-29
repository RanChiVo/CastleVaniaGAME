#include "SmallHeart.h"
#include "../ResourceManagement.h"
#include <math.h> 

constexpr float SMALL_HEART_GRAVITY = 0.0003f;
constexpr float SMALL_HEART_AMPLITUDE = 15;
constexpr float SMALL_HEART_DELTA = 0.05f;

SmallHeart::SmallHeart(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_TEX_SMALL_HEART;

	AddAnimation(SMALL_HEART_ANI);

	specifications = 1;
	state = SMALL_HEART_STATE_HIDE;
	originalLocation = x;
	currentAnimation = SMALL_HEART_ANI;
	delta = 0;
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (state == SMALL_HEART_STATE_SHOW)
	{
		if (GetTickCount() - liveTime > 4000)
		{
			state = STATE_DETROY;
			liveTime = 0;
		}
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != SMALL_HEART_STATE_HIDE)
			CalcPotentialCollisions(coObjects, coEvents);

		delta += SMALL_HEART_DELTA;
		if (specifications)
		{
			specifications = SMALL_HEART_AMPLITUDE * sin(delta);
			x = specifications + originalLocation;
		}
		
		vy += SMALL_HEART_GRAVITY;

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			float Dx = dx, Dy = dy;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			y += min_ty * dy + ny * 0.4f;
			if (ny != 0)
			{
				vx = 0;
				vy = 0;
				specifications = 0;
			}
			
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else if (state == SMALL_HEART_STATE_HIDE)
	{
		SetPosition(D3DXVECTOR2(0, 0));
	};
}

void SmallHeart::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
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

void SmallHeart::movement()
{
	
}

SmallHeart::~SmallHeart()
{
}
