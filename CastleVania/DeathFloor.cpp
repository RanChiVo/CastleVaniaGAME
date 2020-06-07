#include "DeathFloor.h"


DeathFloor::DeathFloor(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_DEATH_FLOOR;
	this->height = height;
	this->width = width;
	SetPosition(pos);
}

void DeathFloor::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void DeathFloor::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

DeathFloor::~DeathFloor()
{
}
