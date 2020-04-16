#include "Entrance.h"


Entrance::Entrance(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_ENTRANCE;
	this->height = height;
	this->width = width;
	SetPosition(pos);
}

void Entrance::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void Entrance::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

Entrance::~Entrance()
{
}
