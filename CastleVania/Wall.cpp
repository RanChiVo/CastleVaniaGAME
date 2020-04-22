#include "Wall.h"
#include "GameObjects/Simon.h"

Wall::Wall(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_WALL;
	this->height = height;
	this->width = width;
	SetPosition(pos);
}

void Wall::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void Wall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
	
}

Wall::~Wall()
{
}
