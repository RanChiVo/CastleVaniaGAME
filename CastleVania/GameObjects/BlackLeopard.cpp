#include "BlackLeopard.h"

constexpr int BLACKLEOPARD_GRAVITY = 0.0009f;
constexpr float BLACKLEOPARD_SPEED = 0.15f;


BlackLeopard::BlackLeopard()
{
	id = ID_TEX_BLACK_LEOPARD;
	AddAnimation(BLACK_LEOPARD_ANI_IDLE);
	AddAnimation(BLACK_LEOPARD_ANI_MOVE);

	state = BLACKLEOPARD_STATE_IDLE;
	currentAnimation = BLACK_LEOPARD_ANI_IDLE;
	isActive = false;
}

void BlackLeopard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	handle();

	vy += BLACKLEOPARD_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
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
			case ID_TEX_FLOOR:
				if (ny != 0) vy = 0;
				Dy = min_ty * dy + ny * 0.4f;
				break;
			}
		}
		x += Dx;
		y += Dy;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void BlackLeopard::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void BlackLeopard::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	animations.find(currentAnimation)->second->Render(position.x, position.y, Flip::normal);

	RenderBoundingBox(viewport);
}

void BlackLeopard::handle()
{
	switch (state)
	{
	case BLACKLEOPARD_STATE_IDLE:
		vx = 0;
		nx = 1;
		currentAnimation = BLACK_LEOPARD_ANI_IDLE;
		break;

	case BLACKLEOPARD_STATE_MOVE_RIGHT:
		vx = BLACKLEOPARD_SPEED;
		nx = 1;
		currentAnimation = BLACK_LEOPARD_ANI_MOVE;
		break;

	case BLACKLEOPARD_STATE_MOVE_LEFT:
		vx = -BLACKLEOPARD_SPEED;
		nx = -1;
		currentAnimation = BLACK_LEOPARD_ANI_MOVE;
		break;
	}
}

BlackLeopard::~BlackLeopard()
{
}
