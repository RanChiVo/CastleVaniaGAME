#include "BallDarkBat.h"
#include  "ResourceManagement.h"

constexpr float BALL_DARK_BAT_GRAVITY = 0.0006f;
constexpr DWORD BALL_DARK_BAT_UNTOUCHED_TIME = 1000;


BallDarkBat::BallDarkBat(D3DXVECTOR2 pos)
{
	id = ID_ENTITY_BALL_DARK_BAT;
	AddAnimation(BALL_DARK_BALL_ANI);
	SetPosition(pos);
	state = STATE_SHOW;
	currentAnimation = BALL_DARK_BALL_ANI;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	liveTime = GetTickCount();
	startUntouched = GetTickCount();
}

void BallDarkBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == STATE_SHOW)
	{
		vy += BALL_DARK_BAT_GRAVITY * dt;

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
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			for (int i = 0; i < coEvents.size(); i++)
			{
				switch (coEvents[i]->obj->getID())
				{
				case ID_ENTITY_FLOOR:
					if (ny < 0) vy = 0;
					Dy = min_ty * dy + ny * 0.11f;
					if (startUntouched > 0 && GetTickCount() - startUntouched > BALL_DARK_BAT_UNTOUCHED_TIME)
					{
						isTouched = true;
						startUntouched = 0;
					}
					break;
				}
			}
			y += Dy;
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

		if (liveTime > 0 && GetTickCount() - liveTime > 20000)
		{
			state = STATE_DETROY;
			liveTime = 0;
		}
	}
}

void BallDarkBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void BallDarkBat::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip = normal;
	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	RenderBoundingBox(viewport);
}

BallDarkBat::~BallDarkBat()
{
}
