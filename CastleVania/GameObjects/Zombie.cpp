#include "Zombie.h"
#include "../ResourceManagement.h"

constexpr float ZOMBIE_WALKING_SPEED = 0.05f;
constexpr float ZOMBIE_GRAVITY = 0.0009f;

Zombie::Zombie()
{
	id = ID_ENTITY_ZOMBIE;
	state = STATE_SHOW;
	width = Textures::GetInstance()->GetSizeObject(id).first;
	height = Textures::GetInstance()->GetSizeObject(id).second;
	AddAnimation(ZOMBIE_ANI_WALKING);
	currentAnimation = ZOMBIE_ANI_WALKING;
}

void Zombie::handleState()
{
	switch (state)
	{
	case ZOMBIE_STATE_WALKING_RIGHT:
		nx = 1;
		vx = ZOMBIE_WALKING_SPEED;
		currentAnimation = ZOMBIE_ANI_WALKING;
		break;
	case ZOMBIE_STATE_WALKING_LEFT:
		nx = -1;
		vx = -ZOMBIE_WALKING_SPEED;
		currentAnimation = ZOMBIE_ANI_WALKING;
		break;
	case STATE_EFFECT:
		vx = 0;
	}
}

bool Zombie::checkInsideViewPort(Viewport * viewport, D3DXVECTOR2 position)
{
	if ((position.x + width) < viewport->getX() ||
		position.x > (viewport->getX() + viewport->getWidth()))
	{
		return false;
	}
	return true;
}

void Zombie::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);

	handleState();

	vy += ZOMBIE_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != STATE_EFFECT)
		CalcPotentialCollisions(coObjects, coEvents);

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
				if (ny != 0) vy = 0;
				Dy = min_ty * dy + ny * 0.008f;
				break;
			case ID_ENTITY_WALL_ENTRANCE:
				if (coEvents[i]->obj->getName().compare("Wall") == 0)
				{
					SetState(STATE_DETROY);
				}
				break;
			}
		}
		x += Dx;
		y += Dy;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Zombie::Render(Viewport* viewport)
{
	if (state!= STATE_EFFECT)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		RenderBoundingBox(viewport);
		Flip flip;
		if (nx == -1) flip = normal;
		else flip = flip_horiz;
		animations.find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	
	if (!GameObject::checkInsideViewPort(viewport))
	{
		state = STATE_DETROY;
	}
	Enemy::Render(viewport);
}

Zombie::~Zombie()
{
}
