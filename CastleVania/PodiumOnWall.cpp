#include "PodiumOnWall.h"

PodiumOnWall::PodiumOnWall()
{
}

PodiumOnWall::PodiumOnWall(D3DXVECTOR2 position)
{
	id = ID_TEX_PODIUM_ON_WALL;
	x = position.x;
	y = position.y;
}

void PodiumOnWall::Render(Viewport * viewport)
{
	//RenderBoundingBox(viewport);
}

void PodiumOnWall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + PODIUM_WIDTH;
	b = y + PODIUM_HEIGHT;
}

PodiumOnWall::~PodiumOnWall()
{
}
