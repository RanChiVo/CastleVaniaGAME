#include "Entrance.h"


Entrance::Entrance()
{
	id = ID_TEX_ENTRANCE;
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
