#include "PortalPosMap.h"



PortalPosMap::PortalPosMap(D3DXVECTOR2 pos, int height, int width, float startViewportX, float endViewportX, float startViewportY)
{
	id = ID_ENTITY_PORTAL_POS_MAP;
	SetPosition(pos);
	this->height = height;
	this->width = width;
	this->startViewportX = startViewportX;
	this->endViewportX = endViewportX;
	this->startViewportY = startViewportY;
}

void PortalPosMap::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void PortalPosMap::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void PortalPosMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt, coObjects);
}

PortalPosMap::~PortalPosMap()
{
}
