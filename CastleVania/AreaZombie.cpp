#include "AreaZombie.h"


AreaZombie::AreaZombie()
{
	id = ID_ENTITY_AREA_ZOMBIE;
}

void AreaZombie::Render(Viewport * viewport)
{
//	RenderBoundingBox(viewport);
}

void AreaZombie::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

AreaZombie::~AreaZombie()
{
}
