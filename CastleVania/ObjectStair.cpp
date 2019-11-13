#include "ObjectStair.h"

ObjectStair::ObjectStair(D3DXVECTOR2 pos, D3DXVECTOR4 infoStair, int height)
{
	this->id = ID_ENTITY_STAIR;
	SetPosition(pos);
	this->infoStair = infoStair;
	this->bboxWidth = infoStair.x;
	this->bboxHeight = infoStair.y;
	this->height = height;
}

void ObjectStair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + bboxWidth;
	bottom = y + bboxHeight;
}

void ObjectStair::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

ObjectStair::~ObjectStair()
{
}
