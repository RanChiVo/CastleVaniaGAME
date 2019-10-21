#include "MiraculousBag.h"
#include "../ResourceManagement.h"

constexpr float MIRACULOUSBAG_GRAVITY = 0.0006f;


MiraculousBag::MiraculousBag()
{
	id = ID_ENTITY_MIRACULOUS_BAG;

	AddAnimation(MIRACULOUSBAG_ANI);

	state = MIRACULOUSBAG_STATE_HIDE;
	currentAnimation = MIRACULOUSBAG_ANI;
}

void MiraculousBag::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == MIRACULOUSBAG_STATE_SHOW)
	{

		vy += MIRACULOUSBAG_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		if (state != MIRACULOUSBAG_STATE_HIDE)
			CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			y += min_ty * dy + ny * 0.4f;
			if (ny != 0) vy = 0;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else if (state == MIRACULOUSBAG_STATE_HIDE)
	{
		SetPosition(D3DXVECTOR2(-100, -100));
	}
}

void MiraculousBag::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void MiraculousBag::Render(Viewport * viewport)
{
	if (state == MIRACULOUSBAG_STATE_SHOW)
	{
		animations.find(currentAnimation)->second->SetLoop(true);
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	//	RenderBoundingBox(viewport);
	}
	else return;
}

MiraculousBag::~MiraculousBag()
{
}
