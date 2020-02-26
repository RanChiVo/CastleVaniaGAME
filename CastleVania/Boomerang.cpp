#include "Boomerang.h"
#include "ResourceManagement.h"

constexpr float BOOMERANG_GRAVITY = 0.0006f;

Boomerang::Boomerang(D3DXVECTOR2 pos)
{
	id = ID_ENTITY_BOOMERANG;
	SetPosition(pos);
	AddAnimation(BOOMERANG_ITEM_ANI);
	currentAnimation = BOOMERANG_ITEM_ANI;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	liveTime = GetTickCount();
}

void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	vy += BOOMERANG_GRAVITY * dt;
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
				Dy = min_ty * dy + ny * 0.08f;
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

void Boomerang::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	Flip flip = normal;
	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
}

void Boomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}


Boomerang::~Boomerang()
{
}
