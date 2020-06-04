#include "ObjectStair.h"

ObjectStair::ObjectStair(D3DXVECTOR2 pos, int width, int height, int nxStair, int nyStair, int heightStair,bool isTwoDirection)
{
	this->id = ID_ENTITY_STAIR;
	SetPosition(pos);
	this->width = width;
	this->height = height;
	this->heightStair = heightStair;
	this->nxStair = nxStair;
	this->nyStair = nyStair;
	this->isTwoDirection = isTwoDirection;
}

//ObjectStair::ObjectStair(ObjectStair * o)
//{
//	this->id = ID_ENTITY_STAIR;
//	SetPosition(o->getPosition());
//	this->width = o->width;
//	this->height = o->height;
//	this->heightStair = o->heightStair;
//	this->nxStair = o->nxStair;
//	this->nyStair = o->nyStair;
//	this->isTwoDirection = o->isTwoDirection;
//}

void ObjectStair::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void ObjectStair::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

ObjectStair::~ObjectStair()
{
}
