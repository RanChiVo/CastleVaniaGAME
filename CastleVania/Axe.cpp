#include "Axe.h"
#include "../CastleVania/ResourceManagement.h"
constexpr float AXE_GRAVITY = 0.0006f;

Axe::Axe(D3DXVECTOR2 position)
{
	id = ID_ENTITY_AXE;
	SetPosition(position);
	AddAnimation(AXE_ANI_ITEM);
	currentAnimation = AXE_ANI_ITEM;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	liveTime = GetTickCount();
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += AXE_GRAVITY * dt;
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
				Dy = min_ty * dy + ny * 0.1f;
				break;
			}
		}
		y += Dy;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (GetTickCount() - liveTime > 4000)
	{
		state = STATE_DETROY;
		liveTime = 0;
	}
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Axe::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip = normal;
	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
}

Axe::~Axe()
{
}
