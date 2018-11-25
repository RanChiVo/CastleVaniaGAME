#include "Entrance.h"

constexpr float ETRANCE_BBOX_WIDTH = 31.0f;
constexpr float ETRANCE_BBOX_HEIGHT = 166.0f;

Entrance::Entrance(D3DXVECTOR2 pos)
{
	id = ID_TEX_ENTRANCE;
	x = pos.x;
	y = pos.y;
}

void Entrance::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void Entrance::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + ETRANCE_BBOX_WIDTH;
	b = y + ETRANCE_BBOX_HEIGHT;
}

Entrance::~Entrance()
{
}
