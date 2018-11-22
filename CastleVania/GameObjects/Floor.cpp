#include "Floor.h"



Floor::Floor()
{
	id = ID_TEX_FLOOR;
}

void Floor::Render(Viewport * viewport)
{
		
}

void Floor::GetBoundingBox(float & l, float & t, float & r, float & b)
{

	l = x;
	t = y;
	r = x + FLOOR_BBOX_WIDTH;
	b = y + FLOOR_BBOX_HEIGHT;

}


Floor::~Floor()
{
}
