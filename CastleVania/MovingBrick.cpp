#include "MovingBrick.h"

MovingBrick::MovingBrick(D3DXVECTOR2 pos, int maxDistance, int width, int height)
{
	id = ID_ENTITY_MOVING_BRICK;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	this->maxDistance = maxDistance;
	currentAnimation = MOVING_BRICK_ANI;
	nx = 1;
	positionXStart = pos.x;
	timeMoving = GetTickCount();
}

void MovingBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt);
	x += dx;
	y += dy;
	if (timeMoving > 0 && GetTickCount() - timeMoving > 1500)
	{
		timeMoving = GetTickCount();
		nx = -nx;
	}

	vx = nx * (maxDistance - positionXStart) / 1500;
}

void MovingBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void MovingBrick::Render(Viewport * viewport)
{
	D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
	animation_set->find(currentAnimation)->second->Render(position.x, position.y, Flip::normal);
}

MovingBrick::~MovingBrick()
{
}
