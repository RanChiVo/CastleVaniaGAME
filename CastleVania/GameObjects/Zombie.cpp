#include "Zombie.h"
#include "../ResourceManagement.h"

constexpr float ZOMBIE_WALKING_SPEED = 0.12f;
constexpr float ZOMBIE_GRAVITY = 0.0009f;

Zombie::Zombie()
{
	AddAnimation(ZOMBIE_ANI_WALKING);
	SetPosition(D3DXVECTOR2(50.0f, 0));

	SetState(ZOMBIE_STATE_WALKING);
	currentAnimation = ZOMBIE_ANI_WALKING;
}

void Zombie::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
	case ZOMBIE_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	case ZOMBIE_STATE_WALKING:
		vx = -ZOMBIE_WALKING_SPEED;
		break;
	}
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	RECT r = ResourceManagement::GetInstance()->getSprite(ID_TEX_ZOMBIE)->Get("zombie_walking1")->getRect();
	int height = r.bottom - r.top;
	int width = r.right - r.left;
	right = x + width;
	bottom = y + height;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
	
	vy += ZOMBIE_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != ZOMBIE_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
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
				Dy = min_ty * dy + ny * 0.4f;
				break;
			}
		}
		x += Dx;
		y += Dy;
	}
	if (vx < 0 && x < 50) {
		x = 50; vx = -vx;
		nx = -1;
	}

	if (vx > 0 && x > 2500) {
		x = 1000; vx = -vx;
		nx = 1;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Zombie::Render(Viewport* viewport)
{

	int ani = ZOMBIE_ANI_WALKING;

	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));

	Flip flip = flip_horiz;

	if (nx == 1) flip = normal;
	else flip = flip_horiz;

	animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	//	RenderBoundingBox(viewport);
}

Zombie::~Zombie()
{
}
