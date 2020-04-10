#include "SmallHeart.h"
#include "../ResourceManagement.h"
#include <math.h> 

constexpr float SMALL_HEART_GRAVITY = 0.0015f;
constexpr float SMALL_HEART_AMPLITUDE = 50;
constexpr float SMALL_HEART_DELTA = 0.055f;

SmallHeart::SmallHeart(D3DXVECTOR2 position)
{
	id = ID_ENTITY_SMALL_HEART;
	SetPosition(position);
	AddAnimation(SMALL_HEART_ANI);
	specifications = 1;
	originalLocation = x;
	currentAnimation = SMALL_HEART_ANI;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	delta = 0;
	liveTime = GetTickCount();
}

void SmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);

	if (state == STATE_SHOW)
	{
		if (GetTickCount() - liveTime > 4000)
		{
			state = STATE_DETROY;
			liveTime = 0;
		}
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		
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
			for (int i = 0; i < coEvents.size(); i++)
			{
				switch (coEvents[i]->obj->getID())
				{
				case ID_ENTITY_FLOOR:
					if (ny < 0) vy = 0;
					Dy = min_ty * dy;
					break;
				}
			}
			y += Dy;
			if (ny != 0)
			{
				vx = 0;
				vy = 0.1f;
				specifications = 0;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
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
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

		Flip flip = flip_horiz;

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
		RenderBoundingBox(viewport);
	}
}

void SmallHeart::movement()
{
	
}

SmallHeart::~SmallHeart()
{
}
