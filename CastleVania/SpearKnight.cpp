#include "SpearKnight.h"

constexpr float SPEAR_KNIGHT_MIN_DISTANCE = 32;
constexpr float SPEAR_KNIGHT_GRAVITY = 0.0009f;

SpearKnight::SpearKnight(D3DXVECTOR2 pos, int maxDistance, int height, int width )
{
	id = ID_ENTITY_SPEAR_KNIGHT;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	this->maxDistance = maxDistance;
	currentAnimation = SPEAR_KNIGHT_ANI_WALKING;
	nx = 1;
	positionXStart = pos.x;
	vx = 0.1f;
	timeMoving = GetTickCount();
}

void SpearKnight::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	vy += SPEAR_KNIGHT_GRAVITY * dt;
	vx = nx * vx;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT> staticObject;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->getID() == ID_ENTITY_FLOOR ||
			coObjects->at(i)->getID() == ID_ENTITY_WALL)
			staticObject.push_back(coObjects->at(i));
	}

	CalcPotentialCollisions(&staticObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
		float Dx = dx, Dy = dy;
		float rdx = 0;
		float rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		y += min_ty * dy;
		if (ny != 0) vy = 0;
	}

	if (timeMoving > 0 && GetTickCount() - timeMoving > 1000)
	{
		timeMoving = GetTickCount();
		nx = -nx;
	}

	int activateAreaX = (maxDistance - positionXStart)*2;
	int randomPositionX = rand() % activateAreaX + positionXStart;
	vx = nx * (randomPositionX - x)/ 1000;
}

void SpearKnight::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void SpearKnight::Render(Viewport * viewport)
{
	if (state != STATE_EFFECT)
	{
		D3DXVECTOR2 position = viewport->WorldToScreen(D3DXVECTOR2(x, y));
		RenderBoundingBox(viewport);
		Flip flip;
		if (nx == 1) flip = normal;
		else flip = flip_horiz;
		animation_set->find(currentAnimation)->second->Render(position.x, position.y, flip);
	}
	Enemy::Render(viewport);
}

SpearKnight::~SpearKnight()
{
}
