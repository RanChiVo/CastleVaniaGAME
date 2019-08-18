#include "Brick.h"
#include "Animations/Animations.h"


CBrick::CBrick()
{
	id = ID_TEX_WALL;
}

void CBrick::Render(Viewport* viewport)
{
	//RenderBoundingBox(viewport);
}

void CBrick::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

CBrick::~CBrick()
{
}
