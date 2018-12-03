#include "Brick.h"
#include "Animations/Animations.h"


CBrick::CBrick(D3DXVECTOR2 position)
{
	id = ID_TEX_WALL;
	x = position.x;
	y = position.y;
}

void CBrick::Render(Viewport* viewport)
{
	RenderBoundingBox(viewport);
}

void CBrick::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

CBrick::~CBrick()
{
}
