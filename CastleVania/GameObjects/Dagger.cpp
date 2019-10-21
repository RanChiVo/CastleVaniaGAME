#include  "../Animations/Animations.h"
#include "../ResourceManagement.h"
#include "Dagger.h"

constexpr float KATANA_GRAVITY = 0.0006f;

Dagger::Dagger(D3DXVECTOR2 position)
{
	id = ID_ENTITY_DAGGER;
	SetPosition(position);
	AddAnimation(DAGGER_ANI);
	currentAnimation = DAGGER_ANI;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	liveTime = GetTickCount();
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	GameObject::Update(dt, coObjects);
	
	if (state == STATE_SHOW)
	{
		vy += KATANA_GRAVITY * dt;

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
			y += min_ty * dy + ny * 0.1f;
			if (ny != 0) vy = 0;
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		if (GetTickCount() - liveTime > 4000)
		{
			state = STATE_DETROY;
			liveTime = 0;
		}
	}
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x + width;
	top = y;
	right = left + width;
	bottom = y + height;
}

void Dagger::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	if (state == STATE_SHOW)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		Flip flip;
		if (nx == 1) flip = normal;
		else flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
}

Dagger::~Dagger()
{
}
