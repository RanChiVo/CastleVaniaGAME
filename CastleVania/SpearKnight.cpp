#include "SpearKnight.h"

constexpr float SPEAR_KNIGHT_MIN_DISTANCE = 32;
constexpr float SPEAR_KNIGHT_GRAVITY = 0.0009f;
constexpr float SPEAR_KNIGHT_SPEED_X = 0.13f;


SpearKnight::SpearKnight(D3DXVECTOR2 pos, int maxDistance, int height, int width )
{
	id = ID_ENTITY_SPEAR_KNIGHT;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	this->maxDistance = maxDistance;
	currentAnimation = SPEAR_KNIGHT_ANI_WALKING;
	nx = 1;
	vx = SPEAR_KNIGHT_SPEED_X;
	positionXStart = pos.x;
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
		y += min_ty * dy + ny*0.11f;
		if (ny != 0) vy = 0;
	}

	if (x > maxDistance )
	{
		nx = -1;
		vx = -SPEAR_KNIGHT_SPEED_X;
	}
	else if (x < positionXStart)
	{
		nx = 1;
		vx = SPEAR_KNIGHT_SPEED_X;
	}
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
