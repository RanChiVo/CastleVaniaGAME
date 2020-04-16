#include "WallEntrance.h"
#include "GameObjects/Simon.h"

WallEntrance::WallEntrance(D3DXVECTOR2 pos, int height, int width)
{
	id = ID_ENTITY_WALL_ENTRANCE;
	this->height = height;
	this->width = width;
	SetPosition(pos);
}

void WallEntrance::Render(Viewport * viewport)
{
	RenderBoundingBox(viewport);
}

void WallEntrance::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (name.compare("WallEndMap")==0 )
	{
		if (!Simon::getInstance()->isMovedEndMap())
		{
			l = t = r = b = 0;
		}
		else
		{
			l = x;
			t = y;
			r = x + width;
			b = y + height;
		}
	}
	else 
	{
		l = x;
		t = y;
		r = x + width;
		b = y + height;
	}
}

WallEntrance::~WallEntrance()
{
}
