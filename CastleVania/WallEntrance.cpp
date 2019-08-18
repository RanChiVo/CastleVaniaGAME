#include "WallEntrance.h"


WallEntrance::WallEntrance()
{
	id = ID_TEX_WALL_ENTRANCE;
}

void WallEntrance::Render(Viewport * viewport)
{
	//RenderBoundingBox(viewport);
}

void WallEntrance::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

WallEntrance::~WallEntrance()
{
}
