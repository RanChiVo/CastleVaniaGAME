#include "WallEntrance.h"

constexpr int WALL_ENTRANCE_WIDTH = 16;
constexpr int WALL_ENTRANCE_HEIGHT = 312;

WallEntrance::WallEntrance(D3DXVECTOR2 position)
{
	id = ID_TEX_WALL_ENTRANCE;
	x = position.x;
	y = position.y;
}

void WallEntrance::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void WallEntrance::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + WALL_ENTRANCE_WIDTH;
	b = y + WALL_ENTRANCE_HEIGHT;
}

WallEntrance::~WallEntrance()
{
}
