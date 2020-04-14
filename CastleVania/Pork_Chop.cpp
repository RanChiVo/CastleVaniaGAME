#include "Pork_Chop.h"
#include "ResourceManagement.h"

constexpr float PORKCHOP_GRAVITY = 0.0006f;

Pork_Chop::Pork_Chop(D3DXVECTOR2 position)
{
	id = ID_ENTITY_PORK_CHOP;
	//AddAnimation(PORK_CHOP_ANI);
	currentAnimation = PORK_CHOP_ANI;
	state = STATE_SHOW;
	SetPosition(position);
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	liveTime = GetTickCount();
}

void Pork_Chop::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	if (state == STATE_SHOW)
	{
		vy += PORKCHOP_GRAVITY * dt;

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
			y += min_ty * dy;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		if (GetTickCount() - liveTime > 4000)
		{
			state = STATE_DETROY;
			liveTime = 0;
		}
	}
}

void Pork_Chop::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Pork_Chop::Render(Viewport * viewport)
{
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		animation_set->at(currentAnimation)->Render(position.x, position.y, Flip::normal);
		RenderBoundingBox(viewport);
	}
}

Pork_Chop::~Pork_Chop()
{
}
