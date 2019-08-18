
#include "Zombie.h"
#include "../ResourceManagement.h"

constexpr float ZOMBIE_WALKING_SPEED = 0.08f;
constexpr float ZOMBIE_GRAVITY = 0.0009f;

Zombie::Zombie()
{
	id = ID_TEX_ZOMBIE;

	AddAnimation(ZOMBIE_ANI_WALKING);
	currentAnimation = ZOMBIE_ANI_WALKING;
}

void Zombie::handleState()
{
	switch (state)
	{
	case ZOMBIE_STATE_DIE:
		vx = 0;
		break;
	case ZOMBIE_STATE_WALKING_RIGHT:
		nx = 1;
		vx = -ZOMBIE_WALKING_SPEED;
		currentAnimation = ZOMBIE_ANI_WALKING;
		break;
	case ZOMBIE_STATE_WALKING_LEFT:
		nx = -1;
		vx = ZOMBIE_WALKING_SPEED;
		currentAnimation = ZOMBIE_ANI_WALKING;
		break;
	}
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);

	handleState();

	vy += ZOMBIE_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ZOMBIE_STATE_DIE)
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


	if (state == ZOMBIE_STATE_DIE)
	{
		SetPosition(D3DXVECTOR2(-100, -100));
	}
}

void Zombie::Render(Viewport* viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	if (state != ZOMBIE_STATE_DIE)
	{
		int ani = ZOMBIE_ANI_WALKING;

		Flip flip = flip_horiz;

		if (nx == 1) flip = normal;
		else flip = flip_horiz;

		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
		RenderBoundingBox(viewport);
	}
	else return;
}

Zombie::~Zombie()
{
}
