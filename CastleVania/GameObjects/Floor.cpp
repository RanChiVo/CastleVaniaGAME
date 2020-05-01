#include "Floor.h"

Floor::Floor(D3DXVECTOR2 position, int height, int width)
{
	id = ID_ENTITY_FLOOR;
	this->x = position.x;
	this->y = position.y;
	setHeight(height);
	setWidth(width);
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
