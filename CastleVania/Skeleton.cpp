#include "Skeleton.h"

constexpr float SKELETON_GRAVITY = 0.0015f;


Skeleton::Skeleton(D3DXVECTOR2 pos, int height, int width, float maxDistance)
{
	id = ID_ENTITY_FLEAMEN;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	//SetState(FLEAMEN_STATE_PREPAIR_ATTACK);
}

void Skeleton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	vy += SKELETON_GRAVITY * dt;
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

}

void Skeleton::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void Skeleton::Render(Viewport * viewport)
{

}

Skeleton::~Skeleton()
{

}
