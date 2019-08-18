#include "Floor.h"



Floor::Floor()
{
	id = ID_TEX_FLOOR;
}

Floor::Floor(D3DXVECTOR2 position)
{
}

void Floor::Render(Viewport * viewport)
{
	//RenderBoundingBox(viewport);
}

void Floor::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}


Floor::~Floor()
{
}
